#ifndef SIGNALEUR_H
#define SIGNALEUR_H

#include <thread>
#include "module.h"

class Signaler : public Module
{
    // Fonction d'initialisation
    void init();

public:
    Signaler(volatile bool *execute);
};

#endif // SIGNALEUR_H
