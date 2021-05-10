#include <QApplication>
#include "configwriter.h"
#include "confighandler.h"
#include "mousehandler.h"
#include "mousemover.h"
#include "appguimanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ConfigWriter configWriter;
    ConfigHandler cfgHandler{&configWriter};
    cfgHandler.importConfig();

    MouseHandler mouseHandler;
    MouseMover mouseMover{&mouseHandler};

    AppGuiManager app{&cfgHandler, &mouseMover};
    app.start();

    return a.exec();
}
