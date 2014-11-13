#include "autolock.h"
#include "simulationdata.h"
#include "TLight.h"
#include "vehicle.h"

std::mutex TLight::mtx;

TLight::TLight(GLfloat x, GLfloat y):lightDelay(0), currentLight(0)
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
    parallelRoads = std::map<road_id_type,road_id_type>();

    last_creation_= exec_time(0);
    isNodeBlocked_ = false;
}

TLight::TLight(GLfloat x, GLfloat y, node_id_type id, bool isSource):lightDelay(0), currentLight(0)
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
    parallelRoads = std::map<road_id_type,road_id_type>();

    // Pourquoi pas avant?
    id_ = id;
    last_creation_= exec_time(0);
    isNodeBlocked_ = false;
}

TLight::TLight(GLfloat x, GLfloat y, node_id_type id, bool isSource, DistributionInfo distributionInfo):lightDelay(0), currentLight(0)
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
    parallelRoads = std::map<road_id_type,road_id_type>();

    // Pourquoi pas avant?
    id_ = id;
    last_creation_= exec_time(0);
    isNodeBlocked_ = false;
}

void TLight::processWaitingVehicles()
{
    Autolock av(mtx);

    --lightDelay;
    if(lightDelay<0)
    {
        lightDelay = 20;
        currentLight = (currentLight+1) % neighbours_.size();
        std::map<node_id_type,road_id_type>::iterator it1 = neighbours_.begin();

        for(int i =0;i<currentLight;i++)
            ++it1;

        waitingRoadIndex_.clear();
        waitingRoadIndex_.insert(it1->second);

        std::map<road_id_type,road_id_type>::iterator it2 = parallelRoads.find(it1->second);
        if(it2!=parallelRoads.end())
        {
            if(it2->first != it2->second)
                waitingRoadIndex_.insert(it2->second);
        }
        else
        {
            RoadSegment& r = SimulationData::getInstance().getRoad(it2->second);
            road_id_type inFront = it2->second;
            std::map<node_id_type,road_id_type>::iterator it3 = neighbours_.begin();

            while(it3 !=neighbours_.end())
            {
                RoadSegment& otherRoad = SimulationData::getInstance().getRoad(it3->second);

                if((it2->second != it3->second) && r.isParallel(r.getStartNode(),r.getEndNode(),otherRoad.getStartNode(),otherRoad.getEndNode()))
                {
                    inFront = it3->second;
                    break;
                }
                it3++;
            }
            parallelRoads[it1->second] = inFront;
            if(it2->second != inFront)
                waitingRoadIndex_.insert(inFront);
        }
    }

    std::set<road_id_type>::iterator it = waitingRoadIndex_.begin();

    while(it != waitingRoadIndex_.end())
    {
        RoadSegment& r = SimulationData::getInstance().getRoad(*it);
        r.allLanesUnblocked(id_);
        it++;
    }

}
