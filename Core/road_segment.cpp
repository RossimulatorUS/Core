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

    while(true) //TODO: (maybe) this should return the lane with the least cars
    {
        auto randLaneNumber = (rand() % (lanes_.size()) + 0);

        if (isInSameDirection(lanes_[randLaneNumber]->getStartNode(), lanes_[randLaneNumber]->getEndNode(), start, end))
        {
            return lanes_[randLaneNumber];
        }
    }

    /*for (unsigned int i = 0; i < lanes_.size(); ++i)
    {
        if (IsInSameDirection(lanes_[i].getNodeDepart(), lanes_[i].getNodeArrivee(), depart, arrivee))
        {
            //qDebug() << "voie.size = " << lanes_.size() << " " << i;
            return lanes_[i];
        }
    }*/
    return 0;
}

RoadSegment::RoadSegment(node_id_type startID, node_id_type endID, bool isOneWay, int laneNumber)
    :startID_(startID), endID_(endID), isReadyToCreate_(true), lanes_(std::vector<Lane*>())
{
    isOneWay_ = isOneWay;
    isLeftToRight_ = isLeftToRight(getStartNode(), getEndNode());
    lineFormula = Formula(getStartNode(), getEndNode(), laneNumber);
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

void RoadSegment::addLane(Node& node1, Node& node2, int laneNumber) //could remove node1 and node2
{
    Lane* lane = new Lane(node1, node2, getRoadID(), laneNumber); //and replace them with getStartNode(), getEndNode()
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
