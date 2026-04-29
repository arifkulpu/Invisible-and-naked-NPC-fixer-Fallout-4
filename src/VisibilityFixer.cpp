#include "PCH.h"
#include "VisibilityFixer.h"
#include "Settings.h"

#include <unordered_map>
#include <vector>
#include <chrono>

using namespace std::chrono_literals;

namespace VisibilityFixer
{
    // FormID usually is uint32_t in FO4
    std::unordered_map<std::uint32_t, std::chrono::steady_clock::time_point> actorFixTimestamps;
    std::chrono::steady_clock::time_point systemStartTime = std::chrono::steady_clock::now();

    bool IsHumanoidNPC(RE::Actor* a_actor)
    {
        if (!a_actor) return false;

        auto npcBase = a_actor->GetNPC();
        if (npcBase && (npcBase->defOutfit || npcBase->sleepOutfit)) {
            return true;
        }

        auto race = a_actor->race;
        if (race) {
            // HumanRace [RACE:00013746], GhoulRace [RACE:00013743]
            if (race->formID == 0x00013746 || race->formID == 0x00013743) {
                return true;
            }
        }

        return false;
    }

    void ProcessActorFix(RE::Actor* actor)
    {
        if (!actor) return;

        auto root = actor->Get3D();
        auto formID = actor->formID;

        bool fixed = false;

        if (!root) {
            logger::info("[Fix] {:08X} Visibility issue detected.", formID);
            actor->Set3DUpdateFlag(RE::RESET_3D_FLAGS::kModel);
            actor->Update3DPosition(false);
            fixed = true;
        } 
        else {
            if (IsHumanoidNPC(actor)) {
                bool isNaked = true;
                if (actor->inventoryList) {
                    actor->inventoryList->rwLock.lock_read();
                    for (const auto& item : actor->inventoryList->data) {
                        if (item.object) {
                            auto armor = item.object->As<RE::TESObjectARMO>();
                            if (armor && item.stackData) {
                                for (auto stack = item.stackData.get(); stack; stack = stack->nextStack.get()) {
                                    if (stack->IsEquipped()) {
                                        if (armor->bipedModelData.bipedObjectSlots & 0x00000008) {
                                            isNaked = false;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        if (!isNaked) break;
                    }
                    actor->inventoryList->rwLock.unlock_read();
                }

                if (isNaked && !actor->IsDead(false)) {
                    logger::info("[Fix] {:08X} NPC is naked. Fixing...", formID);
                    
                    auto equipMgr = RE::ActorEquipManager::GetSingleton();
                    if (equipMgr) {
                        actor->ResetInventory(false);
                        fixed = true;
                    }
                }
            }
        }

        if (fixed) {
            actor->Set3DUpdateFlag(RE::RESET_3D_FLAGS::kModel);
            actor->Update3DPosition(false);
            logger::info(" -> Fix applied.");
        }
    }

    void FixActor(RE::Actor* actor)
    {
        if (!actor || actor->IsPlayerRef()) return;
        if (actor->formFlags & (1u << 11)) return;

        auto formID = actor->formID;
        auto now = std::chrono::steady_clock::now();

        auto it = actorFixTimestamps.find(formID);
        if (it != actorFixTimestamps.end()) {
            if (now - it->second < std::chrono::seconds(Settings::GetSingleton().cooldown)) {
                return;
            }
        }

        actorFixTimestamps[formID] = now;
        ProcessActorFix(actor);
    }

    // Since TESObjectLoadedEvent is missing/different in this CommonLibF4, 
    // we use CellAttachDetachEvent and MenuOpenCloseEvent as alternatives.

    class EventHandler : 
        public RE::BSTEventSink<RE::CellAttachDetachEvent>,
        public RE::BSTEventSink<RE::MenuOpenCloseEvent>
    {
    public:
        virtual RE::BSEventNotifyControl ProcessEvent(const RE::CellAttachDetachEvent& a_event, RE::BSTEventSource<RE::CellAttachDetachEvent>*) override
        {
            if (a_event.type == RE::CellAttachDetachEvent::EVENT_TYPE::kPostAttach) {
                if (a_event.cell) {
                    for (auto& refPtr : a_event.cell->references) {
                        if (refPtr) {
                            auto actor = refPtr->As<RE::Actor>();
                            if (actor) {
                                FixActor(actor);
                            }
                        }
                    }
                }
            }
            return RE::BSEventNotifyControl::kContinue;
        }

        virtual RE::BSEventNotifyControl ProcessEvent(const RE::MenuOpenCloseEvent& a_event, RE::BSTEventSource<RE::MenuOpenCloseEvent>*) override
        {
            if (!a_event.opening && a_event.menuName == "LoadingMenu") {
                // When loading ends, clear cache and maybe scan nearby actors?
                ClearFixedActors();
            }
            return RE::BSEventNotifyControl::kContinue;
        }

        static EventHandler* GetSingleton()
        {
            static EventHandler singleton;
            return &singleton;
        }
    };

    void Install()
    {
        auto ui = RE::UI::GetSingleton();
        if (ui) {
            ui->RegisterSink<RE::MenuOpenCloseEvent>(EventHandler::GetSingleton());
        }

        auto& cellEventSource = RE::CellAttachDetachEventSource::CellAttachDetachEventSourceSingleton::GetSingleton();
        cellEventSource.source.RegisterSink(EventHandler::GetSingleton());

        logger::info("VisibilityFixer: Events registered (CellAttach, MenuOpenClose).");
    }

    void ClearFixedActors()
    {
        actorFixTimestamps.clear();
        systemStartTime = std::chrono::steady_clock::now();
        logger::info("VisibilityFixer: Lists cleared.");
    }
}

