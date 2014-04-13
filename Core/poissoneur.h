#ifndef POISSONEUR_H
#define POISSONEUR_H

#include <vector>

#include "distributeur.h"
#include "historique_dexecution.h"
#include "module.h"
#include "noeud.h"

class Poissoneur : public Module
{
    std::vector<Noeud> noeuds_;
    Distributeur* distributeur_;
    std::list<Vehicule*>* all_vehicules_;

    // Controle du temps d'execution
    Historique_dexecution historique_;

    void initialiser();

public:
    Poissoneur(std::list<Vehicule *> *, std::vector<Noeud>, Distributeur*, bool*, volatile bool*);

};

#endif // POISSONEUR_H
