#include <QDebug>

#include <algorithm>

#include "poissoneur.h"

Poissoneur::Poissoneur(std::list<Vehicule *> *all_vehicules, std::vector<Noeud> noeuds, Distributeur* distributeur, bool* terminer, bool* attendre)
    : distributeur_(distributeur),
      all_vehicules_(all_vehicules)
{
    // Estime de la quantite de sources sur le reseau
    noeuds_.reserve(noeuds.size() / 2);

    // On garde seulement les noeuds qui sont des sources dans le poissoneur
    for(auto i(std::begin(noeuds)); i != std::end(noeuds); ++i)
        if(i->est_source())
            noeuds_.emplace_back(*i);

    terminer_ = terminer;
    attendre_ = attendre;
    execution_ = std::thread(&Poissoneur::initialiser, this);
}

void Poissoneur::initialiser()
{
    // Attendre que le distributeur soit initialise
    while(!distributeur_->est_initialise())
        std::this_thread::yield();

    // Indication que le poissonneur est pret
    est_initialise_ = true;
    Historique_dexecution::temps temps_initial;

    // Tant que la simulation n'est pas terminee
    while(!(*terminer_))
    {
        // Attendre prochain tic
        if(!(*attendre_))
        {
            *attendre_ = true;

            // Demarrer chronometre
            temps_initial = Historique_dexecution::get_time();

            std::for_each(noeuds_.begin(), noeuds_.end(), [&](Noeud noeud){

                // Si le noeud est pret a poissoner, ajouter un vehicule sur le reseau
                if(noeud.est_du())
                {
                    Vehicule* v = noeud.creer_vehicule();
                    all_vehicules_->push_back(v);
                    distributeur_->ajouter_vehicule(v);
                }
            });


            // Arreter chronometre
            historique_.ajouter_temps(Historique_dexecution::get_time() - temps_initial);
        }
        std::chrono::milliseconds timespan(10);//juste pour pas atteindre 100% de la capacité du CPU à regarder des ifs
        std::this_thread::sleep_for(timespan);
    }
}
