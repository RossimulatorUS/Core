#include "simulationdata.h"

SimulationData::SimulationData()
    : allNodes_(std::vector<Node>())
{
}

SimulationData& SimulationData::getInstance()
{
    static SimulationData instance = SimulationData();
    return instance;
}

std::vector<Node>& SimulationData::getNodes()
{
    return allNodes_;
}

std::vector<Road> SimulationData::getRoads()
{
    return allRoads_;
}

std::list<Vehicle *> SimulationData::getVehicles()
{
    return allVehicules_;
}

std::list<Vehicle *> *SimulationData::getVehiclesPointer()
{
    return &allVehicules_;
}

Node& SimulationData::getNode(simulation_traits::node_id_type id)
{
    return allNodes_[id];
}

Road& SimulationData::getRoad(simulation_traits::road_id_type id)
{
    return allRoads_[id];
}

SimulationData::node_id_type SimulationData::addNode(GLfloat x, GLfloat y, bool isSource)
{
    allNodes_.emplace_back(x, y, allNodes_.size(), isSource);

    return allNodes_.size()-1;
}

SimulationData::node_id_type SimulationData::addNode(GLfloat x, GLfloat y, bool isSource, Node::DistributionInfo distributionInfo)
{
    allNodes_.emplace_back(x, y, allNodes_.size(), isSource, distributionInfo);

    return allNodes_.size()-1;
}

SimulationData::road_id_type SimulationData::addRoad(Road r)
{
    allRoads_.push_back(r);
    return allRoads_.size()-1;
}

void SimulationData::removeVehicle(Vehicle * v)
{
    getVehiclesPointer()->remove(v);
    getVehicles().remove(v);
}

void SimulationData::resetAllData()
{
    allNodes_.clear();
    allRoads_.clear();
}
