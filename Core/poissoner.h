#ifndef POISSONER_H
#define POISSONER_H

#include <vector>

#include "distributor.h"
#include "execution_history.h"
#include "module.h"
#include "node.h"

class Poissoner : public Module
{
    std::vector<Node> nodes_;
    Distributor* distributor_;
    std::list<Vehicle*>* all_vehicles_;

    // Controle du temps d'execution
    Execution_history history_;

    void init();

public:
    Poissoner(std::list<Vehicle *> *, std::vector<Node>, Distributor*, bool*, volatile bool*);

};

#endif // POISSONEUR_H
