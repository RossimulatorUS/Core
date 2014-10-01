#ifndef DISTRIBUTOR_H
#define DISTRIBUTOR_H

#include <atomic>
#include <vector>

#include "execution_history.h"
#include "module.h"
#include "vehicle.h"
#include "vehiclethread.h"

class Distributor : public Module
{
    std::vector<Node> nodes_;

    std::list<Vehicle*>* all_vehicles_;

    // Vehicules en attente d'etre distribues
    std::vector<Vehicle*> vehicles_;

    // Threads du cortex qui sont utilisables pour calcul des deplacements
    std::vector<VehicleThread*>* threads_;

    // Controle du temps d'execution
    Execution_history history_;

    void init();

    // ALGORITHME IMPORTANT
    unsigned int chose_thread();

public:
    Distributor(std::vector<VehicleThread *> *, bool*, volatile bool*, std::vector<Node> nodes, std::list<Vehicle*>* all_vehicles_);
    void add_vehicle(Vehicle *);
};

#endif // DISTRIBUTOR_H
