#ifndef SIMULATIONDATA_H
#define SIMULATIONDATA_H
#include <vector>
#include "simulationtraits.h"
#include "noeud.h"
#include "route.h"
#include "vehicule.h"

class SimulationData
{
public:
    using node_id_type = typename simulation_traits::node_id_type;
    using road_id_type = typename simulation_traits::road_id_type;
private:

    SimulationData(SimulationData const&); //DON'T IMPLEMENT
    void operator=(SimulationData const&); //DON'T IMPLEMENT

    SimulationData();
    std::vector<Noeud> allNodes_;
    std::vector<Route> allRoads_;
    std::list<Vehicule*> allVehicules_;
public:
    static SimulationData &GetInstance();
    std::vector<Noeud> &GetNoeuds();
    std::vector<Route> GetRoutes();
    std::list<Vehicule*> GetVehicules();
    std::list<Vehicule *> *GetVehiculesPointer();
    Noeud& GetNoeud(simulation_traits::node_id_type);
    Route& GetRoute(simulation_traits::road_id_type);

    node_id_type AddNode(GLfloat, GLfloat, bool isSource, Noeud::DistributionInfo distributionInfo);
    node_id_type AddNode(GLfloat, GLfloat, bool isSource);
    road_id_type AddRoute(Route);
    void AddVehicule(Vehicule*);
    void ResetAllData();


};

#endif // SIMULATIONDATA_H
