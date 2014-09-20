#include "formula.h"
#include "qdebug.h"
#include "simulationdata.h"

Formula::Formula(){}

Formula::Formula(Node nodeA, Node nodeB, int laneNumber)
{
    a = determineSlope(nodeA.x(), nodeB.x(), nodeA.y(), nodeB.y());
    b = determineB(nodeA.x(), nodeA.y());
    Node tempNode = Node(nodeB.x(), nodeA.y());

    float distanceX = calculateDistance(nodeA, tempNode);
    float distanceY = calculateDistance(nodeB, tempNode);
    lineLength_ = calculateDistance(nodeA, nodeB);

    variationX_ = (distanceX / lineLength_);
    variationY_ = (distanceY / lineLength_);

    determinePerpendicular(nodeA, nodeB, laneNumber);
    determineDirection(nodeA, nodeB);
}

float Formula::getSlope()
{
    return a;
}

GLfloat Formula::determineSlope(GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2)
{
    GLfloat numerator = y2-y1;
    GLfloat denominator = x2-x1;

    return denominator == 0 ? 0 : numerator/denominator;
}

GLfloat Formula::determineB(GLfloat x, GLfloat y)
{
    //y = ax+b
    //y - ax = b
    return y - a*x;
}

bool Formula::isLeftToRight(Node start, Node end)
{
    if (start.x() < end.x())
        return true;
    return false;
}

bool Formula::isRightToLeft(Node start, Node end)
{
    if (start.x() > end.x())
        return true;
    return false;
}

bool Formula::isInSameDirection(Node startRoad, Node endRoad, Node startClick, Node endClick)
{
    if ((isLeftToRight(startRoad, endRoad) && isLeftToRight(startClick, endClick)) ||
        (isTopToBottom(startRoad, endRoad) && isTopToBottom(startClick, endClick)) ||
        (isRightToLeft(startRoad, endRoad) && isRightToLeft(startClick, endClick)) ||
        (isBottomToTop(startRoad, endRoad) && isBottomToTop(startClick, endClick)))
        return true;
    return false;
}

bool Formula::isTopToBottom(Node start, Node end)
{
    if (start.y() < end.y())
        return true;
    return false;
}

bool Formula::isBottomToTop(Node start, Node end)
{
    if (start.y() > end.y())
        return true;
    return false;
}

float Formula::getVariationX()
{
    return variationX_;
}

float Formula::getVariationY()
{
    return variationY_;
}

float Formula::calculatePythagorus(float a, float b)
{
    float c = (a*a)+(b*b);
    return sqrtf(c);
}

float Formula::calculateDistance(Node nodeA, Node nodeB)
{
    float a = nodeB.x() - nodeA.x();
    float b = nodeB.y() - nodeA.y();

    return calculatePythagorus(a,b);
}

void Formula::determineDirection(Node start, Node destination)
{
    //droite a gauche
    if (start.x() > destination.x())
        variationX_ *= -1;
    //haut en bas
    if (start.y() > destination.y())
        variationY_ *= -1;
}

