#include "route.h"
#include "formule.h"
#include "qdebug.h"
#include "simulationdata.h"

Noeud Route::GetNoeudDepart()
{
    return SimulationData::GetInstance().GetNoeud(IDDepart_);
}

Noeud Route::GetNoeudArrivee()
{
    return SimulationData::GetInstance().GetNoeud(IDArrive_);
}

bool Route::IsReadyToCreate()
{
    return isReadyToCreate;
}

//comparer avec des coordonnées
bool Route::IsInSameDirection(Noeud departRoute, Noeud arriveeRoute, Noeud departClick, Noeud arriveeClick)
{
    if (formuleDroite.IsInSameDirection(departRoute, arriveeRoute, departClick, arriveeClick))
        return true;
    return false;
}

/*bool Route::IsInSameDirection(Noeud departRoute, Noeud arriveeRoute)
{
    if (formuleDroite.IsInSameDirection(departRoute, arriveeRoute, GetNoeudDepart(), GetNoeudArrivee()))
        return true;
    return false;
}*/

bool Route::IsLeftToRight(Noeud noeud1, Noeud noeud2)
{
    return formuleDroite.IsLeftToRight(noeud1, noeud2);
}

bool Route::IsLeftToRight()
{
    return isLeftToRight_;
}

Voie Route::FindAssociatedLane(Noeud depart, Noeud arrivee)
{
    QTime time = QTime::currentTime();
    srand((uint)time.msec());

    while(true)
    {
        auto randLaneNumber = (rand() % (voies_.size()) + 0);

        if (IsInSameDirection(voies_[randLaneNumber].GetNoeudDepart(), voies_[randLaneNumber].GetNoeudArrivee(), depart, arrivee))
        {
            return voies_[randLaneNumber];
        }
    }

    /*for (unsigned int i = 0; i < voies_.size(); ++i)
    {
        if (IsInSameDirection(voies_[i].GetNoeudDepart(), voies_[i].GetNoeudArrivee(), depart, arrivee))
        {
            //qDebug() << "voie.size = " << voies_.size() << " " << i;
            return voies_[i];
        }
    }*/
    return Voie();
}

Route::Route(node_id_type idDepart, node_id_type idArrive, bool isOneWay, int laneNumber)
    :IDDepart_(idDepart), IDArrive_(idArrive), isReadyToCreate(true), voies_(std::vector<Voie>())
{
    isOneWay_ = isOneWay;
    isLeftToRight_ = IsLeftToRight(GetNoeudDepart(), GetNoeudArrivee());
    formuleDroite = Formule(GetNoeudDepart(), GetNoeudArrivee(), laneNumber);
}

Route::Route()
    :isReadyToCreate(false)
{}

Formule Route::getFormuleDroite()
{
    return formuleDroite;
}

Route::road_cost_type Route::Cost()
{
    return formuleDroite.GetLongueur();
}

void Route::AddLane(Noeud noeud1, Noeud noeud2, int laneNumber)
{
    voies_.push_back(Voie(noeud1, noeud2, GetRoadID(), laneNumber));
}

Route::road_id_type Route::GetRoadID()
{
    return SimulationData::GetInstance().GetNoeud(IDDepart_).GetProchaineRoute(IDArrive_);
}

std::vector<Voie> Route::GetLanes()
{
    return voies_;
}
