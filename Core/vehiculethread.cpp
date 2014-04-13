#include <QDebug>

#include <algorithm>

#include "simulationdata.h"
#include "vehiculethread.h"

unsigned int VehiculeThread::id_a_date_ = 0;

VehiculeThread::VehiculeThread(bool* terminer, volatile bool* executer)
    : execution_(&VehiculeThread::demarrer_traitement,this, this)
{
    vehicules_ = std::list<Vehicule*>();

    executer_ = executer;
    terminer_ = terminer;

    // Retouner id et incrementer ensuite
    id_ = id_a_date_++;
}

void VehiculeThread::demarrer_traitement(VehiculeThread* vt)
{
    while(!(*terminer_))
    {
        if(*executer_)
        {
            *executer_ = false;
            std::for_each(vt->vehicules_.begin(), vt->vehicules_.end(), [](Vehicule* v){
                if(v->Process() == false)   //i.e. le véhicule est arrivé à destination
                {
                    SimulationData::GetInstance().GetVehiculesPointer()->remove(v);
                }
            });
        }

        std::chrono::milliseconds timespan(1);
        std::this_thread::sleep_for(timespan);
    }
}

void VehiculeThread::ajouter_vehicule(Vehicule* vehicule)
{
    vehicules_.push_back(vehicule);
}

std::list<Vehicule*>::size_type VehiculeThread::nb_vehicules() const
{
    return vehicules_.size();
}

void VehiculeThread::termine()
{
    terminer = true;
}
