#ifndef VEHICULE_H
#define VEHICULE_H

#include <QGLWidget>

#include "noeud.h"
#include "route.h"
#include "voie.h"
#include "simulationtraits.h"

class Vehicule
{
public:
    using node_id_type = typename simulation_traits::node_id_type;
    using road_id_type = typename simulation_traits::road_id_type;
private:
    static const float vitesseBase_;
    static unsigned int id_a_date_;
    unsigned int id_;
    bool isWaiting;

    static road_id_type choisir_route(node_id_type, node_id_type);

    void Avancer();
    void SwitchRoute();
    Noeud GetDestinationImmediate();
    void PrintNodeCoordinates(Noeud depart, Noeud arrivee);
    Noeud &GetNextStep();
public:
    Vehicule();
    Vehicule(node_id_type depart, node_id_type arrive);

    float xVariation_;
    float yVariation_;

    node_id_type noeudDepart_;
    node_id_type noeudArrive_;

    road_id_type actualRoad_;
    Voie actualLane_;

    GLfloat x_;
    GLfloat y_;
    unsigned int id() const;

    Noeud GetNoeudDepart();
    Noeud GetNoeudArrivee();
    Route GetRouteActuelle();
    Voie GetVoieActuelle();

    bool Process();
    void IntersectionGo();
};

#endif // VEHICULE_H
