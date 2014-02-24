#ifndef ANALYSEUR_H
#define ANALYSEUR_H

#include "module.h"

class Analyseur : public Module
{
    void initialiser();
public:
    Analyseur(bool*, bool*);
};

#endif // ANALYSEUR_H
