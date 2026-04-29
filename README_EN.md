# Fallout 4 Naked and Visible NPC Fix (NakedNPCFixF4)

This mod is an **F4SE (Fallout 4 Script Extender)** plugin that automatically resolves engine-level NPC visibility and re-equipping issues.

## 🚀 Key Features

The mod works silently in the background and fixes two major issues:

### 1. Visibility (Ghost NPC) Fix
Addresses the issue where NPCs' 3D models fail to load (becoming invisible/ghosts) after cell transitions or loading screens. It triggers an engine-level 3D refresh to make the character visible again immediately.

### 2. Naked NPC Fix
Ensures characters correctly re-equip their clothing after animation scenes or complex state transitions.
*   Checks if the NPC is equipped in the "Body" slot (Slot 33).
*   If the NPC is incorrectly naked, it forces an inventory reset to re-equip their Default Outfit.

## 🛠️ Technical Highlights

*   **Zero Performance Impact:** Instead of constant polling, the mod triggers only during specific events like loading screen completions, menu closures, or cell attachments.
*   **Smart Targeting:** Specifically targets **Human** and **Ghoul** races. It does not interfere with robots, creatures, or the player character.
*   **Quest Friendly:** Respects the game's internal "Disabled" flags to ensure NPCs intended to be hidden by quests remain hidden.
*   **Cooldown System:** Implements a per-actor cooldown timer to prevent redundant processing or potential loops.

## 🏗️ Built With

Developed using modern Fallout 4 modding standards:

*   **C++ 23:** Utilizing the latest programming standards.
*   **CommonLibF4:** The most advanced framework for Fallout 4 engine access.
*   **F4SE:** Fallout 4 Script Extender API.
*   **spdlog & fmt:** High-performance logging and text formatting libraries.

## 📥 Installation

1.  Copy `NakedNPCFixF4.dll` to your `Fallout 4\Data\F4SE\Plugins\` directory.
2.  Launch the game using `f4se_loader.exe`.
3.  Check logs at: `Documents\My Games\Fallout4\F4SE\NakedNPCFixF4.log`

## 📝 Requirements
*   Fallout 4 (v1.10.163 or compatible versions)
*   Fallout 4 Script Extender (F4SE)
