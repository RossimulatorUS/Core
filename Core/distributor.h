#ifndef DISTRIBUTOR_H
#define DISTRIBUTOR_H

#include <list>
#include <map>
#include <vector>

#include "module.h"
#include "road_segment.h"
#include "vehicle.h"
#include "vehiclethread.h"

class Distributor : public Module
{
    using road_id_type = typename simulation_traits::road_id_type;

    std::vector<Node*> nodes_;

    std::list<Vehicle*>* all_vehicles_;

    // Vehicules en attente d'etre distribues
    std::vector<Vehicle*> vehicles_;

    std::map<road_id_type,std::vector<Vehicle*>> waitingVehicles;

    // Threads du cortex qui sont utilisables pour calcul des deplacements
    std::vector<VehicleThread*>* threads_;

    void init();

    // ALGORITHME IMPORTANT
    unsigned int chose_thread();

public:
    Distributor(std::vector<VehicleThread *> *, volatile bool*, std::vector<Node*> nodes, std::list<Vehicle*>* all_vehicles_);
    void add_vehicle(Vehicle *);
};

#endif // DISTRIBUTOR_H
