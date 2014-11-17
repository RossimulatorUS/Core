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
#include "utils.h"

std::mutex Node::mtx;

Node::Node(){}

Node::Node(GLfloat x, GLfloat y)
    : x_(x), y_(y),
      neighbours_(std::map<node_id_type, road_id_type>()),
      nextHopForDestination_(std::map<node_id_type, node_id_type>()),
      costs_(std::map<node_id_type, road_cost_type>()),
      pendingDVMessages_(std::queue<DVMessage>()),
      waitingVehicles_(std::map<Lane*, std::vector<Vehicle*>>()),
      currentWaitingVehicleIndex(0),
      bernouilli_distribution_(0.2),
      generator_((unsigned int)time(0)),
      waitingRoads_(std::queue<road_id_type>()),
      waitingRoadIndex_(std::set<road_id_type>())
{
    //est_du_fonction_ = std::bind ( distribution_, generateur_ );
    last_creation_= exec_time(0);
    isNodeBlocked_= false;
}

Node::Node(GLfloat x, GLfloat y, node_id_type id, bool isSource)
    : x_(x), y_(y), is_source_(isSource),
      neighbours_(std::map<node_id_type, road_id_type>()),
      nextHopForDestination_(std::map<node_id_type, node_id_type>()),
      costs_(std::map<node_id_type, road_cost_type>()),
      pendingDVMessages_(std::queue<DVMessage>()),
      waitingVehicles_(std::map<Lane*, std::vector<Vehicle*>>()),
      currentWaitingVehicleIndex(0),
      bernouilli_distribution_(std::bernoulli_distribution(0.2)),
      generator_((unsigned int)time(0)),
      waitingRoads_(std::queue<road_id_type>()),
      waitingRoadIndex_(std::set<road_id_type>())
{
    id_ = id;
    last_creation_= exec_time(0);
    isNodeBlocked_ = false;
}

Node::Node(GLfloat x, GLfloat y, node_id_type id, bool isSource, DistributionInfo distributionInfo)
    : x_(x), y_(y), is_source_(isSource), distributionInfo_(distributionInfo),
      neighbours_(std::map<node_id_type, road_id_type>()),
      nextHopForDestination_(std::map<node_id_type, node_id_type>()),
      costs_(std::map<node_id_type, road_cost_type>()),
      pendingDVMessages_(std::queue<DVMessage>()),
      waitingVehicles_(std::map<Lane*, std::vector<Vehicle*>>()),
      currentWaitingVehicleIndex(0),
      bernouilli_distribution_(distributionInfo.bernouilliAmount.toDouble(&ok)),
      exponential_distribution_(distributionInfo.exponentialAmount.toDouble(&ok)),
      generator_((unsigned int)time(0)),
      waitingRoads_(std::queue<road_id_type>()),
      waitingRoadIndex_(std::set<road_id_type>())
{
    id_ = id;
    last_creation_= exec_time(0);
    isNodeBlocked_ = false;
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
}

