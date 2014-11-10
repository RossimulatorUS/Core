#ifndef MAP_WAY_H
#define MAP_WAY_H

#include <map>
#include <string>
#include <vector>

#include "map_node.h"
#include "simulationtraits.h"

class map_way
{
public:
    typedef unsigned long long way_id;
    using node_id_type = simulation_traits::node_id_type;

    map_way(way_id id, std::vector<node_id_type> path, std::map<std::string, std::string> attributes) :
        id(id),
        path(path),
        attributes(attributes)
    {}

//private: On devrait friender client a la place
    way_id id;
    std::vector<node_id_type> path;
    std::map<std::string, std::string> attributes;

};

#endif // MAP_WAY_H
