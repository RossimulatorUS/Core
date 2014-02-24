#include "vehiculethread.h"
#include <QDebug>
#include <iostream>

VehiculeThread::VehiculeThread(unsigned int id)
    : execution_(&VehiculeThread::demarrer_traitement, this), terminer(false), id_(id)
{

}

void VehiculeThread::demarrer_traitement()
{
    while(!terminer)
    {
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


