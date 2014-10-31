#include "lane.h"
#include "vehicle.h"
#include "autolock.h"
#include <QDebug>
#include <iostream>


Lane::Lane(Node& start, Node& end, road_id_type parent, int laneNumber)
    :start_(start), end_(end), parent_(parent)
{

    //vehicleProgressionOrder = std::map<float, Vehicle*>();
    vehicles = std::list<Vehicle*>();
    nbChar = 0;

    lineFormula = Formula(getStartNode(), getEndNode(), laneNumber);

    //start_ = Node( lineFormula.getLaneCoordinate(X1),  lineFormula.getLaneCoordinate(Y1));
    //end_ = Node( lineFormula.getLaneCoordinate(X2),  lineFormula.getLaneCoordinate(Y2));
}

void Lane::addVehicleToLane(Vehicle* vehicle)
{
    Autolock av(mtx);
    //vehicleProgressionOrder.insert(std::pair<float, Vehicle*>(vehicle->getProgress(), vehicle));
    vehicles.insert(vehicles.end(),vehicle);
    ++nbChar;
}

int Lane::getNumberOfVehicle()
{
    return nbChar;
}

void Lane::removeVehicleFromLane(Vehicle* v)
{
    Autolock av(mtx);

    vehicles.remove(v);
    --nbChar;
}

bool Lane::getVehicleInFront(Vehicle* v, float *x, float *y)
{
    Autolock av(mtx);

    bool b = false;

    std::list<Vehicle*>::iterator it = std::find(vehicles.begin(),vehicles.end(),v);

    if(it!=vehicles.begin())
    {
        it--;
        b=true;

        *x = (*it)->x_;
        *y = (*it)->y_;
    }

    return b;
}

float Lane::getLastVehiclePos()
{
    float tmp = 100.0f;

    std::list<Vehicle*>::iterator it = vehicles.end();
    if(vehicles.end()!=vehicles.begin())
    {
        it--;
        tmp = distance((*it)->x_,(*it)->y_,start_.x(),start_.y());
    }

    return tmp;
}

Node& Lane::getStartNode()
{
    return start_;
}

Node& Lane::getEndNode()
{
    return end_;
}

Formula& Lane::getLineFormula()
{
    return lineFormula;
}

simulation_traits::road_id_type Lane::getRoadId()
{
    return parent_;
}

void Lane::laneUnblocked(node_id_type nodeID)
{
    if((vehicles.begin() != vehicles.end()) && (nodeID == end_.GetId()))
        vehicles.front()->intersectionGo();
}
