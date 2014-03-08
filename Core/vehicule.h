#ifndef VEHICULE_H
#define VEHICULE_H

#include "noeud.h"
#include "route.h"
#include <QGLWidget>

class Vehicule
{
    static const float vitesseBase_;
    static unsigned int id_a_date_;
    unsigned int id_;

public:
    Vehicule();
    Vehicule(Noeud* depart, Noeud* arrive, Route* route);
    //Vehicule(Noeud depart, Noeud arrive){}

    float xVariation_;
    float yVariation_;

    Noeud* noeudDepart_;
    Noeud* noeudArrive_;

    Route* actualRoad_;

    GLfloat x_;
    GLfloat y_;
    unsigned int id() const;
};

#endif // VEHICULE_H
