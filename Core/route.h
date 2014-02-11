#ifndef ROUTE_H
#define ROUTE_H

#include <QGLWidget>
#include <vector>
#include <utility> // pair
#include "voie.h"
#include "noeud.h"
#include "formule.h"

using std::vector;
using std::pair;

class Route
{
    vector<Voie> voies_;
    //pair<Noeud, Noeud> origines_;

    Formule formuleDroite;

    //offset 0.2 = pas pire pentoute

public:
    Route(Noeud depart, Noeud arrive);

    Noeud PointDepart_;
    Noeud PointArrive_;

};

#endif // ROUTE_H
