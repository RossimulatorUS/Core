#include <random>

#include "noeud.h"
#include "myglwidget.h"
#include "qdebug.h"
#include "simulationdata.h"
#include "vehicule.h"

std::mutex Noeud::mtx;
std::default_random_engine generateur_ = std::default_random_engine();
std::bernoulli_distribution distribution_uniforme_ = std::bernoulli_distribution(0.5);

/*Noeud::Noeud(bool est_source)
    : est_source_(est_source), est_du_(false),
      neighbours_(std::map<Noeud*, Route*>()),
      nextHopForDestination_(std::map<Noeud*, Noeud*>()),
      costs_(std::map<Noeud*, typename DVMessage::cost_type>( costs_)),
      pendingDVMessages_(std::queue<DVMessage>())
{
    id_ = nextId_++;
}*/

Noeud::Noeud(){}

Noeud::Noeud(GLfloat x, GLfloat y)
    : x_(x), y_(y),
      neighbours_(std::map<node_id_type, road_id_type>()),
      nextHopForDestination_(std::map<node_id_type, node_id_type>()),
      costs_(std::map<node_id_type, road_cost_type>()),
      pendingDVMessages_(std::queue<DVMessage>()),
      derniere_creation_(Historique_dexecution::temps(0)),
      loi_utilisee_(UNIFORME)
      //generateur_(std::default_random_engine()),


{
    //est_du_fonction_ = std::bind ( distribution_, generateur_ );
}


Noeud::Noeud(GLfloat x, GLfloat y, node_id_type id)
    : x_(x), y_(y),
      neighbours_(std::map<node_id_type, road_id_type>()),
      nextHopForDestination_(std::map<node_id_type, node_id_type>()),
      costs_(std::map<node_id_type, road_cost_type>()),
      pendingDVMessages_(std::queue<DVMessage>()),
      derniere_creation_(Historique_dexecution::temps(0)),
      loi_utilisee_(UNIFORME)
{
    // Pourquoi pas avant?
    id_ = id;
}


GLfloat Noeud::x() const
{
    return x_;
}

GLfloat Noeud::y() const
{
    return y_;
}

Noeud::node_id_type Noeud::GetId()
{
    return id_;
}

bool Noeud::est_source()
{
    return neighbours_.size() == 1;
}

bool Noeud::est_du()
{

        if((Historique_dexecution::get_time() - derniere_creation_) > Historique_dexecution::temps(1000))
        {
            derniere_creation_ = Historique_dexecution::get_time();
            return true;
        }

    return false;
}

Vehicule *Noeud::creer_vehicule()
{
    // Atrocement long
    std::default_random_engine generator;
    std::uniform_int_distribution<simulation_traits::node_id_type> distribution(0, SimulationData::GetInstance().GetNoeuds().size() - 1);
    simulation_traits::node_id_type id_fin;

    do
    {
        id_fin = distribution(generator);
    }while(id_fin == this->id_);

    return new Vehicule(this->id_, id_fin);
}

void Noeud::StartDV()
{
    SendDVMessageToNeighbours();
}

bool Noeud::ProcessDVMessages()
{

    auto messages = std::queue<DVMessage>(pendingDVMessages_); //cloner au cas où on recevrait d'autres messages entretemps
    qDebug() << "Node " << id_ << " PROCESSING ITS " << pendingDVMessages_.size() << " MESSAGES";
    bool routingHasChanged = false;
    mtx.lock();
    while(!messages.empty())
    {
        routingHasChanged |= ReceiveDVMessage(messages.front());
        messages.pop();
        pendingDVMessages_.pop();
    }
    mtx.unlock();
    if(routingHasChanged)
    {
        SendDVMessageToNeighbours();
    }
    return routingHasChanged;
}

bool Noeud::ReceiveDVMessage(DVMessage message)
{
    bool routingHasChanged = false;

    auto costs = message.costs();
    for(auto itt = costs.begin(); itt != costs.end() ; ++itt)
    {
        auto destination = itt->first;

        if(destination == id_)
            continue;

        if(!costs_.count(destination))
        {
            costs_[destination] = DV_INFINITY;
        }

        auto newCost = itt->second + costs_[message.origin()];
        if(newCost < costs_[destination])
        {
            costs_[destination] = newCost;
            nextHopForDestination_[destination] = message.origin();
            routingHasChanged = true;
        }
    }

    return routingHasChanged;
}

void Noeud::SendDVMessageToNeighbours()
{
    DVMessage message = DVMessage(id_, nextHopForDestination_, costs_);
    for(auto itt = neighbours_.begin() ; itt != neighbours_.end() ; ++itt)
    {
        GetNoeud(itt->first).pendingDVMessages_.push(message);
    }
}

void Noeud::AddNeighbour(node_id_type neighbour, road_id_type connection)
{
    neighbours_[neighbour] = connection;
    nextHopForDestination_[neighbour] = neighbour;
    costs_[neighbour] = GetRoute(connection).Cost();
}

void Noeud::PrintDVResults()
{
    qDebug() << "PATHS FOR NODE " << + id_;
    for(auto itt = nextHopForDestination_.begin() ; itt != nextHopForDestination_.end() ; ++itt)
    {

        qDebug() << "To " << GetNoeud(itt->first).id_ << " through " << GetNoeud(itt->second).id_ << " which costs " << costs_[itt->first];
    }
    qDebug() << endl;
}

Noeud::node_id_type Noeud::GetProchaineEtape(node_id_type destination)
{
    return nextHopForDestination_.at(destination);
}

Noeud::road_id_type Noeud::GetProchaineRoute(node_id_type destination)
{
    return neighbours_.at(GetProchaineEtape(destination));
}

Noeud &Noeud::GetNoeud(node_id_type id)
{
    return SimulationData::GetInstance().GetNoeud(id);
}

Route &Noeud::GetRoute(Noeud::road_id_type id)
{
    return SimulationData::GetInstance().GetRoute(id);
}
