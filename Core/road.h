#ifndef ROAD_H
#define ROAD_H

#include <string>
#include <vector>

#include "node.h"

class Road
{
    std::vector<Node> nodes_;
    unsigned int id_;
    std::string name_;

    static unsigned int id_to_date_;

public:
    Road(std::string, std::vector<Node>);
};

#endif // ROAD_H
