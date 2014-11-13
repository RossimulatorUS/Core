#include "analyser.h"

Analyser::Analyser(Cortex* cortex)
{
    cortex_ = cortex;
    execution_ = std::thread(&Analyser::init, this);
}

void Analyser::init()
{
    while(!terminate_)
    {
        cortex_->distributor_execution_ = true;
        cortex_->signaler_execution_ = true;

        std::for_each(cortex_->mover_execution_.begin(), cortex_->mover_execution_.end(), [&](volatile bool& b){b = true;});

        // System tic control
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}
