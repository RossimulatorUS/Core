#include "signaleur.h"
#include "simulationdata.h"
#include "qdebug.h"

Signaleur::Signaleur(bool* terminer, volatile bool* executer)
{
    terminer_ = terminer;
    executer_ = executer;
    execution_ = std::thread(&Signaleur::initialiser, this);
}

void Signaleur::initialiser()
{
    while(!(*terminer_))
    {
        if(*executer_)
        {
            *executer_ = false;
            auto& noeuds = SimulationData::GetInstance().GetNoeuds();
            for(auto itt = noeuds.begin(); itt != noeuds.end() ; ++itt)
            {
                itt->ProcessWaitingVehicules();
            }
        }
        std::chrono::milliseconds timespan(1);
        std::this_thread::sleep_for(timespan);
    }
}
