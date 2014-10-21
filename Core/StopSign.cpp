#include "stopSign.h"
#include "vehicle.h"
#include "autolock.h"
#include "simulationdata.h"
#include <iostream>

//std::mutex StopSign::mtx;


StopSign::StopSign(GLfloat x, GLfloat y)
{
    x_=x;
    y_=y;
    neighbours_=std::map<node_id_type, road_id_type>();
    nextHopForDestination_=std::map<node_id_type, node_id_type>();
    costs_=std::map<node_id_type, road_cost_type>();
    pendingDVMessages_=std::queue<DVMessage>();
    waitingVehicles_=new std::map<Lane*, std::vector<Vehicle*>>();
    currentWaitingVehicleIndex=0;
    bernouilli_distribution_=std::bernoulli_distribution(0.2);
    generator_= std::default_random_engine((unsigned int)time(0));

    //est_du_fonction_ = std::bind ( distribution_, generateur_ );
    last_creation_=Execution_history::time(0);
}

StopSign::StopSign(GLfloat x, GLfloat y, node_id_type id, bool isSource)
{
    x_=x;
    y_=y;
    is_source_=isSource;
    neighbours_=std::map<node_id_type, road_id_type>();
    nextHopForDestination_=std::map<node_id_type, node_id_type>();
    costs_=std::map<node_id_type, road_cost_type>();
    pendingDVMessages_=std::queue<DVMessage>();
    waitingVehicles_= new std::map<Lane*, std::vector<Vehicle*>>();
    currentWaitingVehicleIndex=0;
    bernouilli_distribution_=std::bernoulli_distribution(0.2);
    generator_= std::default_random_engine((unsigned int)time(0));

    // Pourquoi pas avant?
    id_ = id;
    last_creation_=Execution_history::time(0);
}

StopSign::StopSign(GLfloat x, GLfloat y, node_id_type id, bool isSource, DistributionInfo distributionInfo)
{
    x_=x;
    y_=y;
    is_source_=isSource;
    distributionInfo_=distributionInfo;
    neighbours_=std::map<node_id_type, road_id_type>();
    nextHopForDestination_=std::map<node_id_type, node_id_type>();
    costs_=std::map<node_id_type, road_cost_type>();
    pendingDVMessages_=std::queue<DVMessage>();
    waitingVehicles_=new std::map<Lane*, std::vector<Vehicle*>>();
    currentWaitingVehicleIndex=0;
    bernouilli_distribution_=std::bernoulli_distribution(distributionInfo.bernouilliAmount.toDouble(&ok));
    generator_= std::default_random_engine((unsigned int)time(0));

    // Pourquoi pas avant?
    id_ = id;
    last_creation_=Execution_history::time(0);
}
void StopSign::processWaitingVehicles()
{
    Autolock av(*mtx);

    /*Road* r = SimulationData::getInstance().getRoad(waitingRoads_.front());
    r->allLanesUnblocked();
    waitingRoads_.pop();

    /*road_id_type id = itt->first->getRoadId();
    Road r = SimulationData::getInstance().getRoad(id);
    std::vector<Lane*> vV = r.getLanes();
    for(int i =0; i<vV.size();i++)
    {
        for(auto ittV = waitingVehicles_.at(vV[i]).begin() ; ittV != waitingVehicles_.at(vV[i]).end() ; ++ittV)
        {
            (*ittV)->intersectionGo();
        }
    }*/

}
