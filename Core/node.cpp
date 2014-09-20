#include <random>
#include <iostream>
#include <chrono>

#include <QDebug>

#include "node.h"
#include "myglwidget.h"
#include "qdebug.h"
#include "simulationdata.h"
#include "vehicle.h"
#include "autolock.h"

std::mutex Node::mtx;
std::default_random_engine generator_ = std::default_random_engine();
std::bernoulli_distribution uniform_distribution_ = std::bernoulli_distribution(0.5);

/*Noeud::Noeud(bool est_source)
    : est_source_(est_source), est_du_(false),
      neighbours_(std::map<Noeud*, Route*>()),
      nextHopForDestination_(std::map<Noeud*, Noeud*>()),
      costs_(std::map<Noeud*, typename DVMessage::cost_type>( costs_)),
      pendingDVMessages_(std::queue<DVMessage>())
{
    id_ = nextId_++;
}*/

Node::Node(){}

Node::Node(GLfloat x, GLfloat y)
    : x_(x), y_(y),
      neighbours_(std::map<node_id_type, road_id_type>()),
      nextHopForDestination_(std::map<node_id_type, node_id_type>()),
      costs_(std::map<node_id_type, road_cost_type>()),
      pendingDVMessages_(std::queue<DVMessage>()),
      waitingVehicles_(std::map<road_id_type, std::vector<Vehicle*>>()),
      currentWaitingVehicleIndex(0),
      bernouilli_distribution_(0.2),
      generator_((unsigned int)time(0))
{
    //est_du_fonction_ = std::bind ( distribution_, generateur_ );
    last_creation_=Execution_history::time(0);
}

Node::Node(GLfloat x, GLfloat y, node_id_type id, bool isSource)
    : x_(x), y_(y), is_source_(isSource),
      neighbours_(std::map<node_id_type, road_id_type>()),
      nextHopForDestination_(std::map<node_id_type, node_id_type>()),
      costs_(std::map<node_id_type, road_cost_type>()),
      pendingDVMessages_(std::queue<DVMessage>()),
      waitingVehicles_(std::map<road_id_type, std::vector<Vehicle*>>()),
      currentWaitingVehicleIndex(0),
      bernouilli_distribution_(0.2),
      generator_((unsigned int)time(0))
{
    // Pourquoi pas avant?
    id_ = id;
    last_creation_=Execution_history::time(0);
}

Node::Node(GLfloat x, GLfloat y, node_id_type id, bool isSource, DistributionInfo distributionInfo)
    : x_(x), y_(y), is_source_(isSource), distributionInfo_(distributionInfo),
      neighbours_(std::map<node_id_type, road_id_type>()),
      nextHopForDestination_(std::map<node_id_type, node_id_type>()),
      costs_(std::map<node_id_type, road_cost_type>()),
      pendingDVMessages_(std::queue<DVMessage>()),
      waitingVehicles_(std::map<road_id_type, std::vector<Vehicle*>>()),
      currentWaitingVehicleIndex(0),
      bernouilli_distribution_(distributionInfo.bernouilliAmount.toDouble(&ok)),
      generator_((unsigned int)time(0))
{
    // Pourquoi pas avant?
    id_ = id;
    last_creation_=Execution_history::time(0);
}


GLfloat Node::x() const
{
    return x_;
}

GLfloat Node::y() const
{
    return y_;
}

Node::node_id_type Node::GetId()
{
    return id_;
}

bool Node::is_source()
{
    return is_source_;
    //return neighbours_.size() == 1;
}

bool Node::is_due()
{
    //static auto derniere_creation = Historique_dexecution::get_time();//for some reason, mettre ça en variable de classe marchait pas, ça valait toujours 0
    static std::default_random_engine generateur((unsigned int)time(0));
    auto timeSinceLastCreation = std::chrono::duration_cast<std::chrono::milliseconds>(Execution_history::get_time()-last_creation_).count();
    if (distributionInfo_.isBernouilli)
    {
        if(is_source() && bernouilli_distribution_(generateur)&& timeSinceLastCreation > 250)
        {
            last_creation_ = Execution_history::get_time();
            return true;
        }

        return false;
    }
    else if (distributionInfo_.isUniform)
    {
        auto delay = distributionInfo_.uniformAmount.toInt(&ok, 10);
        if(is_source() &&timeSinceLastCreation > delay)
        {
            last_creation_ = Execution_history::get_time();
            return true;
        }
        return false;
    }
}

