#include <fstream>
#include <iostream>
#include <cstring>
#include <memory>
#include "confighandler.h"

ConfigHandler::ConfigHandler(IConfigWriter * _configWriter) : configWriter{_configWriter}
{
    auto cfg = configWriter->readFromFile();

    if(cfg)
    {
        config = std::make_unique<Config>(*cfg);
    }
}

void ConfigHandler::importConfig()
{

}

void ConfigHandler::saveConfig()
{
    configWriter->saveToFile(*config);
}

const Config *ConfigHandler::getConfig() const
{
    return config.get();
}

void ConfigHandler::setConfig(const Config &_config)
{
    if(!config)
    {
        config = std::make_unique<Config>();
    }
    *config.get() = _config;
    saveConfig();
}
