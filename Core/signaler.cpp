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
            std::map<simulation_traits::node_id_type,Node*>& nodes = SimulationData::getInstance().getNodes();
            for(auto itt = nodes.begin(); itt != nodes.end(); ++itt)
            {
                // Quite complicated syntax -- keep it on two lines
                Node* node = itt->second;
                (node->*(node->process_function))();
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
