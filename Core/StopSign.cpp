#include "stopSign.h"
#include "vehicle.h"
#include "autolock.h"

//std::mutex StopSign::mtx;

StopSign::StopSign(GLfloat x, GLfloat y)
{
    x_= x;
    y_=y;
    neighbours_ =std::map<node_id_type, road_id_type>();
    nextHopForDestination_=std::map<node_id_type, node_id_type>();
    costs_=std::map<node_id_type, road_cost_type>();
    pendingDVMessages_=std::queue<DVMessage>();
    waitingVehicles_=std::map<road_id_type, std::vector<Vehicle*>>();
    bernouilli_distribution_= std::bernoulli_distribution(0.2);
    generator_=std::default_random_engine((unsigned int)time(0));
    currentWaitingVehicleIndex=0;

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
    waitingVehicles_=std::map<road_id_type, std::vector<Vehicle*>>();
    bernouilli_distribution_= std::bernoulli_distribution(0.2);
    generator_=std::default_random_engine((unsigned int)time(0));
    currentWaitingVehicleIndex=0;

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
    waitingVehicles_=std::map<road_id_type, std::vector<Vehicle*>>();
    bernouilli_distribution_=std::bernoulli_distribution(distributionInfo.bernouilliAmount.toDouble(&ok));
    generator_=std::default_random_engine((unsigned int)time(0));
    currentWaitingVehicleIndex=0;

    // Pourquoi pas avant?
    id_ = id;
    last_creation_=Execution_history::time(0);
}



void StopSign::processWaitingVehicles()
{
    Autolock av(mtx);
    auto itt = waitingVehicles_.begin();

    //amener l'itérateur là où on est rendus
    for(int i = 0; i < currentWaitingVehicleIndex ; ++i)
        ++itt;

    //trouver prochaine queue non-vide
    for(unsigned int i = 0; i < waitingVehicles_.size() ; ++i)
    {
        if(++currentWaitingVehicleIndex > waitingVehicles_.size())
        {
            currentWaitingVehicleIndex = 0;
            itt = waitingVehicles_.begin();
        }

        if(itt->second.empty())
            continue;

        /*auto ittV = itt->second.begin();
        if(ittV != itt->second.end())
        {*/
            for(auto ittV = itt->second.begin(); ittV != itt->second.end() ; ++ittV)
            {
                //road_id_type fromRoad = (*ittV)->getCurrentRoadId();
                (*ittV)->intersectionGo();
                /*std::vector<Vehicle*> lane2 = waitingVehicles_->at((*ittV)->getCurrentRoadId());
                if((!lane2.empty()) && (lane2.front()->getNextRoadID() == fromRoad))
                {
                    lane2.front()->intersectionGo();
                    currentWaitingVehicleIndex++;
                }*/
            }
        //}
        itt->second.clear();/**/
    }
}
