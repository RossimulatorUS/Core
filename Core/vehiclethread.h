#ifndef VEHICULETHREAD_H
#define VEHICULETHREAD_H

#include <thread>
#include <vector>

#include "module.h"
#include "vehicle.h"

class VehicleThread : public Module
{
    // Materiel
    std::list<Vehicle*> vehicles_;
    std::list<Vehicle*> toDelete;
    std::thread execution_;
    bool terminated;
    static unsigned int id_to_date_;
    unsigned int id_;

    // Fonction d'initialisation
    void start_process(VehicleThread *vt);

public:
     VehicleThread(bool *terminate, volatile bool *execute);
     void add_vehicle(Vehicle*);
     std::list<Vehicle*>::size_type nb_vehicles() const;
     void terminate();
};

#endif // VEHICULETHREAD_H
