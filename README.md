# Fallout 4 Naked and Visible NPC Fix (NakedNPCFixF4)

Bu mod, Fallout 4'te motor tabanlı (engine-level) olarak ortaya çıkan NPC görünmezlik ve kıyafet giymeme sorunlarını otomatik olarak çözen bir **F4SE (Fallout 4 Script Extender)** eklentisidir.

## 🚀 Ne İşe Yarar?

Mod, oyun sırasında arka planda sessizce çalışarak şu iki ana sorunu giderir:

### 1. Görünmezlik (Hayalet) Düzeltmesi
Hücre (Cell) geçişleri veya yükleme ekranları sonrasında NPC'lerin 3D modellerinin yüklenmemesi (invisible/ghosting) durumunu anında tespit eder. Motor seviyesinde bir yenileme (3D Refresh) tetikleyerek karakteri tekrar görünür kılar.

### 2. Çıplak NPC Düzeltmesi
Özellikle animasyon modları veya yoğun sahne geçişleri sonrasında karakterlerin kıyafetlerini tekrar giymemesi durumunu kontrol eder. 
*   Karakterin "Body" (Slot 33) kısmında bir zırh/kıyafet olup olmadığına bakar.
*   Eğer karakter çıplaksa, motoru zorlayarak varsayılan kıyafetlerini (Default Outfit) tekrar giymesini sağlar.

## 🛠️ Teknik Özellikler

*   **Sıfır Performans Kaybı:** Mod her saniye kontrol yapmak yerine; sadece yükleme ekranları bittiğinde, menüler kapandığında veya yeni bir bölgeye girildiğinde tetiklenir.
*   **Akıllı Hedefleme:** Sadece **İnsan** ve **Ghoul** ırklarını hedefler. Robotlar, yaratıklar veya oyuncunun kendisi üzerinde işlem yapmaz.
*   **Gelişmiş Filtreleme:** Oyunun kendi senaryosu gereği gizli (Disabled) olan karakterlere dokunmaz, böylece questlerin bozulmasını engeller.
*   **Cooldown Sistemi:** Her NPC için bir bekleme süresi uygular, böylece aynı karaktere üst üste işlem yaparak döngü oluşturmaz.

## 🏗️ Kullanılan Teknolojiler

Bu mod, modern Fallout 4 modlama standartları kullanılarak C++ ile geliştirilmiştir:

*   **C++ 23:** En güncel programlama standartları.
*   **CommonLibF4:** Fallout 4 motoruna erişim sağlayan en gelişmiş framework.
*   **F4SE:** Fallout 4 Script Extender API.
*   **spdlog & fmt:** Yüksek performanslı loglama ve metin biçimlendirme kütüphaneleri.

## 📥 Kurulum

1.  `NakedNPCFixF4.dll` dosyasını `Fallout 4\Data\F4SE\Plugins\` klasörüne kopyalayın.
2.  Oyunu `f4se_loader.exe` ile başlatın.
3.  Logları kontrol etmek isterseniz: `Documents\My Games\Fallout4\F4SE\NakedNPCFixF4.log` yoluna bakabilirsiniz.

## 📝 Gereksinimler
*   Fallout 4 (v1.10.163 veya uyumlu sürümler)
*   Fallout 4 Script Extender (F4SE)
