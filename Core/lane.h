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
private:
    static std::mutex mtx;

    Node start_;
    Node end_;

    int nbChar;

    std::map<float, Vehicle*> vehicleProgressionOrder;

    road_id_type parent_;

    Formula lineFormula;
public:
    Lane();
    Lane(Node, Node, road_id_type parent, int laneNumber);

    Node getStartNode();
    Node getEndNode();

    road_id_type getRoadId();

    void addVehicleToLane(Vehicle *vehicle);
    void addVehicleToLane(Vehicle *vehicle, float progress);
    void removeVehicleFromLane(float progress);
    void updateProgress(float oldProgress, float newProgress);

    int getNumberOfVehicle();
    int getPositionOfVehicle(float progress);

    Vehicle *getVehicleInFront(float progress);
    Vehicle *getVehicleBehind(float progress);
    float getLastVehiclePos();

    Formula getLineFormula();
};

#endif // VOIE_H
