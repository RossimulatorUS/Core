#include "vehiculethread.h"
#include <QDebug>

VehiculeThread::VehiculeThread(QObject *parent) :
    QThread(parent)
{
}

void VehiculeThread::run()
{
    while(true)
    {
        if (vehicule == NULL)
            qDebug() << "VEHICULE IS NULL";
        else
            vehicule->y_-=0.01;
    }
}
