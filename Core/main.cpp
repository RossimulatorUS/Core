#include "window.h"
#include <QApplication>
#include <QDesktopWidget>
#include "myglwidget.h"
#include "map_fetcher.h"
#include <iostream>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Window window;

    window.setWindowTitle("RossimulatorUS");
    window.show();
    return app.exec();
   /* map_fetcher carte(45.37736,-71.93052, 45.37936, -71.928952);
    carte.execute();
    carte.print();
    return 0;*/
}
