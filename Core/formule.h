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

    float CalculerPythagore(float a, float b);
    float CalculerDistance(Noeud noeudA, Noeud noeudB);
    void DeterminerDirection(Noeud depart, Noeud destination);


public:
    Formule();
    Formule(Noeud noeudA, Noeud noeudB);

    GLfloat a;
    GLfloat b;

    float GetLongueur();

    float GetVariationX();
    float GetVariationY();

    float GetDirectionX();
    float GetDirectionY();

    GLfloat DeterminerPente(GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2);
    GLfloat DeterminerB(GLfloat x, GLfloat y);

    float getPente();

};

#endif // FORMULE_H
