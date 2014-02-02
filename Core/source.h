#ifndef SOURCE_H
#define SOURCE_H

#include "noeud.h"

class Source : public Noeud
{
    double coefficient_poisson_;

    public:
        Source();
        Source(double);
        int generer_trafic();
};

#endif // SOURCE_H
