#include <iostream>
#include <QDebug>

#include "distributeur.h"

Distributeur::Distributeur(std::vector<VehiculeThread*>* threads, bool* terminer, bool* attendre)
     /*,
      terminer_(terminer),
      attendre_(attendre),
      execution_(&Distributeur::initialiser, this)*/
{
    threads_ = threads;
    vehicules_ = std::vector<Vehicule*>();
    terminer_ = terminer;
    attendre_ = attendre;
    execution_ = std::thread(&Distributeur::initialiser, this);
}

void Distributeur::initialiser()
{
    while(!(*terminer_))
   {
        static int num_th = 0;
        if(vehicules_.size())
        {
            qDebug() << vehicules_[0];
            threads_->at(0)->ajouter_vehicule(vehicules_[0]);

            vehicules_.erase(begin(vehicules_));
            ++num_th;
        }
    }
}

void Distributeur::ajouter_vehicule(Vehicule* vehicule)
{
    vehicules_.push_back(vehicule);
}

