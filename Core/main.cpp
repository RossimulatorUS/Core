#include "window.h"
#include <QApplication>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Window window;

    window.setWindowTitle("RossimulatorUS");
    window.show();
    return app.exec();
}
