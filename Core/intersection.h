#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <vector>
#include "noeud.h"
#include "route.h"

using std::vector;

class Intersection : public Noeud
{
    vector<Route> routes_;
    public:
        Intersection();
};

#endif // INTERSECTION_H
