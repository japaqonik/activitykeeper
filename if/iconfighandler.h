#include "config.h"

#ifndef ICONFIGHANDLER_H
#define ICONFIGHANDLER_H

class IConfigHandler
{
public:
    virtual void importConfig() = 0;
    virtual const Config* getConfig() const = 0;
    virtual void setConfig(const Config &_config) = 0;
};

#endif // ICONFIGHANDLER_H
