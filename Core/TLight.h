#ifndef STOPSIGN_H
#define STOPSIGN_H

#include <map>
#include <vector>
#include "simulationtraits.h"
#include "vehicle.h"
#include "node.h"

class TLight: public Node
{
    using road_id_type = typename simulation_traits::road_id_type;
    int currentWaitingVehicleIndex;

    std::map<road_id_type,road_id_type> parallelRoads;
    int lightDelay, currentLight;

    static std::mutex mtx;
public:
    TLight(){}
    TLight(GLfloat x, GLfloat y);
    TLight(GLfloat x, GLfloat y, node_id_type id, bool isSource);
    TLight(GLfloat x, GLfloat y, node_id_type id, bool isSource, DistributionInfo distributionInfo);

    void processWaitingVehicles();
};

#endif // STOPSIGN_H
