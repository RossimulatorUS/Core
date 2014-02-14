#ifndef POISSONEUR_H
#define POISSONEUR_H

#include <vector>
#include "noeud.h"

class Poissoneur
{
    std::vector<Noeud>* noeuds_;
public:
    Poissoneur(std::vector<Noeud>*);
};

#endif // POISSONEUR_H
