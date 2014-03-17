#include "simulationdata.h"

SimulationData::SimulationData()
    : allNodes_(std::vector<Noeud>())
{
}

SimulationData& SimulationData::GetInstance()
{
    static SimulationData instance = SimulationData();
    return instance;
}

std::vector<Noeud>& SimulationData::GetNoeuds()
{
    return allNodes_;
}

std::vector<Route> SimulationData::GetRoutes()
{
    return allRoads_;
}

std::list<Vehicule *> SimulationData::GetVehicules()
{
    return allVehicules_;
}

std::list<Vehicule *> *SimulationData::GetVehiculesPointer()
{
    return &allVehicules_;
}

Noeud& SimulationData::GetNoeud(simulation_traits::node_id_type id)
{
    return allNodes_[id];
}

Route& SimulationData::GetRoute(simulation_traits::road_id_type id)
{
    return allRoads_[id];
}

SimulationData::node_id_type SimulationData::AddNode(GLfloat x, GLfloat y)
{
    allNodes_.emplace_back(x, y, allNodes_.size());
    return allNodes_.size()-1;
}

SimulationData::road_id_type SimulationData::AddRoute(Route r)
{
    allRoads_.push_back(r);
    return allRoads_.size()-1;
}

void SimulationData::ResetAllData()
{
    allNodes_.clear();
    allRoads_.clear();
}
