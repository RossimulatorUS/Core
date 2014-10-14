#include "vehicle.h"
#include "simulationdata.h"
#include "qdebug.h"
#include "math.h"
#include "autolock.h"
#include <algorithm>

std::mutex Vehicle::mtx;

const float Vehicle::maxSpeed_ = 0.02f;
const float Vehicle::accelerationRate_ = 0.0001f;
const float Vehicle::baseSpeed_=0.01f;
const float Vehicle::decelerationRate_ = 2*Vehicle::accelerationRate_;

unsigned int Vehicle::id_to_date_ = 0;

Vehicle::Vehicle()
{
    // Retouner id et incrementer ensuite
    //id_ = id_to_date_++;
}

Vehicle::Vehicle(node_id_type start, node_id_type end)
    :startNode_(start),
     endNode_(end),
     isWaiting(false),
     actualSpeed_(baseSpeed_),
     isAccelerating_(true),
     isDecelerating_(false),
     progress_(0),
     currentRoad_(getStartNode().getNextRoad(end))
{
    Autolock av(mtx);

    currentLane_ = getCurrentRoad().findAssociatedLane(getStartNode(), getEndNode());
    //currentLane_->addVehicleToLane(this);

    // Retouner id et incrementer ensuite
    id_ = id_to_date_++;

    x_ = currentLane_->getStartNode().x();
    y_ = currentLane_->getStartNode().y();

    xVariation_ = actualSpeed_ * currentLane_->getLineFormula().getVariationX();
    yVariation_ = actualSpeed_ * currentLane_->getLineFormula().getVariationY();
}

void Vehicle::addToLane()
{
    currentLane_->addVehicleToLane(this);
}

void Vehicle::printNodeCoordinates(Node start, Node end)
{
    qDebug() << "depart : " << start.x() << ", " << start.y() << endl <<
                "arrivee: " << end.x() << ", " << end.y() << endl;
}

unsigned int Vehicle::id() const
{
    return id_;
}

float Vehicle::getSpeed()
{
    return actualSpeed_;
}

Node Vehicle::getStartNode()
{
    return SimulationData::getInstance().getNode(startNode_);
}

Node Vehicle::getEndNode()
{
    return SimulationData::getInstance().getNode(endNode_);
}

Road& Vehicle::getCurrentRoad()
{
    return SimulationData::getInstance().getRoad(currentRoad_);
}

Road::road_id_type Vehicle::getCurrentRoadId()
{
    return currentRoad_;
}

Road::road_id_type Vehicle::getNextRoadID()
{
    return getNextStep().GetId();
}

QSharedPointer<Lane> Vehicle::getCurrentLane()
{
    Autolock av(mtx);
    return currentLane_;
}

float pyth(float a, float b)
{
    return std::sqrt(std::pow(a,2) + std::pow(b,2));
}

float distance(float x1, float y1, float x2, float y2)
{
    return pyth(x1-x2, y1-y2);
}

///checks if there is a car behind this
bool Vehicle::isCarBehind()
{
    if (currentLane_->getNumberOfVehicle() - 1 == getPositionInLane())
        return false;
    else
        return true;
}

///checks if there is a car in front of this
bool Vehicle::isCarInFront()
{
    if (getPositionInLane() == 0)
        return false;
    else
        return true;
}


Vehicle* Vehicle::getVehicleBehind()
{
    return currentLane_->getVehicleBehind(progress_);
}

Vehicle* Vehicle::getVehicleInFront()
{
    return currentLane_->getVehicleInFront(progress_);
}

bool Vehicle::process()
{
    if(isWaiting)
        return true;

    auto nextX = x_ + xVariation_;
    auto nextY = y_ + yVariation_;

    if(distance(nextX, nextY, getImmediateDestination().x(), getImmediateDestination().y()) > pyth(xVariation_, yVariation_)/2)
    {
        auto waitingVehicles = getNextStep().getWaitingVehicles(currentRoad_);
        for(auto itt = waitingVehicles.begin(); itt != waitingVehicles.end(); ++itt)
        {
            Vehicle* v = *itt;
            auto breathingRoom = 16;
            if(distance(v->x_, v->y_, x_, y_) < pyth(xVariation_, yVariation_)/2*breathingRoom)
            {
                isWaiting = true;
                auto& node = getNextStep();
                node.addToWaitingVehicles(this);
                return true;
            }
        };
        advance();
        return true;
    }
    else
    {
        if(isOnLastStretch())
        {
            isWaiting = true;
            currentLane_->removeVehicleFromLane(progress_);
            return false;
        }
        advance();
        isWaiting = true;
        auto& node = getNextStep();
        node.addToWaitingVehicles(this);
        return true;
    }
}

