#include "vehicule.h"

const float Vehicule::vitesseBase_ = 0.01f;
unsigned int Vehicule::id_a_date_ = 0;

Vehicule::Vehicule()
{
    // Retouner id et incrementer ensuite
    id_ = id_a_date_++;
}

Vehicule::Vehicule(Noeud depart, Noeud arrive, Route *route)
    :noeudDepart_(depart), noeudArrive_(arrive), actualRoad_(route)
{
    x_ = depart.x();
    y_ = depart.y();

    xVariation_ = vitesseBase_ * actualRoad_->getFormuleDroite().GetVariationX();
    yVariation_ = vitesseBase_ * actualRoad_->getFormuleDroite().GetVariationY();
}
