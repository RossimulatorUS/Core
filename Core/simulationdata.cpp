#include <algorithm>
#include "simulationdata.h"
#include "TLight.h"

SimulationData::SimulationData()
    : allNodes_(std::vector<Node*>())
{
    accepted_road_types_.push_back("residential");
    accepted_road_types_.push_back("secondary");
}

SimulationData& SimulationData::getInstance()
{
    static SimulationData instance = SimulationData();
    return instance;
}

std::vector<Node*>& SimulationData::getNodes()
{
    return allNodes_;
}

std::vector<RoadSegment>& SimulationData::getRoads()
{
    return allRoads_;
}

std::list<Vehicle *>& SimulationData::getVehicles()
{
    return allVehicles_;
}

std::list<Vehicle *> *SimulationData::getVehiclesPointer()
{
    return &allVehicles_;
}

Node& SimulationData::getNode(simulation_traits::node_id_type id)
{
    return *allNodes_[id];
}

RoadSegment& SimulationData::getRoad(simulation_traits::road_id_type id)
{
    return allRoads_[id];
}

bool SimulationData::accepted_road(std::string road_type)
{
    return std::find(accepted_road_types_.begin(), accepted_road_types_.end(), road_type) != accepted_road_types_.end();
}

SimulationData::node_id_type SimulationData::addNode(GLfloat x, GLfloat y, bool isSource)
{
    allNodes_.push_back(new TLight(x,y, allNodes_.size(), isSource));

    return allNodes_.size()-1;
}

SimulationData::node_id_type SimulationData::addNode(GLfloat x, GLfloat y, bool isSource, node_id_type id)
{
    allNodes_.push_back(new TLight(x,y, id, isSource));

    return allNodes_.size()-1;
}

SimulationData::node_id_type SimulationData::addNode(GLfloat x, GLfloat y, bool isSource, Node::DistributionInfo distributionInfo)
{
    allNodes_.push_back(new TLight(x,y, allNodes_.size(), isSource, distributionInfo));

    return allNodes_.size()-1;
}

SimulationData::node_id_type SimulationData::addNode(GLfloat x, GLfloat y, bool isSource, Node::DistributionInfo distributionInfo, node_id_type id)
{
    allNodes_.push_back(new TLight(x,y, id, isSource, distributionInfo));

    return allNodes_.size()-1;
}

SimulationData::road_id_type SimulationData::addRoad(RoadSegment r)
{
    allRoads_.push_back(r);
    return allRoads_.size()-1;
}

void SimulationData::removeVehicle(Vehicle * v)
{
    getVehicles().remove(v);
}

void SimulationData::resetAllData()
{
    allNodes_.clear();
    allRoads_.clear();
    for(auto vehicle = allVehicles_.begin(); vehicle != allVehicles_.end(); ++vehicle)
    {
        delete *vehicle;
    }
    allVehicles_.clear();
}
