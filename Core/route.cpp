#include "route.h"
#include "formule.h"

Route::Route(Noeud depart, Noeud arrive)
    :PointDepart_(depart), PointArrive_(arrive)
{
    formuleDroite = Formule(PointDepart_, PointArrive_);
}

Route::Route()
{}

Formule Route::getFormuleDroite()
{
    return formuleDroite;
}
