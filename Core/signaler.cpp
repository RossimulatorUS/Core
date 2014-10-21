#include "signaler.h"
#include "simulationdata.h"
#include "qdebug.h"

#include <iostream>

Signaler::Signaler(bool* terminate, volatile bool* execute)
{
    terminate_ = terminate;
    execute_ = execute;
    execution_ = std::thread(&Signaler::init, this);
}

void Signaler::init()
{
    while(!(*terminate_))
    {
        if(*execute_)
        {
            *execute_ = false;
            auto& nodes = SimulationData::getInstance().getNodes();
            for(auto itt = nodes.begin(); itt != nodes.end() ; ++itt)
            {
                itt->processWaitingVehicles();
            }
        }
        std::chrono::milliseconds timespan(1);
        std::this_thread::sleep_for(timespan);
    }
}
