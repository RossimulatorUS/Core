#ifndef POISSONEUR_H
#define POISSONEUR_H

#include <thread>
#include <vector>
#include "distributeur.h"
#include "noeud.h"

class Poissoneur
{
    Distributeur* distributeur_;
    std::vector<Noeud> noeuds_;
    std::thread execution_;

    // Fonction d'initialisation
    void verifier_generation_vehicule();

public:
    Poissoneur(std::vector<Noeud>, Distributeur*);

};

#endif // POISSONEUR_H
