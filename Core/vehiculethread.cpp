#include "vehiculethread.h"
#include <QDebug>
#include <iostream>

VehiculeThread::VehiculeThread(unsigned int id)
    : terminer(false), execution_(&VehiculeThread::demarrer_traitement, this), id_(id)
{

}

void VehiculeThread::demarrer_traitement()
{
    while(!terminer)
    {
        if(terminer) break;
        std::cout << "Thread " << id_ << ", " << std::flush;
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


