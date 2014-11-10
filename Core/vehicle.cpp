#include "vehicle.h"
#include "simulationdata.h"
#include "qdebug.h"
#include "math.h"
#include "autolock.h"
#include <algorithm>
#include<iostream>

//std::mutex Vehicle::mtx;

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
     currentRoad_(getStartNode().getNextRoad(end)),
     readyToSwitch(false)
{
    Autolock av(mtx);

    currentLane_ = getCurrentRoad().findAssociatedLane(getStartNode(), getEndNode());
    //currentLane_->addVehicleToLane(this);

    // Retouner id et incrementer ensuite
    id_ = id_to_date_++;

    x_ = currentLane_->getLineFormula().getLaneCoordinate(X1);
    y_ = currentLane_->getLineFormula().getLaneCoordinate(Y1);

    xVariation_ = actualSpeed_ * currentLane_->getLineFormula().getVariationX();
    yVariation_ = actualSpeed_ * currentLane_->getLineFormula().getVariationY();
}

void Vehicle::resetLane()
{
    currentLane_ = getCurrentRoad().findAssociatedLane(getStartNode(), getEndNode());
    x_ = currentLane_->getLineFormula().getLaneCoordinate(X1);
    y_ = currentLane_->getLineFormula().getLaneCoordinate(Y1);
}

bool Vehicle::addToLane()
{
    if (currentLane_->getStartNode().isNodeBlocked() && currentLane_->getEndNode().isNodeBlocked())
    {
        qDebug() << "BLOCKED";
        return false;
    }

    currentLane_->addVehicleToLane(this);
    return true;
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

Node& Vehicle::getStartNode()
{
    return SimulationData::getInstance().getNode(startNode_);
}

Node& Vehicle::getEndNode()
{
    return SimulationData::getInstance().getNode(endNode_);
}

RoadSegment& Vehicle::getCurrentRoad()
{
    return SimulationData::getInstance().getRoad(currentRoad_);
}

RoadSegment::road_id_type Vehicle::getCurrentRoadId()
{
    return currentRoad_;
}

RoadSegment::road_id_type Vehicle::getNextRoadID()
{
    return getNextStep().GetId();
}

Lane* Vehicle::getCurrentLane()
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
    /*if (currentLane_->getNumberOfVehicle() - 1 == getPositionInLane())
        return false;
    else*/
        return true;
}

///checks if there is a car in front of this
bool Vehicle::isCarInFront()
{
    /*if (getPositionInLane() == 0)
        return false;
    else*/
        return true;
}


Vehicle* Vehicle::getVehicleBehind()
{
    return 0;//currentLane_->getVehicleBehind(progress_);
}

Vehicle* Vehicle::getVehicleInFront()
{
    return 0;//currentLane_->getVehicleInFront(progress_);
}

bool Vehicle::getVehicleInFront(float* x, float* y)
{
    return currentLane_->getVehicleInFront(this, x, y);
}

bool Vehicle::process()
{
    if(isWaiting)
        return true;

    auto nextX = x_ + xVariation_;
    auto nextY = y_ + yVariation_;

    if(distance(nextX, nextY, getImmediateX(), getImmediateY()) > pyth(xVariation_, yVariation_)/2)
    {
        float x,y;

        if(getVehicleInFront(&x,&y))
        {
            auto breathingRoom = 16;
            if(distance(x, y, x_, y_) < pyth(xVariation_, yVariation_)/2*breathingRoom)
            {
                return true;
            }
        }
        advance();
        return true;
    }
    else
    {
        if(isOnLastStretch())
        {
            //isWaiting = true;
            y_ = x_ = 1000000.0f;
            currentLane_->removeVehicleFromLane(this);
            return false;
        }
        advance();
        isWaiting = true;
        auto& node = getNextStep();
        node.addToWaitingRoads(currentRoad_);
        return true;
    }
}

void Vehicle::intersectionGo()
{
    if(isWaiting)
    {
        switchRoad();
        isWaiting = false;
    }
}

bool Vehicle::isOnLastStretch()
{
    return getNextStep().GetId() == endNode_;
}

float Vehicle::getProgress()
{
    return progress_;
}

void Vehicle::advance()
{
    Autolock av(mtx);
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

    x_ = x_ + xVariation_;
    y_ = y_ + yVariation_;

    evaluateProgress();
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
    auto oldProgress = progress_;

    auto laneLength = currentLane_->getLineFormula().getLength();
    auto distanceTraveled = distance(x_, y_, currentLane_->getStartNode().x(), currentLane_->getStartNode().y());

    progress_ = ((distanceTraveled / laneLength)*100.0f);
}

void Vehicle::switchRoad()
{
    //readyToSwitch = false;
    //std::cout<<"SWITCHING"<<std::endl;
    resetVehicleSpeed();

    //qDebug() << "---------------------------------------------------------";
    //qDebug() << "Actual road before switch " << getCurrentRoad().getRoadID();
    startNode_ = getNextStep().GetId();
    //qDebug() << "Next step : " << startNode_;

    currentRoad_ = chose_road(startNode_, endNode_);

    //qDebug() << "Actual road after switch " << currentRoad_;

    //qDebug() << "start Node {" << getStartNode().x() << "," << getStartNode().y() << "}" << " with id : " << getStartNode().GetId();
    //qDebug() << "ROAD end Node {" << getCurrentRoad().getStartNode().x() << "," << getCurrentRoad().getStartNode().y() << "}" << " with id : " << getCurrentRoad().getStartNode().GetId();
    //qDebug() << "Destination Node {" << getEndNode().x() << "," << getEndNode().y() << "}" << " with id : " << getEndNode().GetId();

    currentLane_->removeVehicleFromLane(this);

    //currentLane_ = getCurrentRoad().findAssociatedLane(getStartNode(), getEndNode());

    //usefull when blocking roads
    if (startNode_ == getCurrentRoad().getStartNode().GetId())
        currentLane_ = getCurrentRoad().findAssociatedLane(getStartNode(), getCurrentRoad().getEndNode());
    else
        currentLane_ = getCurrentRoad().findAssociatedLane(getStartNode(), getCurrentRoad().getStartNode());

    currentLane_->addVehicleToLane(this);
    //qDebug() << "Found a lane";

    xVariation_ = actualSpeed_ * currentLane_->getLineFormula().getVariationX();
    yVariation_ = actualSpeed_ * currentLane_->getLineFormula().getVariationY();

    x_ = currentLane_->getLineFormula().getLaneCoordinate(X1);
    y_ = currentLane_->getLineFormula().getLaneCoordinate(Y1);

    progress_ = 0;
}

void Vehicle::resetVehicleSpeed()
{
    actualSpeed_ = baseSpeed_;
}

Node& Vehicle::getImmediateDestination()
{
    //Autolock av(mtx);
    return currentLane_->getEndNode();
}

GLfloat Vehicle::getImmediateX()
{
    return currentLane_->getLineFormula().getLaneCoordinate(X2);
}

GLfloat Vehicle::getImmediateY()
{
    return currentLane_->getLineFormula().getLaneCoordinate(Y2);
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
