#include <memory>
#include "iconfighandler.h"
#include "iconfigstorage.h"
#include "config.h"

#ifndef CONFIGHANDLER_H
#define CONFIGHANDLER_H

class ConfigHandler : public IConfigHandler
{
public:
    ConfigHandler(IConfigStorage * _configWriter);

    const Config* getConfig() const override;
    void setConfig(const Config &_config) override;

private:
    IConfigStorage *configWriter;
    std::unique_ptr<Config> config;
};

#endif // CONFIGHANDLER_H
