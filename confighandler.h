#ifndef CONFIGHANDLER_H
#define CONFIGHANDLER_H

struct Config{
    bool enabled;
    unsigned short timerValue;
};

class ConfigHandler
{
public:
    ConfigHandler();

    void importConfig();
    bool getEnabled();
    unsigned short getTimerValue();

    void setEnabled(bool _enabled);
    void setTimerValue(unsigned short _timerValue);

    bool configFileExists();

private:
    Config cfg;
    bool configImported = false;
    void saveConfig();

};

#endif // CONFIGHANDLER_H
