#include "vehicule.h"
#include "simulationdata.h"
#include "qdebug.h"
#include "math.h"

const float Vehicule::vitesseBase_ = 0.01f;
unsigned int Vehicule::id_a_date_ = 0;

Vehicule::Vehicule()
{
    // Retouner id et incrementer ensuite
    id_ = id_a_date_++;
}

Vehicule::Vehicule(node_id_type depart, node_id_type arrive)
    :noeudDepart_(depart),
     noeudArrive_(arrive),
     actualRoad_(GetNoeudDepart().GetProchaineRoute(arrive))
{
    // Retouner id et incrementer ensuite
    id_ = id_a_date_++;

    x_ = GetNoeudDepart().x();
    y_ = GetNoeudDepart().y();

    xVariation_ = vitesseBase_ * GetRouteActuelle().getFormuleDroite().GetVariationX();
    yVariation_ = vitesseBase_ * GetRouteActuelle().getFormuleDroite().GetVariationY();
    //qDebug() << "VEHICULE HAS SPAWNED! GOING FROM " << depart << " TO " << arrive << " VIA ROAD " << actualRoad_;
}

unsigned int Vehicule::id() const
{
    return id_;
}

Noeud Vehicule::GetNoeudDepart()
{
    return SimulationData::GetInstance().GetNoeud(noeudDepart_);
}

Noeud Vehicule::GetNoeudArrivee()
{
    return SimulationData::GetInstance().GetNoeud(noeudArrive_);
}

Route Vehicule::GetRouteActuelle()
{
    return SimulationData::GetInstance().GetRoute(actualRoad_);
}

float pyth(float a, float b)
{
    return std::sqrt(std::pow(a,2) + std::pow(b,2));
}

float distance(float x1, float y1, float x2, float y2)
{
    return pyth(x1-x2, y1-y2);
}

bool Vehicule::Process()
{
    auto nextX = x_ + xVariation_;
    auto nextY = y_ + yVariation_;

    if(distance(nextX, nextY, GetDestinationImmediate().x(), GetDestinationImmediate().y()) > pyth(xVariation_, yVariation_)/2)
    {
        Avancer();
        return true;
    }
    else
    {
        return SwitchRoute();
    }
}
void Vehicule::Avancer()
{
    x_ = x_ + xVariation_;
    y_ = y_ + yVariation_;
}

bool Vehicule::SwitchRoute()
{
    qDebug() << "SWITCH!";
    if(GetDestinationImmediate().GetId() == noeudArrive_)
        return false;
    noeudDepart_ = GetDestinationImmediate().GetId();
    actualRoad_ = choisir_route(noeudDepart_, noeudArrive_);
    xVariation_ = vitesseBase_ * GetRouteActuelle().getFormuleDroite().GetVariationX();
    yVariation_ = vitesseBase_ * GetRouteActuelle().getFormuleDroite().GetVariationY();
    x_ = SimulationData::GetInstance().GetNoeud(noeudDepart_).x();//just in case...
    y_ = SimulationData::GetInstance().GetNoeud(noeudDepart_).y();
    return true;
}

Noeud Vehicule::GetDestinationImmediate()
{
    auto depart = SimulationData::GetInstance().GetNoeud(noeudDepart_);
    auto idArrivee = SimulationData::GetInstance().GetNoeud(noeudArrive_).GetId();
    auto idNextStep = depart.GetProchaineEtape(idArrivee);
    return SimulationData::GetInstance().GetNoeud(idNextStep);
}

// Algorithme important
///Depart est le noeud actuel ; arrivee est la destination finale
Vehicule::road_id_type Vehicule::choisir_route(node_id_type depart, node_id_type arrivee)
{
    return SimulationData::GetInstance().GetNoeud(depart).GetProchaineRoute(arrivee);
}
