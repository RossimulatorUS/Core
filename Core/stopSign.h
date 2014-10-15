#ifndef STOPSIGN_H
#define STOPSIGN_H

#include <map>
#include <vector>
#include "simulationtraits.h"
#include "vehicle.h"
#include "intersection.h"

class StopSign: public Intersection
{
    using road_id_type = typename simulation_traits::road_id_type;
    int currentWaitingVehicleIndex;
    std::map<Lane*, std::vector<Vehicle*>>* waitingVehicles_;

    std::mutex* mtx;

public:
    StopSign(){}
    StopSign(std::map<Lane*, std::vector<Vehicle*>>* waitingVehicles, std::mutex* mtx_);
    void processWaitingVehicles();
};

#endif // STOPSIGN_H
