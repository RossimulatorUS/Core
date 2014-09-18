#ifndef VOIE_H
#define VOIE_H

#include "noeud.h"
#include "formule.h"
#include "simulationtraits.h"

class Voie
{
public:
    using road_id_type = typename simulation_traits::road_id_type;
private:
    Noeud depart_;
    Noeud arrivee_;

    road_id_type parent_;

    Formule formuleDroite;
public:
    Voie();
    Voie(Noeud, Noeud, road_id_type parent, int laneNumber);

    Noeud GetNoeudDepart();
    Noeud GetNoeudArrivee();

    Formule getFormuleDroite();
};

#endif // VOIE_H
