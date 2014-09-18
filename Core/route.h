#ifndef ROUTE_H
#define ROUTE_H

#include "formule.h"

#include <QGLWidget>
#include <utility>
#include <vector>
#include <QTime>

#include "dvutility.h"
#include "noeud.h"
#include "voie.h"

using std::vector;
using std::pair;

class Noeud;    //forward declaration

class Route
{
public:
    using node_id_type = typename simulation_traits::node_id_type;
    using road_id_type = typename simulation_traits::road_id_type;
    using road_cost_type = typename simulation_traits::road_cost_type;

private:
    vector<Voie> voies_;

    Formule formuleDroite;
    
    bool isReadyToCreate;
    bool isLeftToRight_;
    bool isOneWay_;

public:
    Route(node_id_type idDepart, node_id_type idArrivee, bool isOneWay, int laneNumber);
    Route();

    node_id_type IDDepart_;
    node_id_type IDArrive_;

    road_id_type IDRoute_;

    Noeud GetNoeudDepart();
    Noeud GetNoeudArrivee();

    bool IsReadyToCreate();
    bool IsInSameDirection(Noeud departRoute, Noeud arriveeRoute, Noeud departClick, Noeud arriveeClick);
    //bool IsInSameDirection(Noeud depart, Noeud arrivee);
    bool IsLeftToRight(Noeud noeud1, Noeud noeud2);
    bool IsLeftToRight();

    Voie FindAssociatedLane(Noeud, Noeud);

    Formule getFormuleDroite();
    road_cost_type Cost();

    void AddLane(Noeud, Noeud, int laneNumber);

    std::vector<Voie> GetLanes();

    road_id_type GetRoadID();
};

#endif // ROUTE_H
