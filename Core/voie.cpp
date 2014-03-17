#include "voie.h"

Voie::Voie(Noeud depart, Noeud arrivee, road_id_type parent)
    :depart_(depart), arrivee_(arrivee), parent_(parent)
{
    formuleDroite = Formule(GetNoeudDepart(), GetNoeudArrivee());

    depart_ = Noeud(formuleDroite.GetLaneCoordinateX1(), formuleDroite.GetLaneCoordinateY1());
    arrivee_ = Noeud(formuleDroite.GetLaneCoordinateX2(), formuleDroite.GetLaneCoordinateY2());
}

Voie::Voie()
{}

Noeud Voie::GetNoeudDepart()
{
    return depart_;
}

Noeud Voie::GetNoeudArrivee()
{
    return arrivee_;
}

Formule Voie::getFormuleDroite()
{
    return formuleDroite;
}

