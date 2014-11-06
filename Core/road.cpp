#include "road.h"

unsigned int Road::id_to_date_ = 0;

Road::Road(std::string name, std::vector<Node> nodes) :
    name_(name),
    nodes_(nodes)
{
    id_ = id_to_date_;
    ++id_to_date_;
}