Vehicle *Node::create_vehicle()
{
    static std::default_random_engine generator;
    static std::uniform_int_distribution<simulation_traits::node_id_type> distribution(0, SimulationData::getInstance().getNodes().size() - 1);
    simulation_traits::node_id_type end_id;

    //TODO vérifier si il y a un chemin qui se rend
    do
    {
        end_id = distribution(generator);
    }while(end_id == this->id_);

    return new Vehicle(this->id_, end_id);
}

void Node::startDV()
{
    sendDVMessageToNeighbours();
}

bool Node::processDVMessages()
{

    auto messages = std::queue<DVMessage>(pendingDVMessages_); //cloner au cas où on recevrait d'autres messages entretemps
    qDebug() << "Node " << id_ << " PROCESSING ITS " << pendingDVMessages_.size() << " MESSAGES";
    bool routingHasChanged = false;
    mtx.lock();
    while(!messages.empty())
    {
        routingHasChanged |= receiveDVMessage(messages.front());
        messages.pop();
        pendingDVMessages_.pop();
    }
    mtx.unlock();
    if(routingHasChanged)
    {
        sendDVMessageToNeighbours();
    }
    return routingHasChanged;
}

bool Node::receiveDVMessage(DVMessage message)
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

void Node::sendDVMessageToNeighbours()
{
    DVMessage message = DVMessage(id_, nextHopForDestination_, costs_);
    for(auto itt = neighbours_.begin() ; itt != neighbours_.end() ; ++itt)
    {
        getNode(itt->first).pendingDVMessages_.push(message);
    }
}

void Node::addNeighbour(node_id_type neighbour, road_id_type connection)
{
    neighbours_[neighbour] = connection;
    nextHopForDestination_[neighbour] = neighbour;
    costs_[neighbour] = getRoad(connection).cost();
    waitingVehicles_[connection] = std::vector<Vehicle*>();
}

void Node::printDVResults()
{
    qDebug() << "PATHS FOR NODE " << + id_;
    for(auto itt = nextHopForDestination_.begin() ; itt != nextHopForDestination_.end() ; ++itt)
    {

        qDebug() << "To " << getNode(itt->first).id_ << " through " << getNode(itt->second).id_ << " which costs " << costs_[itt->first];
    }
    qDebug() << endl;
}

Node::node_id_type Node::getNextStep(node_id_type destination)
{
    return nextHopForDestination_.at(destination);
}

Node::road_id_type Node::getNextRoad(node_id_type destination)
{
    return neighbours_.at(getNextStep(destination));
}

Node &Node::getNode(node_id_type id)
{
    return SimulationData::getInstance().getNode(id);
}

Road &Node::getRoad(Node::road_id_type id)
{
    return SimulationData::getInstance().getRoad(id);
}

std::vector<Vehicle *> Node::getWaitingVehicles(Node::road_id_type id)
{
    return waitingVehicles_.at(id);
}

void Node::addToWaitingVehicles(Vehicle * v)
{
    Autolock av(mtx);
    waitingVehicles_.at(v->getCurrentRoad().getRoadID()).push_back(v);
}

//renvoie le véhicule auquel donner le go, ou NULL si aucun véhicule n'attend
void Node::processWaitingVehicles()
{
    Autolock av(mtx);
    auto itt = waitingVehicles_.begin();

    //amener l'itérateur là où on est rendus
    for(int i = 0; i < currentWaitingVehicleIndex ; ++i)
        ++itt;

    //trouver prochaine queue non-vide
    for(unsigned int i = 0; i < waitingVehicles_.size() ; ++i)
    {
        if(++currentWaitingVehicleIndex > waitingVehicles_.size())
        {
            currentWaitingVehicleIndex = 0;
            itt = waitingVehicles_.begin();
        }

        if(itt->second.empty())
            continue;

        for(auto ittV = itt->second.begin() ; ittV != itt->second.end() ; ++ittV)
        {
            (*ittV)->intersectionGo();
        }
        itt->second.clear();
        //return v;
    }

    //return std::queue<Vehicule*>();

}