bool Node::is_due()
{
    static std::default_random_engine generateur((unsigned int)time(0));
    auto timeSinceLastCreation = std::chrono::duration_cast<std::chrono::milliseconds>(get_time() - last_creation_).count();
    if (distributionInfo_.isBernouilli)
    {
        if(is_source() && bernouilli_distribution_(generateur)&& timeSinceLastCreation > 250)
        {
            last_creation_ = get_time();
            return true;
        }

        return false;
    }
    else if (distributionInfo_.isUniform)
    {
        auto delay = distributionInfo_.uniformAmount.toInt(&ok, 10);
        if(is_source() &&timeSinceLastCreation > delay)
        {
            last_creation_ = get_time();
            return true;
        }
        return false;
    }
    else if (distributionInfo_.isExponential)
    {
        if(is_source() && exponential_distribution_(generateur)&& timeSinceLastCreation > 250)
        {
            last_creation_ = get_time();
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
        end_id = SimulationData::getInstance().getKeys()[distribution(generator)];
        //end_id = distribution(generator);
    }while(end_id == this->id_);

    return new Vehicle(this->id_, end_id);
}

void Node::startDV()
{
    originalCosts_ = costs_;
    OriginalnextHopForDestination_ = nextHopForDestination_;
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

        //qDebug() << "Costs for node " << id_ << " to destination " << destination << " = " << costs_[destination] << "Origin of the message is : " << message.origin();

        auto newCost = itt->second + costs_[message.origin()];
        if(newCost < costs_[destination])
        {
            //qDebug() << "NEW COST HAD BEEN FOUND = " << newCost;
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
    originalCosts_ = costs_;
    OriginalnextHopForDestination_ = nextHopForDestination_;
}

void Node::addLanes(road_id_type connection)
{
    std::vector<Lane*> lanes = getRoad(connection).getLanes();
    for(int i=0; i<lanes.size(); i++)
        waitingVehicles_[lanes[i]] = std::vector<Vehicle*>();
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

void Node::resetCosts()
{
    costs_ = originalCosts_;
    nextHopForDestination_ = OriginalnextHopForDestination_;
}

Node::node_id_type Node::getNextStep(node_id_type destination)
{
    return nextHopForDestination_.at(destination);
}

Node::road_id_type Node::getNextRoad(node_id_type destination)
{
    //qDebug() << "---------------------------------------------------------------------";
    //qDebug() << "Neighbours for node : " << id_ << " Going to : " << destination;
    for(auto itt = neighbours_.begin(); itt != neighbours_.end(); ++itt)
    {
        //qDebug() << (*itt).first;
    }

    auto value = neighbours_.at(getNextStep(destination));
    //qDebug() << "Value has been found = " << value;
    //qDebug() << "---------------------------------------------------------------------";

    return value;
}

Node &Node::getNode(node_id_type id)
{
    return SimulationData::getInstance().getNode(id);
}

RoadSegment &Node::getRoad(Node::road_id_type id)
{
    return SimulationData::getInstance().getRoad(id);
}

std::vector<Vehicle *>& Node::getWaitingVehicles(Lane* lane)
{
    return waitingVehicles_.at(lane);
}

void Node::addToWaitingVehicles(Vehicle * v)
{
    Autolock av(mtx);
    waitingVehicles_.at(v->getCurrentLane()).push_back(v);
}

//renvoie le véhicule auquel donner le go, ou NULL si aucun véhicule n'attend
void Node::processWaitingVehicles()
{
    Autolock av(mtx);

    while(waitingRoads_.size()>0)
    {
        road_id_type rID = waitingRoads_.front();
        RoadSegment& r = SimulationData::getInstance().getRoad(rID);
        r.allLanesUnblocked(id_);
        waitingRoads_.pop();
        waitingRoadIndex_.erase(rID);
    }
}

void Node::addToWaitingRoads(road_id_type id)
{
    Autolock av(mtx);

    if(waitingRoadIndex_.find(id) == waitingRoadIndex_.end())
        waitingRoads_.push(id);
}

bool Node::isNodeBlocked()
{
    return isNodeBlocked_;
}

void Node::setIsNodeBlocked(bool isRoadBlocked)
{
    isNodeBlocked_ = isRoadBlocked;
}

void Node::updateCost(Node::node_id_type neighbour, Node::road_cost_type connection)
{
    costs_[neighbour] = connection;
    qDebug() << "Node " << id_ << " Neighbour : " << neighbour << "cost to neighbour : " << costs_[neighbour] << " Road : " << connection;
}

std::map<Node::node_id_type, Node::node_id_type> Node::nextHopForDestination()
{
    return nextHopForDestination_;
}

void Node::setNextHopForDestination(const std::map<Node::node_id_type, Node::node_id_type> &nextHopForDestination)
{
    nextHopForDestination_ = nextHopForDestination;
}
