#include "lane.h"
#include <QDebug>

Lane::Lane(Node start, Node end, road_id_type parent, int laneNumber)
    :start_(start), end_(end), parent_(parent)
{
    lineFormula = Formula(getStartNode(), getEndNode(), laneNumber);

    start_ = Node( lineFormula.getLaneCoordinateX1(),  lineFormula.getLaneCoordinateY1());
    end_ = Node( lineFormula.getLaneCoordinateX2(),  lineFormula.getLaneCoordinateY2());
}

Lane::Lane()
{}

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

