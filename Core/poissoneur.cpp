#include <iostream>
#include "poissoneur.h"

Poissoneur::Poissoneur(std::vector<Noeud> noeuds, Distributeur* distributeur)
    : distributeur_(distributeur), noeuds_(noeuds), execution_(&Poissoneur::verifier_generation_vehicule, this)
{
    // On garde seulement les noeuds qui sont des sources dans le poissoneur
    for(auto i(std::begin(noeuds_)); i != std::end(noeuds_); ++i)
        if(!i->est_source())
            noeuds_.erase(i);

    std::cout << "Construction du poissoneur" << std::endl;
    std::cout << "Quantite de sources : " << noeuds_.size() << std::endl;
}

void Poissoneur::verifier_generation_vehicule()
{
    // Pour chaque noeud source
    for(auto i(std::begin(noeuds_)); i != std::end(noeuds_); ++i)
        // Si le noeud est pret a poissoner
        if(i->est_du())
            // Ajouter un vehicule sur le reseau
            distributeur_->ajouter_vehicule(Vehicule(*i, *(i+1))); // Trouver une facon de definir le noeud d'arrivee

    /*
     * On va avoir besoin d'un pointeur sur le vecteur de noeuds original pour choisir
     * aleatoirement un noeud puit
     */
}
