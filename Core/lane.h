#ifndef LANE_H
#define LANE_H

#include "node.h"
#include "formula.h"
#include "simulationtraits.h"

class Lane
{
public:
    using road_id_type = typename simulation_traits::road_id_type;
private:
    Node start_;
    Node end_;

    road_id_type parent_;

    Formula lineFormula;
public:
    Lane();
    Lane(Node, Node, road_id_type parent, int laneNumber);

    Node getStartNode();
    Node getEndNode();

    Formula getLineFormula();
};

#endif // VOIE_H
