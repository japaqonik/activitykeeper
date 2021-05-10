#include <memory>
#include "maindialog.h"
#include "systemtrayicon.h"

#ifndef APPGUIMANAGER_H
#define APPGUIMANAGER_H


class AppGuiManager
{
public:
    AppGuiManager(IConfigHandler *_cfgHandler, IMouseMover *_mouseMover);
    void start();

private:
    std::unique_ptr<QWidget> widget;
    std::unique_ptr<MainDialog> dialog;
    std::unique_ptr<SystemTrayIcon> tray;

    IMouseMover *mouseMover;
    IConfigHandler *cfgHandler;

    void initConfig();
    void onEnabledCheckBoxStateChange(int state);
    void onShadowCheckBoxStateChange(int state);
    void onSliderValueChange(int value);
    void onTimerTimeout();
    void updateTimer(int newValue);

    void onExit();
    void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void onOpen();
};

#endif // APPGUIMANAGER_H
