#ifndef STOPSIGN_H
#define STOPSIGN_H

//#include <map>
//#include <vector>
#include "simulationtraits.h"
//#include "vehicle.h"
#include "node.h"

class StopSign: public Node
{
    //using road_id_type = typename simulation_traits::road_id_type;
public:
    StopSign(){}

    StopSign(GLfloat x, GLfloat y);
    StopSign(GLfloat x, GLfloat y, node_id_type id, bool isSource);
    StopSign(GLfloat x, GLfloat y, node_id_type id, bool isSource, DistributionInfo distributionInfo);
    void processWaitingVehicles();
};

#endif // STOPSIGN_H
