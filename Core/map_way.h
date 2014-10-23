#ifndef MAP_WAY_H
#define MAP_WAY_H

#include <map>
#include <string>
#include <vector>

#include "map_node.h"

class map_way
{
public:
    typedef unsigned long long way_id;

    map_way(way_id id, std::vector<map_node::node_id> path, std::map<std::string, std::string> attributes) :
        id(id),
        path(path),
        attributes(attributes)
    {}

//private: On devrait friender client a la place
    way_id id;
    std::vector<map_node::node_id> path;
    std::map<std::string, std::string> attributes;

};

#endif // MAP_WAY_H
