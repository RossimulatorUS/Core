#include <QDebug>

#include <algorithm>

#include "cortex.h"
#include "distributeur.h"

bool min(std::vector<VehiculeThread*>::iterator i, std::vector<VehiculeThread*>::iterator j)
{
    return false;
    //return ((*i).size() < j.size());
}

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
    Historique_dexecution::temps temps_initial;

    while(!(*terminer_))
    {
        if(!(*attendre_))
        {
            *attendre_ = true;

            // Demarrer chronometre
            temps_initial = Historique_dexecution::get_time();

            // Qte vehicules a placer pour ce tic
            auto qte_vehicules(vehicules_.size());

            for(unsigned int i(0); i < qte_vehicules; ++i)
            {
                threads_->at(choisir_thread())->ajouter_vehicule(vehicules_[0]);
                vehicules_.erase(begin(vehicules_));
            }

            // Arreter chronometre
            historique_.ajouter_temps(Historique_dexecution::get_time() - temps_initial);
        }
    }
}

// ALGORITHME IMPORTANT
unsigned int Distributeur::choisir_thread()
{
    //return std::min_element(threads_->begin(), threads_->end(), min);
    static int t = 0;
    t = (t + 1) % Cortex::NB_THREADS_DE_BASE;
    return t;
}

void Distributeur::ajouter_vehicule(Vehicule* vehicule)
{
    vehicules_.push_back(vehicule);
}
