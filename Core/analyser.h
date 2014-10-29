#ifndef ANALYSER_H
#define ANALYSER_H

#include "cortex.h"
#include "module.h"

class Cortex;

class Analyser : public Module
{
    Cortex* cortex_;

    void init();
public:
    Analyser(Cortex *cortex);
};

#endif // ANALYSEUR_H
