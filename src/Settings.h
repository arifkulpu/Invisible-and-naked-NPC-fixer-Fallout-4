#pragma once

class Settings
{
public:
    static Settings& GetSingleton()
    {
        static Settings singleton;
        return singleton;
    }

    void Load()
    {
        // Temel ayarlar (İleride INI'den okunabilir)
    }

    int scanInterval = 5;
    int cooldown = 30;
    int startupDelay = 10;
    bool logFixes = true;
};
