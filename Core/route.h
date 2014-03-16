#ifndef ROUTE_H
#define ROUTE_H

#include "formule.h"

#include <QGLWidget>
#include <utility>
#include <vector>

#include "dvutility.h"
#include "noeud.h"
#include "voie.h"

using std::vector;
using std::pair;

class Noeud;    //forward declaration

class Route
{
public:
    using road_id_type = typename simulation_traits::road_id_type;
    using road_cost_type = typename simulation_traits::road_cost_type;

private:
    vector<Voie> voies_;
    //pair<Noeud, Noeud> origines_;

    Formule formuleDroite;
    //offset 0.2 = pas pire pentoute

public:
    Route(road_id_type idDepart, road_id_type idArrivee);
    Route();

    road_id_type IDDepart_;
    road_id_type IDArrive_;
    Noeud GetNoeudDepart();
    Noeud GetNoeudArrivee();

    Formule getFormuleDroite();
    road_cost_type Cost();

};

#endif // ROUTE_H
