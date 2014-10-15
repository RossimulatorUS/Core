#include "lane.h"
#include "vehicle.h"
#include "autolock.h"
#include <QDebug>

std::mutex Lane::mtx;

Lane::Lane(Node start, Node end, road_id_type parent, int laneNumber)
    :start_(start), end_(end), parent_(parent)
{
    vehicleProgressionOrder = std::map<float, Vehicle*>();
    nbChar = 0;

    lineFormula = Formula(getStartNode(), getEndNode(), laneNumber);

    start_ = Node( lineFormula.getLaneCoordinate(X1),  lineFormula.getLaneCoordinate(Y1));
    end_ = Node( lineFormula.getLaneCoordinate(X2),  lineFormula.getLaneCoordinate(Y2));
}

Lane::Lane()
{}

void Lane::addVehicleToLane(Vehicle* vehicle)
{
    Autolock av(mtx);
    vehicleProgressionOrder.insert(std::pair<float, Vehicle*>(vehicle->getProgress(), vehicle));
    ++nbChar;
}

void Lane::addVehicleToLane(Vehicle* vehicle, float progress)
{
    Autolock av(mtx);
    vehicleProgressionOrder.insert(std::pair<float, Vehicle*>(progress, vehicle));
    ++nbChar;
}

int Lane::getNumberOfVehicle()
{
    return vehicleProgressionOrder.size();
}

int Lane::getPositionOfVehicle(float progress)
{
    int position = vehicleProgressionOrder.size()-1;
    for (auto itt = vehicleProgressionOrder.begin(); itt != vehicleProgressionOrder.end(); ++itt)
    {
        float progressArray = itt->first;
        if (progress == progressArray)
        {
            return position;
        }
        --position;
    }
}

void Lane::updateProgress(float oldProgress, float newProgress)
{
    auto value = vehicleProgressionOrder.find(oldProgress);

    if (value != vehicleProgressionOrder.end())
    {
        //mtx.lock();
        vehicleProgressionOrder.erase(value);
        vehicleProgressionOrder.insert(std::pair<float, Vehicle*>(newProgress, value->second));
        //mtx.unlock();
    }
}

//always remove the first vehicle in the lane (dernier vehicle puisque it is sorted)
void Lane::removeVehicleFromLane(float progress)
{
    auto value = vehicleProgressionOrder.find(progress);
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

    if (value != vehicleProgressionOrder.end())
    {
        vehicleProgressionOrder.erase(value);
    }
}

///always use isCarBehind before calling this method
Vehicle* Lane::getVehicleBehind(float progress)
{
    auto value = vehicleProgressionOrder.find(progress);
    auto carBehind = --value;

    return carBehind->second;
}

///always use isCarInFront before calling this method
Vehicle* Lane::getVehicleInFront(float progress)
{
    auto value = vehicleProgressionOrder.find(progress);
    auto frontCar = ++value;

    return frontCar->second;
}

float Lane::getLastVehiclePos()
{
    float pos = 100.0f;
    if(vehicleProgressionOrder.size()!=0)
        pos = vehicleProgressionOrder.begin()->first;
    return pos;
}

Node Lane::getStartNode()
{
    return start_;
}

Node Lane::getEndNode()
{
    return end_;
}

Formula Lane::getLineFormula()
{
    return lineFormula;
}

simulation_traits::road_id_type Lane::getRoadId()
{
    return parent_;
}
