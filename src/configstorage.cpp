#include "configstorage.h"

ConfigStorage::ConfigStorage()
{

}

Config* ConfigStorage::readFromFile()
{

    return bFH.readFromFile<Config>("config.dat");
}

void ConfigStorage::saveToFile(Config &_config)
{
    bFH.saveToFile<Config>("config.dat", _config);
}
