#ifndef POISSONEUR_H
#define POISSONEUR_H

#include <vector>

#include "distributeur.h"
#include "module.h"
#include "noeud.h"

// Singleton
// TODO : Heritage d'une classe incopiable

class Poissoneur : public Module
{
    std::vector<Noeud> noeuds_;
    Distributeur* distributeur_;

    void initialiser();

public:
    Poissoneur(std::vector<Noeud>, Distributeur*, bool*, bool*);

};

#endif // POISSONEUR_H
