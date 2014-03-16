#include <QDebug>

#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>

#include "simulationdata.h"
#include "vehiculethread.h"

unsigned int VehiculeThread::id_a_date_ = 0;

VehiculeThread::VehiculeThread()
    : execution_(&VehiculeThread::demarrer_traitement,this, this),
      terminer(false)
{
    vehicules_ = std::list<Vehicule*>();

    // Retouner id et incrementer ensuite
    id_ = id_a_date_++;
}

void VehiculeThread::demarrer_traitement(VehiculeThread* vt)
{
    while(!terminer)
    {
        //if(!(*attendre_))
        // Temps depart
        for (auto itt = vt->vehicules_.begin() ; itt != vt->vehicules_.end() ; ++itt)
        {
            if((*itt)->Process() == false)   //HE MUST DIE IF HE IS FALSE
            {
                qDebug() << "DESTROY!";
                vt->vehicules_.remove(*itt);
                SimulationData::GetInstance().GetVehiculesPointer()->remove(*itt);
                delete(*itt);
                //*itt
                //destroy it in simulation data first instead of glwidget
                //and here too, bitch
            }
            //x_ += vt->vehicules_[i]->xVariation_;
            //vt->vehicules_[i]->y_ += vt->vehicules_[i]->yVariation_;
            qDebug() << (*itt)->x_ << "," << (*itt)->y_ << " : " << vt->id_;
        }
    }
}

void VehiculeThread::ajouter_vehicule(Vehicule* vehicule)
{
    //qDebug() << vehicules_->size();
    vehicules_.push_back(vehicule); // vehicules n'existe pas encore
}

void VehiculeThread::termine()
{
    terminer = true;
}


