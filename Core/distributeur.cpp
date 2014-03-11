#include <algorithm>
#include <QDebug>

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
        // Demarrer chronometre
        temps_initial = Historique_dexecution::get_time();

        while(vehicules_.size())
        {
            threads_->at(choisir_thread())->ajouter_vehicule(vehicules_[0]);
            vehicules_.erase(begin(vehicules_));
        }

        // Arreter chronometre
        historique_.ajouter_temps(Historique_dexecution::get_time() - temps_initial);
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
