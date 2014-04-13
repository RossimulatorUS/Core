#include "analyseur.h"
#include <qdebug.h>

Analyseur::Analyseur(bool* terminer, Cortex* cortex)
{
    terminer_ = terminer;
    cortex_ = cortex;
    execution_ = std::thread(&Analyseur::initialiser, this);

}

void Analyseur::initialiser()
{
    while(!(*terminer_))
    {
        std::chrono::milliseconds timespan(50);

        for(int i = 0; i < 5 ; ++i)
        {
            cortex_->execution_distributeur_ = true;
            cortex_->execution_poissoneur_ = true;
            std::for_each(cortex_->execution_deplaceurs_.begin(), cortex_->execution_deplaceurs_.end(), [&](volatile bool& b){b = true;});
            std::this_thread::sleep_for(timespan);
        }
        cortex_->execution_signaleur_ = true;



    }
}
