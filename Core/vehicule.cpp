#include "vehicule.h"
#include "simulationdata.h"
#include "qdebug.h"
#include "math.h"
#include <algorithm>

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
    actualLane_ = GetRouteActuelle().FindAssociatedLane(GetNoeudDepart(), GetNoeudArrivee());

    // Retouner id et incrementer ensuite    
    id_ = id_a_date_++;

    x_ = actualLane_.GetNoeudDepart().x();
    y_ = actualLane_.GetNoeudDepart().y();

    /*x_ = GetNoeudDepart().x();
    y_ = GetNoeudDepart().y();*/

    xVariation_ = vitesseBase_ * GetVoieActuelle().getFormuleDroite().GetVariationX();
    yVariation_ = vitesseBase_ * GetVoieActuelle().getFormuleDroite().GetVariationY();
    //qDebug() << "VEHICULE HAS SPAWNED! GOING FROM " << depart << " TO " << arrive << " VIA ROAD " << actualRoad_;
}

void Vehicule::PrintNodeCoordinates(Noeud depart, Noeud arrivee)
{
    qDebug() << "depart : " << depart.x() << ", " << depart.y() << endl <<
                "arrivee: " << arrivee.x() << ", " << arrivee.y() << endl;
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

Voie Vehicule::GetVoieActuelle()
{
    return actualLane_;
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
    if(isWaiting)
        return true;

    auto nextX = x_ + xVariation_;
    auto nextY = y_ + yVariation_;

    if(distance(nextX, nextY, GetDestinationImmediate().x(), GetDestinationImmediate().y()) > pyth(xVariation_, yVariation_)/2)
    {
        auto waitingVehicules = GetNextStep().GetWaitingVehicules(actualRoad_);
        for(auto itt = waitingVehicules.begin(); itt != waitingVehicules.end(); ++itt)
        {
            Vehicule* v = *itt;
            if(distance(v->x_, v->y_, x_, y_) < pyth(xVariation_, yVariation_)/2*16 ) //le *valeur est "breathing room"
            {
                isWaiting = true;
                auto& noeud = GetNextStep();
                noeud.AddToWaitingVehicules(this);
                return true;
            }
        };
        Avancer();
        return true;
    }
    else
    {
        if(IsOnLastStretch())
        {
            isWaiting = true;
            return false;
        }
        Avancer();
        isWaiting = true;
        auto& noeud = GetNextStep();
        noeud.AddToWaitingVehicules(this);
        return true;
    }
}

void Vehicule::IntersectionGo()
{
    if(distance(x_, y_, GetDestinationImmediate().x(), GetDestinationImmediate().y()) < pyth(xVariation_, yVariation_)/2)
    {
        SwitchRoute();
    }
    isWaiting = false;

}

bool Vehicule::IsOnLastStretch()
{
    return GetNextStep().GetId() == noeudArrive_;
}

void Vehicule::Avancer()
{
    x_ = x_ + xVariation_;
    y_ = y_ + yVariation_;
}

void Vehicule::SwitchRoute()
{
    noeudDepart_ = GetNextStep().GetId();

    actualRoad_ = choisir_route(noeudDepart_, noeudArrive_);
    actualLane_ = GetRouteActuelle().FindAssociatedLane(GetNoeudDepart(), GetNoeudArrivee());
    xVariation_ = vitesseBase_ * GetVoieActuelle().getFormuleDroite().GetVariationX();
    yVariation_ = vitesseBase_ * GetVoieActuelle().getFormuleDroite().GetVariationY();
    x_ = GetVoieActuelle().GetNoeudDepart().x();
    y_ = GetVoieActuelle().GetNoeudDepart().y();
}

Noeud Vehicule::GetDestinationImmediate()
{
    return GetVoieActuelle().GetNoeudArrivee();
}

Noeud& Vehicule::GetNextStep()
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
