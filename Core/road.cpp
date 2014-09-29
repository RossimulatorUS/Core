#include "road.h"
#include "formula.h"
#include "qdebug.h"
#include "simulationdata.h"

Node Road::getStartNode()
{
    return SimulationData::getInstance().getNode(startID_);
}

Node Road::getEndNode()
{
    return SimulationData::getInstance().getNode(endID_);
}

bool Road::isReadyToCreate()
{
    return isReadyToCreate_;
}

//comparer avec des coordonnees
bool Road::isInSameDirection(Node startRoad, Node endRoad, Node startClick, Node endClick)
{
    return lineFormula.isInSameDirection(startRoad, endRoad, startClick, endClick);
}

bool Road::isLeftToRight(Node Node1, Node Node2)
{
    return lineFormula.isLeftToRight(Node1, Node2);
}

bool Road::isLeftToRight()
{
    return isLeftToRight_;
}

QSharedPointer<Lane> Road::findAssociatedLane(Node start, Node end)
{
    QTime time = QTime::currentTime();
    srand((uint)time.msec());

    while(true)
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
    return QSharedPointer<Lane>();
}

Road::Road(node_id_type startID, node_id_type endID, bool isOneWay, int laneNumber)
    :startID_(startID), endID_(endID), isReadyToCreate_(true), lanes_(std::vector<QSharedPointer<Lane>>())
{
    isOneWay_ = isOneWay;
    isLeftToRight_ = isLeftToRight(getStartNode(), getEndNode());
    lineFormula = Formula(getStartNode(), getEndNode(), laneNumber);
}

Road::Road()
    :isReadyToCreate_(false)
{}

Formula Road::getLineFormula()
{
    return lineFormula;
}

Road::road_cost_type Road::cost()
{
    return lineFormula.getLength();
}

void Road::addLane(Node node1, Node node2, int laneNumber)
{
    QSharedPointer<Lane> lane = QSharedPointer<Lane>(new Lane(node1, node2, getRoadID(), laneNumber));
    lanes_.push_back(lane);
}

Road::road_id_type Road::getRoadID()
{
    return SimulationData::getInstance().getNode(startID_).getNextRoad(endID_);
}

std::vector<QSharedPointer<Lane>> Road::getLanes()
{
    return lanes_;
}
