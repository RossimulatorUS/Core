#include "signaler.h"
#include "simulationdata.h"

Signaler::Signaler(volatile bool* execute)
{
    execute_ = execute;
    execution_ = std::thread(&Signaler::init, this);
}

void Signaler::init()
{
    while(!terminate_)
    {
        if(*execute_)
        {
            *execute_ = false;
            std::vector<Node*>& nodes = SimulationData::getInstance().getNodes();
            for(auto itt = nodes.begin(); itt != nodes.end() ; ++itt)
            {
                (*itt)->processWaitingVehicles();
            }
        }
        std::chrono::milliseconds timespan(1);
        std::this_thread::sleep_for(timespan);
    }
}
