#include "iconfigstorage.h"
#include "binfilehandler.h"
#include "config.h"

#ifndef CONFIGSTORAGE_H
#define CONFIGSTORAGE_H


class ConfigStorage : public IConfigStorage
{
public:
    ConfigStorage();
    Config* readFromFile() override;
    void saveToFile(Config& _config) override;

private:
    BinFileHandler bFH;
};

#endif // CONFIGSTORAGE_H
