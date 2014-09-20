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

///pointControle X1 et autre correspond au coordonnee de la zone pour la route
/// LaneCoordinate X1 et autre correspond au coordonnee de la zone pour la voie
void Formula::determinePerpendicular(Node node1, Node node2, int laneNumber)
{
    if (a > 0)
    {
        controlPoints[X1] = node1.x()-(10*(variationY_*0.01));
        controlPoints[Y1] = node1.y()+(10*(variationX_*0.01));

        controlPoints[X2] = node1.x()+(10*(variationY_*0.01));
        controlPoints[Y2] = node1.y()-(10*(variationX_*0.01));

        controlPoints[X3] = node2.x()-(10*(variationY_*0.01));
        controlPoints[Y3] = node2.y()+(10*(variationX_*0.01));

        controlPoints[X4] = node2.x()+(10*(variationY_*0.01));
        controlPoints[Y4] = node2.y()-(10*(variationX_*0.01));

        if (isLeftToRight(node1, node2))
        {
            laneCoordinates[X1] = node1.x()+(5*((laneNumber*variationY_)*0.01)) + (10*(variationX_*0.01));
            laneCoordinates[X2] = node2.x()+(5*((laneNumber*variationY_)*0.01)) - (10*(variationX_*0.01));

            laneCoordinates[Y1] = node1.y()-(5*((laneNumber*variationX_)*0.01)) + (10*(variationY_*0.01));
            laneCoordinates[Y2] = node2.y()-(5*((laneNumber*variationX_)*0.01)) - (10*(variationY_*0.01));
        }
        else
        {
            laneCoordinates[X1] = node1.x()-(5*((laneNumber*variationY_)*0.01)) - (10*(variationX_*0.01));
            laneCoordinates[X2] = node2.x()-(5*((laneNumber*variationY_)*0.01)) + (10*(variationX_*0.01));

            laneCoordinates[Y1] = node1.y()+(5*((laneNumber*variationX_)*0.01)) - (10*(variationY_*0.01));
            laneCoordinates[Y2] = node2.y()+(5*((laneNumber*variationX_)*0.01)) + (10*(variationY_*0.01));
        }
    }
    else if (a < 0)
    {
        controlPoints[X1] = node1.x()-(10*(variationY_*0.01));
        controlPoints[Y1] = node1.y()-(10*(variationX_*0.01));

        controlPoints[X2] = node1.x()+(10*(variationY_*0.01));
        controlPoints[Y2] = node1.y()+(10*(variationX_*0.01));

        controlPoints[X3] = node2.x()-(10*(variationY_*0.01));
        controlPoints[Y3] = node2.y()-(10*(variationX_*0.01));

        controlPoints[X4] = node2.x()+(10*(variationY_*0.01));
        controlPoints[Y4] = node2.y()+(10*(variationX_*0.01));

        if (isLeftToRight(node1, node2))
        {
            laneCoordinates[X1] = node1.x()-(5*((laneNumber*variationY_)*0.01)) + (10*(variationX_*0.01));
            laneCoordinates[X2] = node2.x()-(5*((laneNumber*variationY_)*0.01)) - (10*(variationX_*0.01));

            laneCoordinates[Y1] = node1.y()-(5*((laneNumber*variationX_)*0.01)) - (10*(variationY_*0.01));
            laneCoordinates[Y2] = node2.y()-(5*((laneNumber*variationX_)*0.01)) + (10*(variationY_*0.01));
        }
        else
        {
            laneCoordinates[X1] = node1.x()+(5*((laneNumber*variationY_)*0.01)) - (10*(variationX_*0.01));
            laneCoordinates[X2] = node2.x()+(5*((laneNumber*variationY_)*0.01)) + (10*(variationX_*0.01));

            laneCoordinates[Y1] = node1.y()+(5*((laneNumber*variationX_)*0.01)) + (10*(variationY_*0.01));
            laneCoordinates[Y2] = node2.y()+(5*((laneNumber*variationX_)*0.01)) - (10*(variationY_*0.01));
        }
    }
    //horizontal
    else if(isLeftToRight(node1, node2) || isLeftToRight(node2, node1))
    {
        controlPoints[X1] = node1.x();
        controlPoints[Y1] = node1.y()-10*0.01;

        controlPoints[X2] = node1.x();
        controlPoints[Y2] = node1.y()+10*0.01;

        controlPoints[X3] = node2.x();
        controlPoints[Y3] = node2.y()-10*0.01;

        controlPoints[X4] = node2.x();
        controlPoints[Y4] = node2.y()+10*0.01;

        if(node1.x() < node2.x())
        {
            laneCoordinates[Y1] = node1.y()-5*(laneNumber*0.01);
            laneCoordinates[Y2] = node1.y()-5*(laneNumber*0.01);

            laneCoordinates[X1] = node1.x() + 0.1;
            laneCoordinates[X2] = node2.x() - 0.1;
        }
        else
        {
            laneCoordinates[Y1] = node1.y()+5*(laneNumber*0.01);
            laneCoordinates[Y2] = node1.y()+5*(laneNumber*0.01);

            laneCoordinates[X1] = node1.x() - 0.1;
            laneCoordinates[X2] = node2.x() + 0.1;
        }
    }
    //vertical
    else
    {
        controlPoints[X1] = node1.x()-10*0.01;
        controlPoints[Y1] = node1.y();

        controlPoints[X2] = node1.x()+10*0.01;
        controlPoints[Y2] = node1.y();

        controlPoints[X3] = node2.x()-10*0.01;
        controlPoints[Y3] = node2.y();

        controlPoints[X4] = node2.x()+10*0.01;
        controlPoints[Y4] = node2.y();

        if(node1.y() < node2.y())
        {
            laneCoordinates[X1] = node1.x()+5*(laneNumber*0.01);
            laneCoordinates[X2] = node1.x()+5*(laneNumber*0.01);

            laneCoordinates[Y1] = node1.y() + 0.1;
            laneCoordinates[Y2] = node2.y() - 0.1;
        }
        else
        {
            laneCoordinates[X1] = node1.x()-5*(laneNumber*0.01);
            laneCoordinates[X2] = node1.x()-5*(laneNumber*0.01);

            laneCoordinates[Y1] = node1.y() - 0.1;
            laneCoordinates[Y2] = node2.y() + 0.1;
        }
    }
}

float Formula::getControlPoint(int which)
{
    return controlPoints[which];
}

float Formula::getLaneCoordinate(int which)
{
    return laneCoordinates[which];
}

float Formula::getLength()
{
    return lineLength_;
}


