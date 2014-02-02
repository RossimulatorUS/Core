#ifndef ROUTE_H
#define ROUTE_H

#include <vector>
#include <utility> // pair
#include "voie.h"
#include "noeud.h"

using std::vector;
using std::pair;

class Route
{
    vector<Voie> voies_;
    pair<Noeud, Noeud> origines_;

    public:
        Route();
};

#endif // ROUTE_H
