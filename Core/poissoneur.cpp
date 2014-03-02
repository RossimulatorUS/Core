#include <QDebug>
#include <iostream>
#include "poissoneur.h"

Poissoneur::Poissoneur(std::vector<Vehicule*>* all_vehicules, std::vector<Noeud> noeuds, Distributeur* distributeur, bool* terminer, bool* attendre)
    : noeuds_(noeuds),
      distributeur_(distributeur),
      all_vehicules_(all_vehicules)

{
    // On garde seulement les noeuds qui sont des sources dans le poissoneur
    /*for(auto i(std::begin(noeuds_)); i != std::end(noeuds_); ++i)
        if(!i->est_source())
            noeuds_.erase(i);*/

    terminer_ = terminer;
    attendre_ = attendre;
    execution_ = std::thread(&Poissoneur::initialiser, this);
}

void Poissoneur::initialiser()
{
    // Attendre que le distributeur soit initialise
    while(!distributeur_->est_initialise())
        std::this_thread::yield();

    std::vector<Noeud>::iterator iterateur(std::begin(noeuds_));

    Route* route = new Route(*iterateur, *(iterateur+1));
    int i = 0;

    // Indication que
    est_initialise_ = true;

    // Pour chaque noeud source
    while(!(*attendre_))
    {
        //std::cout << "Poissonage" << std::endl;
        // Si le noeud est pret a poissoner, ajouter un vehicule sur le reseau
        if(iterateur->est_du() && i < 10)
        {
            Vehicule* vec = new Vehicule(noeuds_[0], noeuds_[1], route);
            std::cout << vec->id() << std::endl;
            all_vehicules_->emplace_back(vec);
            distributeur_->ajouter_vehicule(vec);
            ++i;
            sleep(1);
        }

        //if(iterateur == end(noeuds_))
          //  iterateur = begin(noeuds_);
    }

    /*
     * On va avoir besoin d'un pointeur sur le vecteur de noeuds original pour choisir
     * aleatoirement un noeud puit
     */
}
