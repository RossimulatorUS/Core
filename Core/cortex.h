#ifndef CORTEX_H
#define CORTEX_H

#include <vector>
#include <vehiculethread.h>

class Cortex
{
    // Informations du systeme pour optimiser nombre de threads
    // et les autres facteurs
    void load_informations();
    unsigned int nombre_threads;

public:
    Cortex();

    std::vector<VehiculeThread> threads;
    void ajouter_thread();
};

#endif // CORTEX_H
