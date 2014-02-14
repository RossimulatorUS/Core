#ifndef CORTEX_H
#define CORTEX_H

#include <vector>
#include <vehiculethread.h>
#include "distributeur.h"
#include "poissoneur.h"

class Cortex
{
    // Informations du systeme pour optimiser nombre de threads
    // et les autres facteurs
    void load_informations();
    void reserve_ressources();
    unsigned int get_physical_threads();

    unsigned int physical_threads; // Threads de la machines
    unsigned int nombre_threads; // Threads disponibles dans la simulation

    std::vector<VehiculeThread> threads_vehicule_;

    Distributeur distributeur_;
    Poissoneur poissoneur_;

public:
    Cortex(std::vector<Noeud>*);

    void ajouter_thread();
};

#endif // CORTEX_H
