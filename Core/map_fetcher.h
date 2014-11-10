#ifndef MAP_FETCHER_H
#define MAP_FETCHER_H

#include <map>
#include <string>
#include <vector>

#include "map_node.h"
#include "map_way.h"
#include "simulationtraits.h"

class map_fetcher
{
    using node_id_type = typename simulation_traits::node_id_type;
public:
    map_fetcher(double, double, double, double);
    void fetch();
    void print_response();
    void print();
    std::vector<map_way> get_ways();
    std::map<node_id_type, map_node> get_nodes();

private:
    void url_encode();
    void parse_response();
    const char* site;
    std::string response, request, site_path;
    std::vector<map_way> ways;
    std::map<node_id_type, map_node> nodes;
};

#endif // MAP_FETCHER_H
