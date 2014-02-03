#include "mainwindow.h"
#include "source.h"
#include "distributeur.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Source test;
    //test.generer_trafic();

    Distributeur::get_distributeur().increment();
    Distributeur::get_distributeur().afficher();

    return a.exec();
}
