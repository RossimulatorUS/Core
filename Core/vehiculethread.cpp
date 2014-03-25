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
            if((*itt)->Process() == false)   //i.e. le véhicule est arrivé à destination
            {
                //vt->vehicules_.remove(*itt); //on peut pas modifier une collection sur laquelle on itère, donc changer ça
                SimulationData::GetInstance().GetVehiculesPointer()->remove(*itt);
                //delete(*itt);
            }
            //x_ += vt->vehicules_[i]->xVariation_;
            //vt->vehicules_[i]->y_ += vt->vehicules_[i]->yVariation_;
            //qDebug() << (*itt)->x_ << "," << (*itt)->y_ << " : " << vt->id_;
        }
        std::chrono::milliseconds timespan(100);
        std::this_thread::sleep_for(timespan);
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


