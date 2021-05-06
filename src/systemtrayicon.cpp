#include "systemtrayicon.h"
#include <QMenu>

SystemTrayIcon::SystemTrayIcon(const QIcon &icon, QWidget *parent, MainDialog * _mainDialog): QSystemTrayIcon(icon, parent), mainDialog(_mainDialog)
{
    setToolTip("Cursor mover");

    auto menu = new QMenu(parent);
    auto open_app = menu->addAction("Open");
    connect(open_app, &QAction::triggered, this, &SystemTrayIcon::onOpen);

    menu->addSeparator();

    auto exit = menu->addAction("Exit");

    connect(exit, &QAction::triggered, this, &SystemTrayIcon::onExit);

    connect(this, &QSystemTrayIcon::activated, this, &SystemTrayIcon::onTrayIconActivated);

    this->setContextMenu(menu);
}

void SystemTrayIcon::onExit()
{
    std::exit(0);
}

void SystemTrayIcon::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == DoubleClick)
    {
        if(mainDialog->isVisible())
        {
            mainDialog->hide();
        }
        else
        {
            mainDialog->show();
        }
    }
}

void SystemTrayIcon::onOpen()
{
    if(!mainDialog->isVisible())
    {
        mainDialog->show();
    }
}
