#include "route.h"
#include "formule.h"
#include "simulationdata.h"

Noeud Route::GetNoeudDepart()
{
    return SimulationData::GetInstance().GetNoeud(IDDepart_);
}

Noeud Route::GetNoeudArrivee()
{
    return SimulationData::GetInstance().GetNoeud(IDArrive_);
}

Route::Route(road_id_type idDepart, road_id_type idArrive)
    :IDDepart_(idDepart), IDArrive_(idArrive)
{
    formuleDroite = Formule(GetNoeudDepart(), GetNoeudArrivee());
}

Route::Route()
{}

Formule Route::getFormuleDroite()
{
    return formuleDroite;
}

Route::road_cost_type Route::Cost()
{
    return formuleDroite.GetLongueur();
}
