#ifndef VEHICULE_H
#define VEHICULE_H

#include "noeud.h"
#include <QGLWidget>

class Vehicule
{
    Noeud noeudDepart_;
    Noeud noeudArrive_;

public:
    Vehicule();
    Vehicule(Noeud depart, Noeud arrive);

    GLfloat x_;
    GLfloat y_;
};

#endif // VEHICULE_H
