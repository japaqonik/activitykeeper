#include <QApplication>
#include "configstorage.h"
#include "confighandler.h"
#include "mousehandler.h"
#include "mousemover.h"
#include "appguimanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ConfigStorage configStorage;
    ConfigHandler cfgHandler{&configStorage};

    MouseHandler mouseHandler;
    MouseMover mouseMover{&mouseHandler};

    AppGuiManager app{&cfgHandler, &mouseMover};
    app.start();

    return a.exec();
}
