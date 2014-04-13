#include "analyseur.h"

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
        cortex_->execution_distributeur_ = true;
        cortex_->execution_poissoneur_ = true;
        cortex_->execution_deplaceurs_ = true;
        cortex_->execution_signaleur_ = true;

        std::chrono::milliseconds timespan(10);
        std::this_thread::sleep_for(timespan);
    }
}
