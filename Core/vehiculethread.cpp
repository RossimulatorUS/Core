#include "vehiculethread.h"
#include <QDebug>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>

const unsigned int REFRESH_TIME = 100000;

unsigned int VehiculeThread::id_a_date_ = 0;

VehiculeThread::VehiculeThread()
    : execution_(&VehiculeThread::demarrer_traitement,this, this),
      terminer(false)
{
    vehicules_ = std::vector<Vehicule*>();

    // Retouner id et incrementer ensuite
    id_ = id_a_date_++;
}

void VehiculeThread::demarrer_traitement(VehiculeThread* vt)
{
    while(!terminer)
    {
        // Temps depart
        for (unsigned int i = 0; i < vt->vehicules_.size(); ++i)
        {
            vt->vehicules_[i]->x_ += vt->vehicules_[i]->xVariation_;
            vt->vehicules_[i]->y_ += vt->vehicules_[i]->yVariation_;
            //qDebug() << vt->vehicules_[i]->x_ << "," << vt->vehicules_[i]->y_;
        }
        usleep(REFRESH_TIME/* - (temps_fin - temps_depart)*/);

        //QObject *test = this->parent();
        //MyGLWidget *widget = reinterpret_cast<MyGLWidget*>(test);
        //widget->RemoveCar(vehicule);

    }
}

void VehiculeThread::ajouter_vehicule(Vehicule* vehicule)
{
    //qDebug() << vehicules_->size();
    vehicules_.emplace_back(vehicule); // vehicules n'existe pas encore
}

void VehiculeThread::termine()
{
    terminer = true;
}


