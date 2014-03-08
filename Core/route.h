#ifndef ROUTE_H
#define ROUTE_H

#include <QGLWidget>
#include <vector>
#include <utility> // pair
#include "voie.h"
#include "noeud.h"
#include "formule.h"
#include "dvutility.h"

using std::vector;
using std::pair;

class Noeud;    //forward declaration

class Route
{
public:
    using cost_type = DVMessage::cost_type;
private:
    vector<Voie> voies_;
    //pair<Noeud, Noeud> origines_;

    Formule formuleDroite;

    //offset 0.2 = pas pire pentoute

public:
    Route(Noeud* depart, Noeud* arrive);
    Route();

    Noeud* PointDepart_;
    Noeud* PointArrive_;

    Formule getFormuleDroite();
    cost_type Cost();

};

#endif // ROUTE_H
