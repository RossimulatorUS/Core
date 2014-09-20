#ifndef FORMULE_H
#define FORMULE_H

#include <QGLWidget>
#include "node.h"

class Formula
{
    //Formule de la forme y = ax+b

    float variationX_;
    float variationY_;
    float lineLength_;
    float directionX_;
    float directionY_;

    float controlPointX1_;
    float controlPointY1_;
    float controlPointX2_;
    float controlPointY2_;
    float controlPointX3_;
    float controlPointY3_;
    float controlPointX4_;
    float controlPointY4_;

    float laneCoordinateX1_;
    float laneCoordinateX2_;

    float laneCoordinateY1_;
    float laneCoordinateY2_;

    float calculatePythagorus(float a, float b);
    float calculateDistance(Node noeudA, Node noeudB);
    void determineDirection(Node depart, Node destination);
    void determinePerpendicular(Node, Node, int laneNumber);


public:

    float getControlPointX1();
    float getControlPointY1();
    float getControlPointX2();
    float getControlPointY2();
    float getControlPointX3();
    float getControlPointY3();
    float getControlPointX4();
    float getControlPointY4();

    float getLaneCoordinateX1();
    float getLaneCoordinateX2();

    float getLaneCoordinateY1();
    float getLaneCoordinateY2();

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
    bool isTopToBottom(Node start, Node end);
    bool isBottomToTop(Node start, Node end);

    float getSlope();

private:
    void initControlPoint(Node node1, Node node2);
};

#endif // FORMULE_H
