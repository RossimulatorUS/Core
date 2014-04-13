#ifndef SIGNALEUR_H
#define SIGNALEUR_H

#include <thread>
#include "module.h"

class Signaleur : public Module
{
    // Fonction d'initialisation
    void initialiser();

public:
    Signaleur(bool *terminer, volatile bool *executer);
};

#endif // SIGNALEUR_H
