#ifndef DISTRIBUTEUR_H
#define DISTRIBUTEUR_H

#include <atomic>
#include <vector>

#include "historique_dexecution.h"
#include "module.h"
#include "vehicule.h"
#include "vehiculethread.h"

class Distributeur : public Module
{
    // Vehicules en attente d'etre distribues
    std::vector<Vehicule*> vehicules_;

    // Threads du cortex qui sont utilisables pour calcul des deplacements
    std::vector<VehiculeThread*>* threads_;

    // Controle du temps d'execution
    Historique_dexecution historique_;

    void initialiser();

    // ALGORITHME IMPORTANT
    unsigned int choisir_thread();

public:
    Distributeur(std::vector<VehiculeThread *> *, bool*, bool*);
    void ajouter_vehicule(Vehicule *);

};

#endif // DISTRIBUTEUR_H
