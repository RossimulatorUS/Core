#include <algorithm>
#include <iostream>

#include "simulationdata.h"
#include "TLight.h"
#include "StopSign.h"
#include <iostream>

SimulationData::SimulationData()
    : allNodes_(std::map<node_id_type,Node*>()),
      opengl_fps_(60),
      simulation_fps_(30)
{
    accepted_road_types_.push_back("residential");
    accepted_road_types_.push_back("secondary");
}

std::vector<SimulationData::node_id_type> SimulationData::getKeys() const
{
    return keys;
}

void SimulationData::runDv(bool print_results)
{
    bool dvEnCours = true;

    // Start DV
    for(auto itt = allNodes_.begin() ; itt != allNodes_.end() ; ++itt)
    {
        (*itt).second->startDV();
    }

    // Wait for all messages to be completed
    while(dvEnCours)
    {
        dvEnCours = false;
        for(auto itt = allNodes_.begin() ; itt != allNodes_.end() ; ++itt)
        {
            dvEnCours |= (*itt).second->processDVMessages();
        }
    }

    if(print_results)
    {
        for(auto itt = allNodes_.begin() ; itt != allNodes_.end() ; ++itt)
        {
            (*itt).second->printDVResults();
        }
    }
}

SimulationData& SimulationData::getInstance()
{
    static SimulationData instance = SimulationData();
    return instance;
}

std::map<simulation_traits::node_id_type,Node*>& SimulationData::getNodes()
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
    Node* n = allNodes_.at(id);
    return (*n);
}

RoadSegment& SimulationData::getRoad(simulation_traits::road_id_type id)
{
    return allRoads_[id];
}

bool SimulationData::accepted_road(std::string road_type)
{
    return std::find(accepted_road_types_.begin(), accepted_road_types_.end(), road_type) != accepted_road_types_.end();
}

SimulationData::node_id_type SimulationData::add_intersection(GLfloat x,
                                                              GLfloat y,
                                                              simulation_traits::intersection law,
                                                              node_id_type id)
{
    // When Nodes are created manually
    if (id == 0) id = allNodes_.size();
    keys.push_back(id);

    allNodes_.insert(std::pair<simulation_traits::node_id_type,Node*>(id, new Node(x, y, law, id)));
    return id;
}

SimulationData::node_id_type SimulationData::add_source(GLfloat x,
                                                        GLfloat y,
                                                        simulation_traits::intersection intersection_type,
                                                        simulation_traits::law law,
                                                        double law_coefficient,
                                                        node_id_type id)
{
    // When Nodes are created manually
    if (id == 0) id = allNodes_.size();
    keys.push_back(id);

    allNodes_.insert(std::pair<simulation_traits::node_id_type,Node*>(id, new Node(x, y, intersection_type, law, law_coefficient, id)));
    return id;
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

void SimulationData::print_nodes()
{
    for(auto it = allNodes_.begin(); it != allNodes_.end(); ++it)
    {
        std::cout << (*it).second->GetId() << std::endl;
    }
}

unsigned int SimulationData::opengl_fps()
{
    return opengl_fps_;
}

unsigned int SimulationData::simulation_fps()
{
    return simulation_fps_;
}
