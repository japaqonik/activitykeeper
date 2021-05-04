#include <QWidget>
#include <QApplication>
#include <QDialog>
#include <QImageReader>
#include <iostream>
#include "systemtrayicon.h"
#include "confighandler.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget w;
    ConfigHandler cfgHandler;
    cfgHandler.importConfig();
    MainDialog mainDialog{&cfgHandler};
    SystemTrayIcon trayIcon(QIcon(":icons/mouse.png"), &w, &mainDialog);
    trayIcon.show();
    mainDialog.show();

    return a.exec();
}
