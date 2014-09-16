#include <QDebug>

#include <algorithm>

#include "simulationdata.h"
#include "vehiculethread.h"

unsigned int VehiculeThread::id_a_date_ = 0;

VehiculeThread::VehiculeThread(bool* terminer, volatile bool* executer)
    : execution_(&VehiculeThread::demarrer_traitement,this, this)
{
    vehicules_ = std::list<Vehicule*>();
    toDelete = std::list<Vehicule*>();

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

            for (auto itt = vehicules_.begin(); itt != vehicules_.end(); ++itt)
            {
                //remove the vehicule from the simluation data
                Vehicule* v = *itt;
                if (v->Process() == false)
                {
                    SimulationData::GetInstance().RemoveVehicule(v);
                    toDelete.push_back(v);
                }
            }

            for (auto itt = toDelete.begin(); itt != toDelete.end(); ++itt)
            {
                //remove the vehicule from the vehicule thread
                Vehicule *v = *itt;
                vehicules_.remove(v);
            }

            /*std::for_each(vt->vehicules_.begin(), vt->vehicules_.end(), [](Vehicule* v){
                if(v->Process() == false)   //i.e. le véhicule est arrivé à destination
                {
                    SimulationData::GetInstance().RemoveVehicule(v);
                }
            });*/
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
