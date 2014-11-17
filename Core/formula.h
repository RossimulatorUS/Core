#ifndef FORMULE_H
#define FORMULE_H

#include "node.h"

enum{
    X1=0,
    Y1=1,
    X2=2,
    Y2=3,
    X3=4,
    Y3=5,
    X4=6,
    Y4=7
} pointEnum;

class Formula
{
    //Formule de la forme y = ax+b

    float variationX_;
    float variationY_;
    float lineLength_;
    float directionX_;
    float directionY_;

    float controlPoints[8];
    float laneCoordinates[4];

    float calculatePythagorus(float a, float b);
    float calculateDistance(Node noeudA, Node noeudB);
    void determineDirection(Node depart, Node destination);
    void determinePerpendicular(Node, Node, int laneNumber);


public:

    float getControlPoint(int which);

    float getLaneCoordinate(int which);

    Formula();
    Formula(Node nodeA, Node nodeB, int laneNumber);

    GLfloat a;
    GLfloat b;

    float getLength();

    float getVariationX();
    float getVariationY();

    GLfloat determineSlope(GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2);
    GLfloat determineB(GLfloat x, GLfloat y);

    bool isLeftToRight(Node start, Node end);
    bool isRightToLeft(Node start, Node end);
    bool isInSameDirection(Node routeStart, Node routeEnd, Node startClick, Node endClick);
    bool isParallel(Node routeStart, Node routeEnd, Node startClick, Node endClick);
    bool isTopToBottom(Node start, Node end);
    bool isBottomToTop(Node start, Node end);

    float getSlope();

private:
    void initControlPoint(Node node1, Node node2);
};

#endif // FORMULE_H
