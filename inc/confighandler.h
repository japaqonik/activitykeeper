#include <memory>
#include "iconfighandler.h"
#include "iconfigwriter.h"
#include "config.h"

#ifndef CONFIGHANDLER_H
#define CONFIGHANDLER_H

class ConfigHandler : public IConfigHandler
{
public:
    ConfigHandler(IConfigWriter * _configWriter);

    void importConfig() override;

    const Config* getConfig() const override;
    void setConfig(const Config &_config) override;

private:
    IConfigWriter * configWriter;
    std::unique_ptr<Config> config;
    void saveConfig();

};

#endif // CONFIGHANDLER_H
