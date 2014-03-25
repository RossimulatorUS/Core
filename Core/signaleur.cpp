#include "signaleur.h"
#include "simulationdata.h"
#include "qdebug.h"

Signaleur::Signaleur()
{
    execution_ = std::thread(&Signaleur::initialiser, this);
}

void Signaleur::initialiser()
{
    while(true) //TODO plz fix this Ross
    {
        auto& noeuds = SimulationData::GetInstance().GetNoeuds();
        for(auto itt = noeuds.begin(); itt != noeuds.end() ; ++itt)
        {
            itt->ProcessWaitingVehicules();
        }
        std::chrono::milliseconds timespan(600);//s'arranger pour que le cortex donne des ordres
        std::this_thread::sleep_for(timespan);
    }
}
