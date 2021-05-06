#include "iconfigwriter.h"
#include "binfilehandler.h"
#include "config.h"

#ifndef CONFIGWRITER_H
#define CONFIGWRITER_H


class ConfigWriter : public IConfigWriter
{
public:
    ConfigWriter();
    Config* readFromFile() override;
    void saveToFile(Config& _config) override;

private:
    BinFileHandler bFH;
};

#endif // CONFIGWRITER_H
