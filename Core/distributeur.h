#ifndef DISTRIBUTEUR_H
#define DISTRIBUTEUR_H

#include <atomic>
#include <vector>

#include <vehiculethread.h>
#include <vehicule.h>
#include "module.h"

// Singleton
// TODO : Heritage d'une classe incopiable

class Distributeur : public Module
{
    // Vehicules en attente d'etre distribues
    std::vector<Vehicule*> vehicules_;

    // Threads du cortex qui sont utilisables pour calcul des deplacements
    std::vector<VehiculeThread*>* threads_;

    void initialiser();

public:
    Distributeur(std::vector<VehiculeThread *> *, bool*, bool*);
    void ajouter_vehicule(Vehicule *);

};

#endif // DISTRIBUTEUR_H
