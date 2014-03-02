#include <iostream>
#include <QDebug>

#include "distributeur.h"

Distributeur::Distributeur(std::vector<VehiculeThread*>* threads, bool* terminer, bool* attendre)
{
    threads_ = threads;
    vehicules_ = std::vector<Vehicule*>();
    terminer_ = terminer;
    attendre_ = attendre;
    execution_ = std::thread(&Distributeur::initialiser, this);
}

void Distributeur::initialiser()
{
    est_initialise_ = true;
    while(!(*terminer_))
    {
        if(vehicules_.size())
        {
            threads_->at(0)->ajouter_vehicule(vehicules_[0]);
            vehicules_.erase(begin(vehicules_));
        }
    }
}

void Distributeur::ajouter_vehicule(Vehicule* vehicule)
{
    vehicules_.push_back(vehicule);
}

