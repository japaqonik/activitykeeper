#include <fstream>
#include <iostream>
#include <cstring>
#include "confighandler.h"

ConfigHandler::ConfigHandler()
{
    std::memset(&cfg, 0, sizeof(cfg));
}

void ConfigHandler::importConfig()
{
    std::ifstream configFile{"conf.dat", std::ios::out | std::ios::binary};

    if(configFile)
    {
        configImported = true;
        configFile.read(reinterpret_cast<char *>(&cfg), sizeof(Config));
        configFile.close();
    }
}

void ConfigHandler::saveConfig()
{
    std::ofstream configFile{"conf.dat", std::ios::out | std::ios::binary | std::ios::trunc};

    if(configFile)
    {
        configFile.write(reinterpret_cast<char *>(&cfg), sizeof(Config));
        configFile.close();
    }
}

bool ConfigHandler::getEnabled()
{
    return cfg.enabled;
}

void ConfigHandler::setEnabled(bool _enabled)
{
    cfg.enabled = _enabled;
    saveConfig();
}

unsigned short ConfigHandler::getTimerValue()
{
    return cfg.timerValue;
}

void ConfigHandler::setTimerValue(unsigned short _timerValue)
{
    cfg.timerValue = _timerValue;
    saveConfig();
}

bool ConfigHandler::configFileExists()
{
    return configImported;
}
