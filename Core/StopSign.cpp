#include "autolock.h"
#include "simulationdata.h"
#include "StopSign.h"
#include "vehicle.h"

std::mutex StopSign::mtx;

/*StopSign::StopSign(GLfloat x, GLfloat y)
{
    x_=x;
    y_=y;
    neighbours_=std::map<node_id_type, road_id_type>();
    nextHopForDestination_=std::map<node_id_type, node_id_type>();
    costs_=std::map<node_id_type, road_cost_type>();
    pendingDVMessages_=std::queue<DVMessage>();
    currentWaitingVehicleIndex=0;
    bernouilli_distribution_=std::bernoulli_distribution(0.2);
    generator_= std::default_random_engine((unsigned int)time(0));
    waitingRoads_ = std::queue<road_id_type>();
    waitingRoadIndex_ = std::set<road_id_type>();

    last_creation_= exec_time(0);
    isNodeBlocked_ = false;
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
    currentWaitingVehicleIndex=0;
    bernouilli_distribution_=std::bernoulli_distribution(0.2);
    generator_= std::default_random_engine((unsigned int)time(0));
    waitingRoads_ = std::queue<road_id_type>();
    waitingRoadIndex_ = std::set<road_id_type>();

    // Pourquoi pas avant?
    id_ = id;
    last_creation_= exec_time(0);
    isNodeBlocked_ = false;
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
    currentWaitingVehicleIndex=0;
    bernouilli_distribution_=std::bernoulli_distribution(distributionInfo.bernouilliAmount.toDouble(&ok));
    generator_= std::default_random_engine((unsigned int)time(0));
    waitingRoads_ = std::queue<road_id_type>();
    waitingRoadIndex_ = std::set<road_id_type>();

    // Pourquoi pas avant?
    id_ = id;
    last_creation_= exec_time(0);
    isNodeBlocked_ = false;
}

void StopSign::processWaitingVehicles()
{
    Autolock av(mtx);

    if(waitingRoads_.size())
    {
        road_id_type rID = waitingRoads_.front();
        RoadSegment& r = SimulationData::getInstance().getRoad(rID);
        r.allLanesUnblocked(id_);
        waitingRoads_.pop();
        waitingRoadIndex_.erase(rID);
    }
}

*/
