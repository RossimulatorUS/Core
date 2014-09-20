#include "analyser.h"
#include <qdebug.h>

Analyser::Analyser(bool* terminate, Cortex* cortex)
{
    terminate_ = terminate;
    cortex_ = cortex;
    execution_ = std::thread(&Analyser::init, this);
}

void Analyser::init()
{
    while(!(*terminate_))
    {
        std::chrono::milliseconds timespan(50);

        for(int i = 0; i < 5 ; ++i)
        {
            cortex_->distributor_execution_ = true;
            cortex_->poissoner_execution_ = true;
            std::for_each(cortex_->mover_execution_.begin(), cortex_->mover_execution_.end(), [&](volatile bool& b){b = true;});
            std::this_thread::sleep_for(timespan);
        }
        cortex_->signaler_execution_ = true;
    }
}
