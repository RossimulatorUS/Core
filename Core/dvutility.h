#ifndef DVUTILITY_H
#define DVUTILITY_H

#include <map>
#include "simulationtraits.h"
#define DV_INFINITY 999999;
class Noeud;    //forward declaration




class DVMessage
{
public:
    using node_id_type = typename simulation_traits::node_id_type;
    using road_id_type = typename simulation_traits::road_id_type;
    using road_cost_type = typename simulation_traits::road_cost_type;
private:
    node_id_type origin_;
    std::map<node_id_type, node_id_type> paths_;
    std::map<node_id_type, road_cost_type> costs_;
public:
    DVMessage(node_id_type origin, std::map<node_id_type, node_id_type> paths, std::map<node_id_type, road_cost_type> costs);

    //getters
    std::map<node_id_type, node_id_type> paths() const;
    std::map<node_id_type, road_cost_type> costs() const;
    node_id_type origin() const;
};

#endif // DVUTILITY_H
