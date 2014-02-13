#include "vehicule.h"

Vehicule::Vehicule() {}

Vehicule::Vehicule(Noeud depart, Noeud arrive)
    :noeudDepart_(depart), noeudArrive_(arrive)
{
    x_ = depart._x;
    y_ = depart._y;
}
