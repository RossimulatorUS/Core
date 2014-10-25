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

void Lane::addVehicleToLane(Vehicle* vehicle, float progress)
{
    Autolock av(mtx);
    //vehicleProgressionOrder.insert(std::pair<float, Vehicle*>(progress, vehicle));
    vehicles.insert(vehicles.end(),vehicle);
    ++nbChar;
}

int Lane::getNumberOfVehicle()
{
    return nbChar;
}

int Lane::getPositionOfVehicle(float progress)
{
    /*int position = vehicleProgressionOrder.size()-1;
    for (auto itt = vehicleProgressionOrder.begin(); itt != vehicleProgressionOrder.end(); ++itt)
    {
        float progressArray = itt->first;
        if (progress == progressArray)
        {
            return position;
        }
        --position;
    }*/
    return 0;
}

void Lane::updateProgress(float oldProgress, float newProgress)
{
    /*Autolock av(mtx);

    auto value = vehicleProgressionOrder.find(oldProgress);

    if (value != vehicleProgressionOrder.end())
    {
        //mtx.lock();
        vehicleProgressionOrder.erase(value);
        vehicleProgressionOrder.insert(std::pair<float, Vehicle*>(newProgress, value->second));
        //mtx.unlock();
    }*/
}

//always remove the first vehicle in the lane (dernier vehicle puisque it is sorted)
void Lane::removeVehicleFromLane(float progress)
{
    Autolock av(mtx);

    //auto value = vehicleProgressionOrder.find(progress);
    --nbChar;

    /*typedef std::map<float, Vehicle>::iterator mapIterator;
    mapIterator itemToRemove;
    for (auto itt = vehicleProgressionOrder.begin(); itt != vehicleProgressionOrder.end(); ++itt)
    {
        float progressArray = itt->first;
        qDebug() << progressArray;
        if (progressArray == progress)
        {
            itemToRemove = itt;
            break;
            //itt->first = newProgress;
        }
    }*/

    /*if (value != vehicleProgressionOrder.end())
    {
        //Vehicle* v = value->second;
        //vehicles.remove(v);
        vehicleProgressionOrder.erase(value);
    }*/
}

void Lane::removeVehicleFromLane(Vehicle* v)
{
    Autolock av(mtx);

    vehicles.remove(v);
    --nbChar;
}

///always use isCarBehind before calling this method
Vehicle* Lane::getVehicleBehind(float progress)
{
    Autolock av(mtx);

    Vehicle* v = 0;
    auto value = vehicleProgressionOrder.find(progress);
    if(value != vehicleProgressionOrder.begin())
    {
        auto carBehind = --value;
        v = carBehind->second;
    }

    return v;
}

///always use isCarInFront before calling this method
Vehicle* Lane::getVehicleInFront(float progress)
{
    Autolock av(mtx);

    Vehicle* v = 0;
    auto value = vehicleProgressionOrder.find(progress);
    auto frontCar = ++value;
    if(value != vehicleProgressionOrder.end())
    {
        v = frontCar->second;
    }

    return v;
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

void Lane::laneUnblocked()
{
    if(vehicles.begin() != vehicles.end())
        vehicles.front()->intersectionGo();
    /*if(vehicleProgressionOrder.size()>0)
    {
        std::map<float, Vehicle*>::iterator it = vehicleProgressionOrder.end();
        //do
        //{
        it--;
        it->second->intersectionGo();
    }*/
    //else
    //    std::cout<<"ERMAGERD"<<std::endl;
    //while(it!= vehicleProgressionOrder.begin());
}
