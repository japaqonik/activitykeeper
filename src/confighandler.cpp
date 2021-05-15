#include <fstream>
#include <iostream>
#include <cstring>
#include "confighandler.h"

ConfigHandler::ConfigHandler(IConfigStorage *_configWriter) : configWriter{_configWriter}
{
    auto cfg = configWriter->readFromFile();

    if(cfg)
    {
        config = std::make_unique<Config>(*cfg);
    }
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
    configWriter->saveToFile(*config);
}
