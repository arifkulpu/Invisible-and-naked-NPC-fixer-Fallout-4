#include "PCH.h"
#include "VisibilityFixer.h"
#include "Settings.h"
#include <spdlog/sinks/basic_file_sink.h>

void InitializeLog() {
    auto path = logger::log_directory();
    if (!path) return;

    *path /= "NakedNPCFixF4.log"sv;
    auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);

    auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));

    log->set_level(spdlog::level::info);
    log->flush_on(spdlog::level::info);

    spdlog::set_default_logger(std::move(log));
    spdlog::set_pattern("[%H:%M:%S] %v"s);
}

extern "C" __declspec(dllexport) bool F4SEAPI F4SEPlugin_Query(const F4SE::QueryInterface* a_skse, F4SE::PluginInfo* a_info)
{
    a_info->infoVersion = F4SE::PluginInfo::kVersion;
    a_info->name = "NakedNPCFixF4";
    a_info->version = 1;

    if (a_skse->IsEditor()) {
        return false;
    }

    return true;
}

extern "C" __declspec(dllexport) bool F4SEAPI F4SEPlugin_Load(const F4SE::LoadInterface* a_skse)
{
    InitializeLog();
    logger::info("NakedNPCFixF4 yukleniyor...");

    F4SE::Init(a_skse);
    Settings::GetSingleton().Load();

    auto messaging = F4SE::GetMessagingInterface();
    if (messaging) {
        messaging->RegisterListener([](F4SE::MessagingInterface::Message* a_msg) {
            switch (a_msg->type) {
                case F4SE::MessagingInterface::kGameDataReady:
                    VisibilityFixer::Install();
                    break;
                case F4SE::MessagingInterface::kPreLoadGame:
                case F4SE::MessagingInterface::kNewGame:
                    VisibilityFixer::ClearFixedActors();
                    break;
            }
        });
    }

    logger::info("NakedNPCFixF4 basariyla yuklendi!");

    return true;
}
