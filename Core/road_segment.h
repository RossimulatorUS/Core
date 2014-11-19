#ifndef ROAD_H
#define ROAD_H

#include "formula.h"

#include <QGLWidget>
#include <utility>
#include <vector>
#include <QTime>

#include "dvutility.h"
#include "node.h"
#include "lane.h"

using std::vector;
using std::pair;

class Node;

class RoadSegment
{
public:
    using node_id_type = typename simulation_traits::node_id_type;
    using road_id_type = typename simulation_traits::road_id_type;
    using road_cost_type = typename simulation_traits::road_cost_type;

private:
    std::string roadName_;

    vector<Lane*> lanes_;

    Formula lineFormula;

    int actualNumberOfCar;
    int totalNumberOfCar;
    int numberWaitingCars;
    
    bool isReadyToCreate_;
    bool isLeftToRight_;
    bool isOneWay_;

public:
    RoadSegment(node_id_type startID, node_id_type EndID, bool isOneWay, int laneNumber, std::string name);
    RoadSegment();

    node_id_type startID_;
    node_id_type endID_;

    void setNumberWaitingCars(int howMany);
    int getWaitingCars();

    std::string getRoadName();

    road_id_type roadID_;

    Node& getStartNode();
    Node& getEndNode();

    bool isReadyToCreate();
    bool isInSameDirection(Node startRoad, Node endRoad, Node startClick, Node endClick);
    bool isParallel(Node startRoad, Node endRoad, Node startClick, Node endClick);
    bool isLeftToRight(Node node1, Node node2);
    bool isLeftToRight();
    bool isBlocked_;

    void BlockRoad();
    void UnBlockRoad();

    int GetActualNumberOfCar();
    int GetTotalNumberOfCar();
    road_cost_type cost_;

    Lane* findAssociatedLane(Node, Node);

    Formula& getLineFormula();
    road_cost_type cost();

    void addLane(Node&, Node&, int laneNumber, int laneId);
    void allLanesUnblocked(node_id_type nodeID);

    std::vector<Lane*>& getLanes();

    road_id_type getRoadID();
};

#endif // ROUTE_H
