#include "poissoneur.h"

Poissoneur::Poissoneur(std::vector<Noeud> noeuds, Distributeur* distributeur)
    : noeuds_(noeuds), distributeur_(distributeur)
{
    // On garde seulement les noeuds qui sont des sources dans le poissoneur
    for(auto i(std::begin(noeuds_)); i != std::end(noeuds_); ++i)
        if(!i->est_source())
            noeuds_.erase(i);
}

void Poissoneur::verifier_generation_vehicule()
{
    for(auto i(std::begin(noeuds_)); i != std::end(noeuds_); ++i)
        if(i->est_du())
            distributeur_->ajouter_vehicule(Vehicule(*i, *(i+1))); // Trouver une facon de definir le noeud d'arrivee
}
