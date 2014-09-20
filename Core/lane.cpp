#include "lane.h"
#include <QDebug>

Lane::Lane(Node start, Node end, road_id_type parent, int laneNumber)
    :start_(start), end_(end), parent_(parent)
{
    lineFormula = Formula(getStartNode(), getEndNode(), laneNumber);

    start_ = Node( lineFormula.getLaneCoordinate(X1),  lineFormula.getLaneCoordinate(Y1));
    end_ = Node( lineFormula.getLaneCoordinate(X2),  lineFormula.getLaneCoordinate(Y2));
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

