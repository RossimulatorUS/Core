#ifndef POISSONEUR_H
#define POISSONEUR_H

#include <vector>

#include "module.h"
#include "distributeur.h"

#include "noeud.h"

// Singleton
// TODO : Heritage d'une classe incopiable

class Poissoneur : public Module
{
    std::vector<Noeud> noeuds_;
    std::vector<Vehicule*>* all_vehicules_;
    Distributeur* distributeur_;
    void initialiser();

public:
    Poissoneur(std::vector<Vehicule *> *, std::vector<Noeud>, Distributeur*, bool*, bool*);

};

#endif // POISSONEUR_H
