#include "stopSign.h"
#include "vehicle.h"
#include "autolock.h"

//std::mutex StopSign::mtx;

StopSign::StopSign(std::map<Lane*, std::vector<Vehicle*>>* waitingVehicles, std::mutex* mtx_)
    :waitingVehicles_(waitingVehicles),
      currentWaitingVehicleIndex(0),
      mtx(mtx_)
{}

void StopSign::processWaitingVehicles()
{
    Autolock av(*mtx);
    auto itt = waitingVehicles_->begin();

    //amener l'itérateur là où on est rendus
    for(int i = 0; i < currentWaitingVehicleIndex ; ++i)
        ++itt;

    //trouver prochaine queue non-vide
    for(unsigned int i = 0; i < waitingVehicles_->size() ; ++i)
    {
        if(++currentWaitingVehicleIndex > waitingVehicles_->size())
        {
            currentWaitingVehicleIndex = 0;
            itt = waitingVehicles_->begin();
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
