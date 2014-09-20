#include <QDebug>

#include <algorithm>

#include "cortex.h"
#include "distributor.h"

Distributor::Distributor(std::vector<VehicleThread*>* threads, bool* terminate, volatile bool* execute)
    : threads_(threads)
{
    vehicles_ = std::vector<Vehicle*>();
    terminate_ = terminate;
    execute_ = execute;
    execution_ = std::thread(&Distributor::init, this);
}

void Distributor::init()
{
    is_initialised_ = true;
    //Historique_dexecution::temps temps_initial;

    while(!(*terminate_))
    {
        if(*execute_)
        {
            *execute_ = false;

            // Demarrer chronometre
            //temps_initial = Historique_dexecution::get_time();

            // Qte vehicules a placer pour ce tic
            auto qty_vehicles(vehicles_.size());

            for(unsigned int i(0); i < qty_vehicles; ++i)
            {
                threads_->at(chose_thread())->add_vehicle(vehicles_[0]);
                vehicles_.erase(begin(vehicles_));
            }

            // Arreter chronometre
            //historique_.ajouter_temps(Historique_dexecution::get_time() - temps_initial);
        }
        std::chrono::milliseconds timespan(1); // Max 20% du temps de perdu
        std::this_thread::sleep_for(timespan);
    }
}

// ALGORITHME IMPORTANT
unsigned int Distributor::chose_thread()
{
    // Retourne l'iterateur du thread le moins occupe - le debut du vector, donc sa position
    return std::min_element(threads_->begin(), threads_->end(),
                            [](VehicleThread* a, VehicleThread* b){
                                return a->nb_vehicles() < b->nb_vehicles();
                            }) - threads_->begin();
}

void Distributor::add_vehicle(Vehicle* vehicle)
{
    vehicles_.push_back(vehicle);
}
