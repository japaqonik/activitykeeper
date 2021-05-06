#include "config.h"

#ifndef ICONFIGWRITER_H
#define ICONFIGWRITER_H

class IConfigWriter
{
public:
    virtual Config *readFromFile() = 0;
    virtual void saveToFile(Config& _config) = 0;
};

#endif // ICONFIGWRITER_H
