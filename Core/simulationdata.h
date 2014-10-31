#ifndef SIMULATIONDATA_H
#define SIMULATIONDATA_H

#include <vector>
#include "simulationtraits.h"
#include "node.h"
#include "road.h"
#include "vehicle.h"
#include "lane.h"
#include "TLight.h"

class SimulationData
{
public:
    using node_id_type = typename simulation_traits::node_id_type;
    using road_id_type = typename simulation_traits::road_id_type;
private:

    SimulationData(SimulationData const&); //DON'T IMPLEMENT
    void operator=(SimulationData const&); //DON'T IMPLEMENT

    SimulationData();
    std::vector<TLight> allNodes_;
    std::vector<Road> allRoads_;
    std::list<Vehicle*> allVehicles_;
public:
    static SimulationData &getInstance();
    std::vector<TLight>& getNodes();
    std::vector<Road>& getRoads();
    std::list<Vehicle*>& getVehicles();
    std::list<Vehicle *> *getVehiclesPointer();
    TLight& getNode(simulation_traits::node_id_type);
    Road& getRoad(simulation_traits::road_id_type);

    node_id_type addNode(GLfloat, GLfloat, bool isSource, Node::DistributionInfo distributionInfo);
    node_id_type addNode(GLfloat, GLfloat, bool isSource);
    road_id_type addRoad(Road);

    void removeVehicle(Vehicle*);
    void addVehicle(Vehicle*);
    void resetAllData();
};

#endif // SIMULATIONDATA_H
