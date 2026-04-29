# Fallout 4 Naked and Visible NPC Fix (NakedNPCFixF4)

[English](#english) | [Türkçe](#türkçe)

---

<a name="english"></a>
## English

This mod is an **F4SE (Fallout 4 Script Extender)** plugin that automatically resolves engine-level NPC visibility and re-equipping issues.

### 🚀 Key Features

The mod works silently in the background and fixes two major issues:

#### 1. Visibility (Ghost NPC) Fix
Addresses the issue where NPCs' 3D models fail to load (becoming invisible/ghosts) after cell transitions or loading screens. It triggers an engine-level 3D refresh to make the character visible again immediately.

#### 2. Naked NPC Fix
Ensures characters correctly re-equip their clothing after animation scenes or complex state transitions.
*   Checks if the NPC is equipped in the "Body" slot (Slot 33).
*   If the NPC is incorrectly naked, it forces an inventory reset to re-equip their Default Outfit.

### 🛠️ Technical Highlights

*   **Zero Performance Impact:** Instead of constant polling, the mod triggers only during specific events like loading screen completions, menu closures, or cell attachments.
*   **Smart Targeting:** Specifically targets **Human** and **Ghoul** races. It does not interfere with robots, creatures, or the player character.
*   **Quest Friendly:** Respects the game's internal "Disabled" flags to ensure NPCs intended to be hidden by quests remain hidden.
*   **Cooldown System:** Implements a per-actor cooldown timer to prevent redundant processing or potential loops.

### 🏗️ Built With

Developed using modern Fallout 4 modding standards:

*   **C++ 23:** Utilizing the latest programming standards.
*   **CommonLibF4:** The most advanced framework for Fallout 4 engine access.
*   **F4SE:** Fallout 4 Script Extender API.
*   **spdlog & fmt:** High-performance logging and text formatting libraries.

### 📥 Installation

1.  Copy `NakedNPCFixF4.dll` to your `Fallout 4\Data\F4SE\Plugins\` directory.
2.  Launch the game using `f4se_loader.exe`.
3.  Check logs at: `Documents\My Games\Fallout4\F4SE\NakedNPCFixF4.log`

### 📝 Requirements
*   Fallout 4 (v1.10.163 or compatible versions)
*   Fallout 4 Script Extender (F4SE)

---

<a name="türkçe"></a>
## Türkçe

Bu mod, Fallout 4'te motor tabanlı (engine-level) olarak ortaya çıkan NPC görünmezlik ve kıyafet giymeme sorunlarını otomatik olarak çözen bir **F4SE (Fallout 4 Script Extender)** eklentisidir.

### 🚀 Ne İşe Yarar?

Mod, oyun sırasında arka planda sessizce çalışarak şu iki ana sorunu giderir:

#### 1. Görünmezlik (Hayalet) Düzeltmesi
Hücre (Cell) geçişleri veya yükleme ekranları sonrasında NPC'lerin 3D modellerinin yüklenmemesi (invisible/ghosting) durumunu anında tespit eder. Motor seviyesinde bir yenileme (3D Refresh) tetikleyerek karakteri tekrar görünür kılar.

#### 2. Çıplak NPC Düzeltmesi
Özellikle animasyon modları veya yoğun sahne geçişleri sonrasında karakterlerin kıyafetlerini tekrar giymemesi durumunu kontrol eder. 
*   Karakterin "Body" (Slot 33) kısmında bir zırh/kıyafet olup olmadığına bakar.
*   Eğer karakter çıplaksa, motoru zorlayarak varsayılan kıyafetlerini (Default Outfit) tekrar giymesini sağlar.

### 🛠️ Teknik Özellikler

*   **Sıfır Performans Kaybı:** Mod her saniye kontrol yapmak yerine; sadece yükleme ekranları bittiğinde, menüler kapandığında veya yeni bir bölgeye girildiğinde tetiklenir.
*   **Akıllı Hedefleme:** Sadece **İnsan** ve **Ghoul** ırklarını hedefler. Robotlar, yaratıklar veya oyuncunun kendisi üzerinde işlem yapmaz.
*   **Gelişmiş Filtreleme:** Oyunun kendi senaryosu gereği gizli (Disabled) olan karakterlere dokunmaz, böylece questlerin bozulmasını engeller.
*   **Cooldown Sistemi:** Her NPC için bir bekleme süresi uygular, böylece aynı karaktere üst üste işlem yaparak döngü oluşturmaz.

### 🏗️ Kullanılan Teknolojiler

Bu mod, modern Fallout 4 modlama standartları kullanılarak C++ ile geliştirilmiştir:

*   **C++ 23:** En güncel programlama standartları.
*   **CommonLibF4:** Fallout 4 motoruna erişim sağlayan en gelişmiş framework.
*   **F4SE:** Fallout 4 Script Extender API.
*   **spdlog & fmt:** Yüksek performanslı loglama ve metin biçimlendirme kütüphaneleri.

### 📥 Kurulum

1.  `NakedNPCFixF4.dll` dosyasını `Fallout 4\Data\F4SE\Plugins\` klasörüne kopyalayın.
2.  Oyunu `f4se_loader.exe` ile başlatın.
3.  Logları kontrol etmek isterseniz: `Documents\My Games\Fallout4\F4SE\NakedNPCFixF4.log` yoluna bakabilirsiniz.

### 📝 Gereksinimler
*   Fallout 4 (v1.10.163 veya uyumlu sürümler)
*   Fallout 4 Script Extender (F4SE)
