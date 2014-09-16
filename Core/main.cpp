#include "window.h"
#include <QApplication>
#include <QDesktopWidget>
#include "myglwidget.h"


int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Window window;

    window.setWindowTitle("RossimulatorUS");
    window.show();
    return app.exec();
}
