#include "window.h"
#include <QApplication>
#include <QDesktopWidget>
#include <myglwidget.h>


int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Window window;

    window.setWindowTitle("OpenGL with Qt");
    window.show();
    return app.exec();
}
