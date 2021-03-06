#include "lane.h"
#include "vehicle.h"
#include "autolock.h"
#include <QDebug>
#include <iostream>


Lane::Lane(Node& start, Node& end, road_id_type parent, int laneNumber, int laneId)
    :start_(start), end_(end), parent_(parent)
{
    vehicles = std::list<Vehicle*>();
    nbChar = 0;
    nbCharTotal = 0;
    laneId_ = laneId;

    lineFormula = Formula(getStartNode(), getEndNode(), laneNumber);
}

void Lane::addVehicleToLane(Vehicle* vehicle)
{
    Autolock av(mtx);
    vehicles.insert(vehicles.end(),vehicle);
    ++nbChar;
    ++nbCharTotal;
}

int Lane::getNumberOfVehicle()
{
    return nbChar;
}

int Lane::getTotalNumberOfVehicle()
{
    return nbCharTotal;
}

int Lane::getLaneId()
{
    return laneId_;
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
        tmp = distance((*it)->x_,(*it)->y_,getLineFormula().getLaneCoordinate(X1),getLineFormula().getLaneCoordinate(Y1));
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
    {

        vehicles.front()->intersectionGo();
    }

}
