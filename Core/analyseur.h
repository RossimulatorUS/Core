#ifndef ANALYSEUR_H
#define ANALYSEUR_H

#include "cortex.h"
#include "module.h"

class Cortex;

class Analyseur : public Module
{
    Cortex* cortex_;
    void initialiser(Analyseur *a);
public:
    Analyseur(bool*, Cortex *cortex);
};

#endif // ANALYSEUR_H
