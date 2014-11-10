#ifndef ROAD_H
#define ROAD_H

#include <string>
#include <vector>
#include "simulationtraits.h"
//#include "road_segment.h"

class Road
{
    using node_id_type = typename simulation_traits::node_id_type;
    std::vector<node_id_type> nodes_;
    //std::vector<RoadSegment> segments;
    unsigned int id_;
    std::string name_;

    static unsigned int id_to_date_;

public:
    Road(std::string, std::vector<node_id_type>);
};

#endif // ROAD_H
