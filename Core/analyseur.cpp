#include "analyseur.h"

Analyseur::Analyseur(bool* terminer, Cortex* cortex)/*
    : terminer_(terminer),
      attendre_(attendre),
      execution_(&Analyseur::initialiser, this)*/
{
    terminer_ = terminer;
    cortex_ = cortex;
    execution_ = std::thread(&Analyseur::initialiser, this, this);

}

void Analyseur::initialiser(Analyseur* a)
{
    while(!(*terminer_))
    {
        a->cortex_->attente_distributeur_ = false;
        a->cortex_->attente_poissoneur_ = false;
        //attente_deplaceurs_;
        //attente_signaleur_;
        std::chrono::milliseconds timespan(1000); // or whatever
        std::this_thread::sleep_for(timespan);
    }
}
