#include "config.h"

#ifndef ICONFIGSTORAGE_H
#define ICONFIGSTORAGE_H

class IConfigStorage
{
public:
    virtual Config *readFromFile() = 0;
    virtual void saveToFile(Config& _config) = 0;
};

#endif // ICONFIGSTORAGE_H
