#ifndef LANE_H
#define LANE_H

#include "node.h"
#include "formula.h"
#include "simulationtraits.h"
#include <vector>
#include <set>

class Vehicle; //forward declaration

class Lane
{
public:
    using road_id_type = typename simulation_traits::road_id_type;
    using node_id_type = typename simulation_traits::node_id_type;
private:
    std::mutex mtx;

    Node& start_;
    Node& end_;

    int nbChar;
    int nbCharTotal;
    int laneId_;

    std::list<Vehicle*> vehicles;

    road_id_type parent_;

    Formula lineFormula;
public:
    Lane();
    Lane(Node&, Node&, road_id_type parent, int laneNumber, int laneId);

    Node& getStartNode();
    Node& getEndNode();

    road_id_type getRoadId();

    void addVehicleToLane(Vehicle *vehicle);
    void removeVehicleFromLane(Vehicle *vehicle);
    void laneUnblocked(node_id_type nodeID);

    int getNumberOfVehicle();
    int getTotalNumberOfVehicle();
    int getLaneId();

    bool getVehicleInFront(Vehicle* v, float* x, float* y);
    float getLastVehiclePos();

    Formula& getLineFormula();
    GLfloat getCoordinate(int which);
};

#endif // VOIE_H
