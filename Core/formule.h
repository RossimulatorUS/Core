#ifndef FORMULE_H
#define FORMULE_H

#include <QGLWidget>
#include "noeud.h"

class Formule
{
    //Formule de la forme y = ax+b

    float variationX_;
    float variationY_;
    float distanceDroite_;
    float directionX_;
    float directionY_;

    float pointControleX1_;
    float pointControleY1_;
    float pointControleX2_;
    float pointControleY2_;
    float pointControleX3_;
    float pointControleY3_;
    float pointControleX4_;
    float pointControleY4_;

    float LaneCoordinateX1_;
    float LaneCoordinateX2_;

    float LaneCoordinateY1_;
    float LaneCoordinateY2_;

    float CalculerPythagore(float a, float b);
    float CalculerDistance(Noeud noeudA, Noeud noeudB);
    void DeterminerDirection(Noeud depart, Noeud destination);
    void DeterminerPerpendiculaire(Noeud, Noeud);


public:

    float GetPointControleX1();
    float GetPointControleY1();
    float GetPointControleX2();
    float GetPointControleY2();
    float GetPointControleX3();
    float GetPointControleY3();
    float GetPointControleX4();
    float GetPointControleY4();

    float GetLaneCoordinateX1();
    float GetLaneCoordinateX2();

    float GetLaneCoordinateY1();
    float GetLaneCoordinateY2();

    Formule();
    Formule(Noeud noeudA, Noeud noeudB);

    GLfloat a;
    GLfloat b;

    float GetLongueur();

    float GetVariationX();
    float GetVariationY();

    GLfloat DeterminerPente(GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2);
    GLfloat DeterminerB(GLfloat x, GLfloat y);

    bool IsLeftToRight(Noeud depart, Noeud arrivee);
    bool IsRightToLeft(Noeud depart, Noeud arrivee);
    bool IsInSameDirection(Noeud departRoute, Noeud arriveeRoute, Noeud departClick, Noeud arriveeClick);
    bool IsTopToBottom(Noeud depart, Noeud arrivee);
    bool IsBottomToTop(Noeud depart, Noeud arrivee);

    float getPente();

private:
    void InitialiserPointControle(Noeud noeud1, Noeud noeud2);
};

#endif // FORMULE_H
