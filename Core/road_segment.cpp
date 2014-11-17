#include "road_segment.h"
#include "formula.h"
#include "qdebug.h"
#include "simulationdata.h"
#include <iostream>

Node& RoadSegment::getStartNode()
{
    return SimulationData::getInstance().getNode(startID_);
}

Node& RoadSegment::getEndNode()
{
    return SimulationData::getInstance().getNode(endID_);
}

bool RoadSegment::isReadyToCreate()
{
    return isReadyToCreate_;
}

//comparer avec des coordonnees
bool RoadSegment::isInSameDirection(Node startRoad, Node endRoad, Node startClick, Node endClick)
{
    return lineFormula.isInSameDirection(startRoad, endRoad, startClick, endClick);
}

bool RoadSegment::isParallel(Node startRoad, Node endRoad, Node startClick, Node endClick)
{
    return lineFormula.isParallel(startRoad, endRoad, startClick, endClick);
}

bool RoadSegment::isLeftToRight(Node Node1, Node Node2)
{
    return lineFormula.isLeftToRight(Node1, Node2);
}

bool RoadSegment::isLeftToRight()
{
    return isLeftToRight_;
}

Lane* RoadSegment::findAssociatedLane(Node start, Node end)
{
    QTime time = QTime::currentTime();
    srand((uint)time.msec());
    int cpt = 0;

    while(true) //TODO: (maybe) this should return the lane with the least cars
    {
        auto randLaneNumber = (rand() % (lanes_.size()) + 0);

        //qDebug() << "Lanes get start node = " << lanes_[randLaneNumber]->getStartNode().GetId() << "Lanes get end node = " << lanes_[randLaneNumber]->getEndNode().GetId() << cpt;

        if (isInSameDirection(lanes_[randLaneNumber]->getStartNode(), lanes_[randLaneNumber]->getEndNode(), start, end))
        {
            return lanes_[randLaneNumber];
        }

        if (cpt > 10)
            qDebug() << "Perte de temps";

        ++cpt;
    }

    return 0;
}

RoadSegment::RoadSegment(node_id_type startID, node_id_type endID, bool isOneWay, int laneNumber, std::string name)
    :startID_(startID), endID_(endID), isReadyToCreate_(true), lanes_(std::vector<Lane*>())
{
    isOneWay_ = isOneWay;
    isLeftToRight_ = isLeftToRight(getStartNode(), getEndNode());
    lineFormula = Formula(getStartNode(), getEndNode(), laneNumber);
    actualNumberOfCar = 0;
    totalNumberOfCar = 0;
    cost_ = lineFormula.getLength();
    roadName_ = name;
    isBlocked_ = false;
}

RoadSegment::RoadSegment()
    :isReadyToCreate_(false)
{}

Formula& RoadSegment::getLineFormula()
{
    return lineFormula;
}

RoadSegment::road_cost_type RoadSegment::cost()
{
    return lineFormula.getLength();
}

void RoadSegment::addLane(Node& node1, Node& node2, int laneNumber, int laneId) //could remove node1 and node2
{
    Lane* lane = new Lane(node1, node2, getRoadID(), laneNumber, laneId); //and replace them with getStartNode(), getEndNode()
    lanes_.push_back(lane);
}

RoadSegment::road_id_type RoadSegment::getRoadID()
{
    return SimulationData::getInstance().getNode(startID_).getNextRoad(endID_);
}

std::vector<Lane*>& RoadSegment::getLanes()
{
    return lanes_;
}

void RoadSegment::allLanesUnblocked(node_id_type nodeID)
{
    for(int i = 0;i<lanes_.size();i++)
    {
        lanes_[i]->laneUnblocked(nodeID);
    }
}

std::string RoadSegment::getRoadName()
{
    return roadName_;
}

void RoadSegment::BlockRoad()
{
    getStartNode().setIsNodeBlocked(true);
    getEndNode().setIsNodeBlocked(true);
    isBlocked_ = true;
    cost_ = 999999;
    //qDebug() << "Blocking road : startNode = " << getStartNode().GetId() << " end node = " << getEndNode().GetId();
    getStartNode().updateCost(getEndNode().GetId(), cost_);
    getEndNode().updateCost(getStartNode().GetId(), cost_);
}

void RoadSegment::UnBlockRoad()
{
    getStartNode().setIsNodeBlocked(false);
    getEndNode().setIsNodeBlocked(false);
    isBlocked_ = false;
    cost_ = lineFormula.getLength();
    //qDebug() << "Blocking road : startNode = " << getStartNode().GetId() << " end node = " << getEndNode().GetId();
    getStartNode().updateCost(getEndNode().GetId(), cost_);
    getEndNode().updateCost(getStartNode().GetId(), cost_);
}

int RoadSegment::GetActualNumberOfCar()
{
    auto allLanes = getLanes();
    for (auto itt = allLanes.begin(); itt != allLanes.end(); ++itt)
    {
        actualNumberOfCar += (*itt)->getNumberOfVehicle();
    }
    return actualNumberOfCar;
}

int RoadSegment::GetTotalNumberOfCar()
{
    auto allLanes = getLanes();
    for (auto itt = allLanes.begin(); itt != allLanes.end(); ++itt)
    {
        totalNumberOfCar += (*itt)->getTotalNumberOfVehicle();
    }
    return totalNumberOfCar;
}
