#include <QSystemTrayIcon>
#include "maindialog.h"

#ifndef SYSTEMTRAYICON_H
#define SYSTEMTRAYICON_H


class SystemTrayIcon : public QSystemTrayIcon
{
public:
    SystemTrayIcon(const QIcon &icon, QWidget *parent, MainDialog * _mainDialog);
private:
    MainDialog *mainDialog;
    void onExit();
    void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void onOpen();
};

#endif // SYSTEMTRAYICON_H
