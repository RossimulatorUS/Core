#include <QDebug>

#include <algorithm>

#include "cortex.h"
#include "distributeur.h"

Distributeur::Distributeur(std::vector<VehiculeThread*>* threads, bool* terminer, volatile bool* executer)
    : threads_(threads)
{
    vehicules_ = std::vector<Vehicule*>();
    terminer_ = terminer;
    executer_ = executer;
    execution_ = std::thread(&Distributeur::initialiser, this);
}

void Distributeur::initialiser()
{
    est_initialise_ = true;
    //Historique_dexecution::temps temps_initial;

    while(!(*terminer_))
    {
        if(*executer_)
        {
            *executer_ = false;

            // Demarrer chronometre
            //temps_initial = Historique_dexecution::get_time();

            // Qte vehicules a placer pour ce tic
            auto qte_vehicules(vehicules_.size());

            for(unsigned int i(0); i < qte_vehicules; ++i)
            {
                threads_->at(choisir_thread())->ajouter_vehicule(vehicules_[0]);
                vehicules_.erase(begin(vehicules_));
            }

            // Arreter chronometre
            //historique_.ajouter_temps(Historique_dexecution::get_time() - temps_initial);
        }
        std::chrono::milliseconds timespan(1); // Max 20% du temps de perdu
        std::this_thread::sleep_for(timespan);
    }
}

// ALGORITHME IMPORTANT
unsigned int Distributeur::choisir_thread()
{
    // Retourne l'iterateur du thread le moins occupe - le debut du vector, donc sa position
    return std::min_element(threads_->begin(), threads_->end(),
                            [](VehiculeThread* a, VehiculeThread* b){
                                return a->nb_vehicules() < b->nb_vehicules();
                            }) - threads_->begin();
}

void Distributeur::ajouter_vehicule(Vehicule* vehicule)
{
    vehicules_.push_back(vehicule);
}
