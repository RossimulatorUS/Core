#include <algorithm>
#include <QDebug>

#include "cortex.h"
#include "distributeur.h"

Distributeur::Distributeur(std::vector<VehiculeThread*>* threads, bool* terminer, bool* attendre)
    : threads_(threads)
{
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
            threads_->at(choisir_thread())->ajouter_vehicule(vehicules_[0]);
            vehicules_.erase(begin(vehicules_));
        }
    }
}

// ALGORITHME IMPORTANT
unsigned int Distributeur::choisir_thread()
{
    //return std::min_element(std::begin(threads_), std::end(threads_), min);
    static int t = 0;
    t = (t + 1) % Cortex::NB_THREADS_DE_BASE;
    return t;
}

void Distributeur::ajouter_vehicule(Vehicule* vehicule)
{
    vehicules_.push_back(vehicule);
}

bool min(int i, int j) { return i<j; }
