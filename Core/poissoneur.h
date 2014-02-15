#ifndef POISSONEUR_H
#define POISSONEUR_H

#include <vector>
#include "distributeur.h"
#include "noeud.h"

class Poissoneur
{
    Distributeur* distributeur_;
    std::vector<Noeud> noeuds_;

public:
    Poissoneur(std::vector<Noeud>, Distributeur*);
    void verifier_generation_vehicule();

};

#endif // POISSONEUR_H
