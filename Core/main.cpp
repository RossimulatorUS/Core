#include "window.h"
#include <QApplication>
#include <QDesktopWidget>
#include "myglwidget.h"
#include "map_fetcher.h"
#include <iostream>

int main(int argc, char **argv)
{
    std::cout<<"IN MAIN"<<std::endl;
    QApplication app(argc, argv);

    Window window;

    window.setWindowTitle("RossimulatorUS");
    window.show();
    return app.exec();
}
