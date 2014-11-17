#ifndef MAP_NODE_H
#define MAP_NODE_H

#include "simulationtraits.h"

class map_node
{
public:
    using node_id_type = simulation_traits::node_id_type;

    map_node(){x =0; y=0;}
    map_node(double longitude, double latittude) : x(longitude), y(latittude){}
    double longitude(){return x;}
    double lattitude(){return y;}

private:
    double x;
    double y;
};

#endif // MAP_NODE_H
