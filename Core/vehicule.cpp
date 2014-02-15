#include "vehicule.h"

Vehicule::Vehicule() {}

Vehicule::Vehicule(Noeud depart, Noeud arrive)
    :noeudDepart_(depart), noeudArrive_(arrive)
{
    x_ = depart.x_;
    y_ = depart.y_;
}
