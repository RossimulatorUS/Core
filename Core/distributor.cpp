#include <algorithm>

#include "distributor.h"
#include "simulationdata.h"

Distributor::Distributor(std::vector<VehicleThread*>* threads, volatile bool* execute, std::map<node_id_type,Node*> nodes, std::list<Vehicle*>* all_vehicles_)
    : all_vehicles_(all_vehicles_),
      vehicles_(std::vector<Vehicle*>()),
      threads_(threads)
{
    execute_ = execute;
    execution_ = std::thread(&Distributor::init, this);

    waitingVehicles = std::map<road_id_type,std::vector<Vehicle*>>();

    std::vector<RoadSegment> allRoads = SimulationData::getInstance().getRoads();

    for(size_t i(0); i<allRoads.size();i++)
    {
        waitingVehicles.insert(std::pair<road_id_type,std::vector<Vehicle*>>((allRoads.at(i)).getRoadID(),std::vector<Vehicle*>()));
    }

    //nodes_.reserve(nodes.size() / 2);

    // Keep only source nodes
    for(auto i(std::begin(nodes)); i != std::end(nodes); ++i)
        if((*i).second->is_source())
            nodes_.insert((*i));
}

void Distributor::init()
{
    is_initialised_ = true;

    while(!terminate_)
    {
        // Wait for next tic (from analyser)
        if(*execute_)
        {
            *execute_ = false;

            //Try to spawn unspawned vehicles
            for(std::map<road_id_type,std::vector<Vehicle*>>::iterator it = waitingVehicles.begin();
                it != waitingVehicles.end(); it++)
            {
                std::vector<Vehicle*>* vV = &(it->second);
                if(vV->size() > 0)
                {
                    Vehicle* v = vV->back();
                    v->resetLane();
                    Lane* entry = v->getCurrentLane();
                    float lastProgression = std::min(100.0f,entry->getLastVehiclePos());

                    if(lastProgression > 0.12f)
                    {
                        if (v->addToLane())
                        {
                            auto roadID = it->first;
                            all_vehicles_->push_back(v);
                            threads_->at(chose_thread())->add_vehicle(v);
                            vV->pop_back();
                            SimulationData::getInstance().getRoad(roadID).setNumberWaitingCars(vV->size());
                        }
                    }
                }
            }

            std::for_each(nodes_.begin(), nodes_.end(), [&](std::pair<node_id_type,Node*> it){

                Node* node = it.second;
                // Si le noeud est pret, ajouter un vehicule sur le reseau
                if(node->is_due())
                {
                    Vehicle* v = node->create_vehicle();
                    Lane* entry = v->getCurrentLane();
                    auto roadID = entry->getRoadId();

                    float lastProgression = std::min(100.0f,entry->getLastVehiclePos());
<<<<<<< HEAD
=======

>>>>>>> bf4cdb3f5a51cae3903cb083f5e3edb675d3ad87
                    if(lastProgression < 0.12f)
                    {
                        waitingVehicles[roadID].push_back(v);
                        SimulationData::getInstance().getRoad(roadID).setNumberWaitingCars(waitingVehicles[roadID].size());
                    }
                    else
                    {
                        if (v->addToLane())
                        {
                            all_vehicles_->push_back(v);
                            threads_->at(chose_thread())->add_vehicle(v);
                        }
                    }
                }
            });
        }

        std::chrono::milliseconds timespan(1); // Max 20% de la plage perdu
        std::this_thread::sleep_for(timespan); //THIS HERE ALMOST CERTAINLY DOES NOT WORK AS PLANNED. CPU CLOCK PRECISION IS 16ms, SAYING SLEEP(1) SLEEPS FOR 16
    }
}

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
