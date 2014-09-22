#include "vehicle.h"
#include "simulationdata.h"
#include "qdebug.h"
#include "math.h"
#include <algorithm>

const float Vehicle::baseSpeed_ = 0.01f;
unsigned int Vehicle::id_to_date_ = 0;

Vehicle::Vehicle()
{
    // Retouner id et incrementer ensuite
    id_ = id_to_date_++;
}

Vehicle::Vehicle(node_id_type start, node_id_type end)
    :startNode_(start),
     endNode_(end),
     isWaiting(false),
     currentRoad_(getStartNode().getNextRoad(end))
{
    currentLane_ = getCurrentRoad().findAssociatedLane(getStartNode(), getEndNode());

    // Retouner id et incrementer ensuite    
    id_ = id_to_date_++;

    x_ = currentLane_.getStartNode().x();
    y_ = currentLane_.getStartNode().y();

    /*x_ = GetNoeudDepart().x();
    y_ = GetNoeudDepart().y();*/

    xVariation_ = baseSpeed_ * getCurrentLane().getLineFormula().getVariationX();
    yVariation_ = baseSpeed_ * getCurrentLane().getLineFormula().getVariationY();
    //qDebug() << "VEHICULE HAS SPAWNED! GOING FROM " << depart << " TO " << arrive << " VIA ROAD " << actualRoad_;
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

Node Vehicle::getStartNode()
{
    return SimulationData::getInstance().getNode(startNode_);
}

Node Vehicle::getEndNode()
{
    return SimulationData::getInstance().getNode(endNode_);
}

Road Vehicle::getCurrentRoad()
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

Lane Vehicle::getCurrentLane()
{
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
            if(distance(v->x_, v->y_, x_, y_) < pyth(xVariation_, yVariation_)/2*16 ) //le *valeur est "breathing room"
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

void Vehicle::advance()
{
    x_ = x_ + xVariation_;
    y_ = y_ + yVariation_;
}

void Vehicle::switchRoad()
{
    startNode_ = getNextStep().GetId();

    currentRoad_ = chose_road(startNode_, endNode_);
    currentLane_ = getCurrentRoad().findAssociatedLane(getStartNode(), getEndNode());
    xVariation_ = baseSpeed_ * getCurrentLane().getLineFormula().getVariationX();
    yVariation_ = baseSpeed_ * getCurrentLane().getLineFormula().getVariationY();
    x_ = getCurrentLane().getStartNode().x();
    y_ = getCurrentLane().getStartNode().y();
}

Node Vehicle::getImmediateDestination()
{
    return getCurrentLane().getEndNode();
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
