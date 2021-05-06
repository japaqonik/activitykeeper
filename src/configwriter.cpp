#include "configwriter.h"

ConfigWriter::ConfigWriter()
{

}

Config* ConfigWriter::readFromFile()
{

    return bFH.readFromFile<Config>("config.dat");
}

void ConfigWriter::saveToFile(Config &_config)
{
    bFH.saveToFile<Config>("config.dat", _config);
}
