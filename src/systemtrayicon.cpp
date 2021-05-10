#include "systemtrayicon.h"
#include <QMenu>

SystemTrayIcon::SystemTrayIcon(QWidget *parent): QSystemTrayIcon{QIcon{":icons/icon.ico"}, parent}
{
    setToolTip("Activity keeper");

    auto menu = new QMenu(parent);
    open = menu->addAction("Open");
    menu->addSeparator();
    exit = menu->addAction("Exit");

    setContextMenu(menu);
}

void SystemTrayIcon::setOnOpenAction(std::function<void ()> action)
{
    onOpenAction = action;
    connect(open, &QAction::triggered, this, &SystemTrayIcon::onOpen);
}

void SystemTrayIcon::onOpen()
{
    onOpenAction();
}

void SystemTrayIcon::setOnExitAction(std::function<void ()> action)
{
    onExitAction = action;
    connect(exit, &QAction::triggered, this, &SystemTrayIcon::onExit);
}

void SystemTrayIcon::onExit()
{
    onExitAction();
}

void SystemTrayIcon::setOnTrayIconTriggeredAction(std::function<void (ActivationReason)> action)
{
    onTrayIconTriggeredAction = action;
    connect(this, &QSystemTrayIcon::activated, this, &SystemTrayIcon::onTrayIconTriggered);
}

void SystemTrayIcon::onTrayIconTriggered(ActivationReason reason)
{
    onTrayIconTriggeredAction(reason);
}
