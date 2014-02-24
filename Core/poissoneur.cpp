#include "poissoneur.h"

Poissoneur::Poissoneur(std::vector<Noeud> noeuds, Distributeur* distributeur, bool* terminer, bool* attendre)
    : noeuds_(noeuds),
      distributeur_(distributeur),
      terminer_(terminer),
      attendre_(attendre),
      execution_(&Poissoneur::initialiser, this)
{
    // On garde seulement les noeuds qui sont des sources dans le poissoneur
    for(auto i(std::begin(noeuds_)); i != std::end(noeuds_); ++i)
        if(!i->est_source())
            noeuds_.erase(i);
}

void Poissoneur::initialiser()
{
    std::vector<Noeud>::iterator iterateur(std::begin(noeuds_));

    // Pour chaque noeud source
    while(!(*attendre_))
    {
        // Si le noeud est pret a poissoner, ajouter un vehicule sur le reseau
        if(iterateur->est_du())
            distributeur_->ajouter_vehicule(Vehicule(*iterateur, *(iterateur+1))); // Trouver une facon de definir le noeud d'arrivee

        if(iterateur == end(noeuds_))
            iterateur = begin(noeuds_);
    }

    /*
     * On va avoir besoin d'un pointeur sur le vecteur de noeuds original pour choisir
     * aleatoirement un noeud puit
     */
}
