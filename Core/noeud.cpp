#include "noeud.h"
#include "myglwidget.h"
#include "qdebug.h"

Noeud::id_type Noeud::nextId_ = 0;
std::mutex Noeud::mtx;

/*Noeud::Noeud(bool est_source)
    : est_source_(est_source), est_du_(false),
      neighbours_(std::map<Noeud*, Route*>()),
      nextHopForDestination_(std::map<Noeud*, Noeud*>()),
      costs_(std::map<Noeud*, typename DVMessage::cost_type>( costs_)),
      pendingDVMessages_(std::queue<DVMessage>())
{
    id_ = nextId_++;
}*/

Noeud::Noeud(GLfloat x, GLfloat y, bool isDummy)
    : x_(x), y_(y),
      neighbours_(std::map<Noeud*, Route*>()),
      nextHopForDestination_(std::map<Noeud*, Noeud*>()),
      costs_(std::map<Noeud*, typename DVMessage::cost_type>( costs_)),
      pendingDVMessages_(std::queue<DVMessage>())
{
    if(!isDummy)
        id_ = nextId_++;
}


GLfloat Noeud::x() const
{
    return x_;
}

GLfloat Noeud::y() const
{
    return y_;
}

bool Noeud::est_source()
{
    return true;
    //return est_source_;
}

bool Noeud::est_du()
{
    static bool tmp(true);
    tmp = !tmp;
    return tmp;
}

void Noeud::StartDV()
{
    SendDVMessageToNeighbours();
}

bool Noeud::ProcessDVMessages()
{
    auto messages = std::queue<DVMessage>(pendingDVMessages_); //cloner au cas où on recevrait d'autres messages entretemps

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

        if(destination == this)
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
    DVMessage message = DVMessage(this, nextHopForDestination_, costs_);
    for(auto itt = neighbours_.begin() ; itt != neighbours_.end() ; ++itt)
    {
        itt->first->pendingDVMessages_.push(message);
    }
}

void Noeud::AddNeighbour(Noeud * neighbour, Route * connection)
{
    neighbours_[neighbour] = connection;
    nextHopForDestination_[neighbour] = neighbour;
    costs_[neighbour] = connection->Cost();
}

void Noeud::PrintDVResults()
{
    qDebug() << "PATHS FOR NODE " << + id_;
    for(auto itt = nextHopForDestination_.begin() ; itt != nextHopForDestination_.end() ; ++itt)
    {

        qDebug() << "To " << itt->first->id_ << " through " << itt->second->id_ << " which costs " << costs_[itt->first];
    }
    qDebug() << endl;
}

Noeud *Noeud::GetProchaineEtape(Noeud *destination)
{
    return nextHopForDestination_[destination];
}