void Vehicle::intersectionGo()
{
    if(distance(x_, y_, getImmediateDestination().x(), getImmediateDestination().y()) < pyth(xVariation_, yVariation_)/2)
    {
        switchRoad();
    }
    isWaiting = false;

}

bool Vehicle::isOnLastStretch()
{
    return getNextStep().GetId() == endNode_;
}

float Vehicle::getProgress()
{
    return progress_;
}

///Returns the index of the vehicle in the lane array
int Vehicle::getPositionInLane()
{
    return currentLane_->getPositionOfVehicle(progress_);
}

void Vehicle::advance()
{
    //auto breathingRoom = 40;
    //Vehicle* carInFront = currentLane_.getWaitingVehicle(this);

    /*if(distance(carInFront->x_, carInFront->y_, x_, y_) < pyth(xVariation_, yVariation_)/2*breathingRoom)
    {
        isDecelerating_ = true;
        isAccelerating_ = false;
        decelerateVehicle();
    }
    else
    {*/
        //isDecelerating_ = false;
        //isAccelerating_ = true;
        //accelerateVehicle();
    //}

    evaluateProgress();

    x_ = x_ + xVariation_;
    y_ = y_ + yVariation_;
}

void Vehicle::decelerateVehicle()
{
    /*if (actualSpeed_ >= baseSpeed_)
    {
        actualSpeed_ = actualSpeed_ - decelerationRate_;

        xVariation_ = actualSpeed_ * getCurrentLane()->getLineFormula().getVariationX();
        yVariation_ = actualSpeed_ * getCurrentLane()->getLineFormula().getVariationY();
    }*/
}

void Vehicle::accelerateVehicle()
{
    /*if (actualSpeed_ <= maxSpeed_)
    {
        actualSpeed_ = actualSpeed_+ accelerationRate_;

        xVariation_ = actualSpeed_ * getCurrentLane()->getLineFormula().getVariationX();
        yVariation_ = actualSpeed_ * getCurrentLane()->getLineFormula().getVariationY();
    }*/
}

void Vehicle::evaluateProgress()
{
    Autolock av(mtx);
    auto oldProgress = progress_;

    auto laneLength = currentLane_->getLineFormula().getLength();
    auto distanceLeft = distance(x_, y_, currentLane_->getEndNode().x(), currentLane_->getEndNode().y());

    auto distanceTraveled = laneLength - distanceLeft;

    progress_ = ((distanceTraveled / laneLength)*100);
    currentLane_->updateProgress(oldProgress, progress_);
}

void Vehicle::switchRoad()
{
    //Autolock av(mtx);
    resetVehicleSpeed();

    startNode_ = getNextStep().GetId();

    currentRoad_ = chose_road(startNode_, endNode_);

    currentLane_->removeVehicleFromLane(progress_);
    currentLane_ = getCurrentRoad().findAssociatedLane(getStartNode(), getEndNode());
    currentLane_->addVehicleToLane(this, 0);

    xVariation_ = actualSpeed_ * currentLane_->getLineFormula().getVariationX();
    yVariation_ = actualSpeed_ * currentLane_->getLineFormula().getVariationY();

    x_ = currentLane_->getStartNode().x();
    y_ = currentLane_->getStartNode().y();

    progress_ = 0;
}

void Vehicle::resetVehicleSpeed()
{
    actualSpeed_ = baseSpeed_;
}

Node Vehicle::getImmediateDestination()
{
    //Autolock av(mtx);
    return getCurrentLane()->getEndNode();
}

Node& Vehicle::getNextStep()
{
    auto start = SimulationData::getInstance().getNode(startNode_);
    auto endID = SimulationData::getInstance().getNode(endNode_).GetId();
    auto idNextStep = start.getNextStep(endID);
    return SimulationData::getInstance().getNode(idNextStep);
}

// Algorithme important
///Depart est le noeud actuel ; arrivee est la destination finale
Vehicle::road_id_type Vehicle::chose_road(node_id_type start, node_id_type end)
{
    return SimulationData::getInstance().getNode(start).getNextRoad(end);
}
