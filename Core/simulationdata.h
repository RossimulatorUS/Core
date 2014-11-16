#ifndef SIMULATIONDATA_H
#define SIMULATIONDATA_H

#include <vector>
#include "simulationtraits.h"
#include "node.h"
#include "road_segment.h"
#include "vehicle.h"
#include "lane.h"
#include <string>
#include <map>

class SimulationData
{
public:
    using node_id_type = typename simulation_traits::node_id_type;
    using road_id_type = typename simulation_traits::road_id_type;
private:

    SimulationData(SimulationData const&); //DON'T IMPLEMENT
    void operator=(SimulationData const&); //DON'T IMPLEMENT

    SimulationData();
    std::map<node_id_type,Node*> allNodes_;
    std::vector<RoadSegment> allRoads_;
    std::list<Vehicle*> allVehicles_;
    std::vector<std::string> accepted_road_types_;

public:
    static SimulationData &getInstance();
    std::map<node_id_type,Node*>& getNodes();
    std::vector<RoadSegment>& getRoads();
    std::list<Vehicle*>& getVehicles();
    std::list<Vehicle *> *getVehiclesPointer();
    Node& getNode(simulation_traits::node_id_type);
    RoadSegment& getRoad(simulation_traits::road_id_type);
    bool accepted_road(std::string);

    node_id_type addNode(GLfloat, GLfloat, bool isSource, Node::DistributionInfo distributionInfo);
    node_id_type addNode(GLfloat, GLfloat, bool isSource, Node::DistributionInfo distributionInfo, node_id_type id);
    node_id_type addNode(GLfloat, GLfloat, bool isSource);
    node_id_type addNode(GLfloat, GLfloat, bool isSource, node_id_type id);
    road_id_type addRoad(RoadSegment);

    void removeVehicle(Vehicle*);
    void addVehicle(Vehicle*);
    void resetAllData();
};

#endif // SIMULATIONDATA_H
