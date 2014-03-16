#include "analyseur.h"

Analyseur::Analyseur(bool* terminer, Cortex* cortex)/*
    : terminer_(terminer),
      attendre_(attendre),
      execution_(&Analyseur::initialiser, this)*/
{
    terminer_ = terminer;
    execution_ = std::thread(&Analyseur::initialiser, this);
    cortex_ = cortex;
}

void Analyseur::initialiser()
{
    while(!(*terminer_))
    {
        cortex_->attente_distributeur_ = false;
        cortex_->attente_poissoneur_ = false;
        //attente_deplaceurs_;
        //attente_signaleur_;
    }
}
