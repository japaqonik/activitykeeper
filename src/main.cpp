#include <QWidget>
#include <QApplication>
#include <QDialog>
#include <QImageReader>
#include <iostream>
#include "configwriter.h"
#include "mousehandler.h"
#include "systemtrayicon.h"
#include "confighandler.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget w;

    ConfigWriter configWriter;
    ConfigHandler cfgHandler{&configWriter};
    cfgHandler.importConfig();

    MouseHandler mouseHandler;
    MouseMover mouseMover{&mouseHandler};

    MainDialog mainDialog{&cfgHandler, &mouseMover};
    SystemTrayIcon trayIcon(QIcon(":icons/icon.ico"), &w, &mainDialog);
    trayIcon.show();
    mainDialog.show();

    return a.exec();
}