///pointControleX1 et autre correspond au coordonnee de la zone pour la route
/// LaneCoordinateX1 et autre correspond au coordonnee de la zone pour la voie
void Formula::determinePerpendicular(Node node1, Node node2, int laneNumber)
{
    if (a > 0)
    {
        controlPointX1_ = node1.x()-(10*(variationY_*0.01));
        controlPointY1_ = node1.y()+(10*(variationX_*0.01));

        controlPointX2_ = node1.x()+(10*(variationY_*0.01));
        controlPointY2_ = node1.y()-(10*(variationX_*0.01));

        controlPointX3_ = node2.x()-(10*(variationY_*0.01));
        controlPointY3_ = node2.y()+(10*(variationX_*0.01));

        controlPointX4_ = node2.x()+(10*(variationY_*0.01));
        controlPointY4_ = node2.y()-(10*(variationX_*0.01));

        if (isLeftToRight(node1, node2))
        {
            laneCoordinateX1_ = node1.x()+(5*((laneNumber*variationY_)*0.01)) + (10*(variationX_*0.01));
            laneCoordinateX2_ = node2.x()+(5*((laneNumber*variationY_)*0.01)) - (10*(variationX_*0.01));

            laneCoordinateY1_ = node1.y()-(5*((laneNumber*variationX_)*0.01)) + (10*(variationY_*0.01));
            laneCoordinateY2_ = node2.y()-(5*((laneNumber*variationX_)*0.01)) - (10*(variationY_*0.01));
        }
        else
        {
            laneCoordinateX1_ = node1.x()-(5*((laneNumber*variationY_)*0.01)) - (10*(variationX_*0.01));
            laneCoordinateX2_ = node2.x()-(5*((laneNumber*variationY_)*0.01)) + (10*(variationX_*0.01));

            laneCoordinateY1_ = node1.y()+(5*((laneNumber*variationX_)*0.01)) - (10*(variationY_*0.01));
            laneCoordinateY2_ = node2.y()+(5*((laneNumber*variationX_)*0.01)) + (10*(variationY_*0.01));
        }
    }
    else if (a < 0)
    {
        controlPointX1_ = node1.x()-(10*(variationY_*0.01));
        controlPointY1_ = node1.y()-(10*(variationX_*0.01));

        controlPointX2_ = node1.x()+(10*(variationY_*0.01));
        controlPointY2_ = node1.y()+(10*(variationX_*0.01));

        controlPointX3_ = node2.x()-(10*(variationY_*0.01));
        controlPointY3_ = node2.y()-(10*(variationX_*0.01));

        controlPointX4_ = node2.x()+(10*(variationY_*0.01));
        controlPointY4_ = node2.y()+(10*(variationX_*0.01));

        if (isLeftToRight(node1, node2))
        {
            laneCoordinateX1_ = node1.x()-(5*((laneNumber*variationY_)*0.01)) + (10*(variationX_*0.01));
            laneCoordinateX2_ = node2.x()-(5*((laneNumber*variationY_)*0.01)) - (10*(variationX_*0.01));

            laneCoordinateY1_ = node1.y()-(5*((laneNumber*variationX_)*0.01)) - (10*(variationY_*0.01));
            laneCoordinateY2_ = node2.y()-(5*((laneNumber*variationX_)*0.01)) + (10*(variationY_*0.01));
        }
        else
        {
            laneCoordinateX1_ = node1.x()+(5*((laneNumber*variationY_)*0.01)) - (10*(variationX_*0.01));
            laneCoordinateX2_ = node2.x()+(5*((laneNumber*variationY_)*0.01)) + (10*(variationX_*0.01));

            laneCoordinateY1_ = node1.y()+(5*((laneNumber*variationX_)*0.01)) + (10*(variationY_*0.01));
            laneCoordinateY2_ = node2.y()+(5*((laneNumber*variationX_)*0.01)) - (10*(variationY_*0.01));
        }
    }
    //horizontal
    else if(isLeftToRight(node1, node2) || isLeftToRight(node2, node1))
    {
        controlPointX1_ = node1.x();
        controlPointY1_ = node1.y()-10*0.01;

        controlPointX2_ = node1.x();
        controlPointY2_ = node1.y()+10*0.01;

        controlPointX3_ = node2.x();
        controlPointY3_ = node2.y()-10*0.01;

        controlPointX4_ = node2.x();
        controlPointY4_ = node2.y()+10*0.01;

        if(node1.x() < node2.x())
        {
            laneCoordinateY1_ = node1.y()-5*(laneNumber*0.01);
            laneCoordinateY2_ = node1.y()-5*(laneNumber*0.01);

            laneCoordinateX1_ = node1.x() + 0.1;
            laneCoordinateX2_ = node2.x() - 0.1;
        }
        else
        {
            laneCoordinateY1_ = node1.y()+5*(laneNumber*0.01);
            laneCoordinateY2_ = node1.y()+5*(laneNumber*0.01);

            laneCoordinateX1_ = node1.x() - 0.1;
            laneCoordinateX2_ = node2.x() + 0.1;
        }
    }
    //vertical
    else
    {
        controlPointX1_ = node1.x()-10*0.01;
        controlPointY1_ = node1.y();

        controlPointX2_ = node1.x()+10*0.01;
        controlPointY2_ = node1.y();

        controlPointX3_ = node2.x()-10*0.01;
        controlPointY3_ = node2.y();

        controlPointX4_ = node2.x()+10*0.01;
        controlPointY4_ = node2.y();

        if(node1.y() < node2.y())
        {
            laneCoordinateX1_ = node1.x()+5*(laneNumber*0.01);
            laneCoordinateX2_ = node1.x()+5*(laneNumber*0.01);

            laneCoordinateY1_ = node1.y() + 0.1;
            laneCoordinateY2_ = node2.y() - 0.1;
        }
        else
        {
            laneCoordinateX1_ = node1.x()-5*(laneNumber*0.01);
            laneCoordinateX2_ = node1.x()-5*(laneNumber*0.01);

            laneCoordinateY1_ = node1.y() - 0.1;
            laneCoordinateY2_ = node2.y() + 0.1;
        }
    }
}

float Formula::getControlPointX1()
{
    return controlPointX1_;
}

float Formula::getControlPointY1()
{
    return controlPointY1_;
}

float Formula::getControlPointX2()
{
    return controlPointX2_;
}

float Formula::getControlPointY2()
{
    return controlPointY2_;
}

float Formula::getControlPointX3()
{
    return controlPointX3_;
}

float Formula::getControlPointY3()
{
    return controlPointY3_;
}

float Formula::getControlPointX4()
{
    return controlPointX4_;
}

float Formula::getControlPointY4()
{
    return controlPointY4_;
}

float Formula::getLaneCoordinateX1()
{
    return laneCoordinateX1_;
}

float Formula::getLaneCoordinateX2()
{
    return laneCoordinateX2_;
}

float Formula::getLaneCoordinateY1()
{
    return laneCoordinateY1_;
}

float Formula::getLaneCoordinateY2()
{
    return laneCoordinateY2_;
}

float Formula::getLength()
{
    return lineLength_;
}


