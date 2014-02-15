#include "vehiculethread.h"
#include <QDebug>

VehiculeThread::VehiculeThread()
    : terminer(true), execution_(&VehiculeThread::traitement, this)
{

}

void VehiculeThread::traitement()
{
    while(true)
    {
        /*if (vehicules_ == NULL)
            qDebug() << "VEHICULE IS NULL";
        else
            vehicules_->y_-=0.01;
        */

        // S'il faut donner du temps a un autre fil d'execution
        if(terminer) break;
    }
}

void VehiculeThread::ajouter_vehicule(Vehicule vehicule)
{
    vehicules_.push_back(vehicule);
}

void VehiculeThread::termine()
{
    terminer = true;
}


