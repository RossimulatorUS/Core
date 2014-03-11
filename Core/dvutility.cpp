#include "dvutility.h"

DVMessage::DVMessage(node_id_type origin, std::map<node_id_type, node_id_type> paths, std::map<node_id_type, road_cost_type> costs)
    :origin_(origin), paths_(paths), costs_(costs)
{

}

std::map<DVMessage::node_id_type, DVMessage::node_id_type> DVMessage::paths() const
{
    return paths_;
}


std::map<DVMessage::node_id_type, DVMessage::road_cost_type> DVMessage::costs() const
{
    return costs_;
}


DVMessage::node_id_type DVMessage::origin() const
{
    return origin_;
}
