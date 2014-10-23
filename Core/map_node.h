#ifndef MAP_NODE_H
#define MAP_NODE_H

class map_node
{
public:
    typedef unsigned long long node_id;

    map_node(double longitude, double latitude) : x(longitude), y(latitude){}
    double longitude(){return x;}
    double latitude(){return y;}

private:
    double x;
    double y;
};

#endif // MAP_NODE_H
