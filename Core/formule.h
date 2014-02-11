#ifndef FORMULE_H
#define FORMULE_H

#include <QGLWidget>
#include "noeud.h"

class Formule
{
    //Formule de la forme y = ax+b

public:
    Formule();
    Formule(Noeud noeudA, Noeud noeudB);

    GLfloat a;
    GLfloat b;

    void DeterminerFormule();
    GLfloat DeterminerPente(GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2);
    GLfloat DeterminerB(GLfloat x, GLfloat y);

};

#endif // FORMULE_H
