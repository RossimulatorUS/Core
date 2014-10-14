#include <QDebug>

#include <algorithm>

#include "cortex.h"
#include "distributor.h"
#include "simulationdata.h"
#include <iostream>

Distributor::Distributor(std::vector<VehicleThread*>* threads, bool* terminate, volatile bool* execute, std::vector<Node> nodes, std::list<Vehicle*>* all_vehicles_)
    : threads_(threads),
      all_vehicles_(all_vehicles_)
{
    vehicles_ = std::vector<Vehicle*>();
    terminate_ = terminate;
    execute_ = execute;
    execution_ = std::thread(&Distributor::init, this);

    waitingVehicles = std::map<Road*,std::vector<Vehicle*>>();

    std::vector<Road>* allRoads = SimulationData::getInstance().getRoads();

    for(int i=0; i<allRoads->size();i++)
    {
        waitingVehicles.insert(std::pair<Road*,std::vector<Vehicle*>>(&(allRoads->at(i)),std::vector<Vehicle*>()));
    }

    nodes_.reserve(nodes.size() / 2);

    // On garde seulement les noeuds qui sont des sources
    for(auto i(std::begin(nodes)); i != std::end(nodes); ++i)
        if(i->is_source())
            nodes_.emplace_back(*i);
}

void Distributor::init()
{
    is_initialised_ = true;
    //Historique_dexecution::temps temps_initial;

    while(!(*terminate_))
    {
        // Attendre prochain tic
        if(*execute_)
        {
            *execute_ = false;

            // Demarrer chronometre
            //temps_initial = Historique_dexecution::get_time();

            std::for_each(nodes_.begin(), nodes_.end(), [&](Node& node){

                // Si le noeud est pret, ajouter un vehicule sur le reseau
                if(node.is_due())
                {
                    Vehicle* v = node.create_vehicle();

                    Road entry = v->getCurrentRoad(); //might want to make spawn limit node-based, rather than road-based
                    std::vector<QSharedPointer<Lane>> roadLanes = entry.getLanes();

                    float lastProgression = 100.0f;

                    for(int i=0; i<roadLanes.size(); i++) //change this when lanes are independant
                    {
                        float tmp = roadLanes[i]->getLastVehiclePos();
                        std::cout<<lastProgression<<" "<<tmp<<std::endl;
                        lastProgression = std::min(lastProgression,tmp);
                    }

                    if(lastProgression < 15.0f)
                    {
                        std::cout<<lastProgression<<std::endl;
                        waitingVehicles[(&entry)].push_back(v);
                    }
                    else
                    {
                        all_vehicles_->push_back(v);
                        threads_->at(chose_thread())->add_vehicle(v);
                        v->addToLane();
                    }
                }
            });
        }

        std::chrono::milliseconds timespan(1); // Max 20% de la plage perdu
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
