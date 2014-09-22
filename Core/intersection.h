#ifndef INTERSECTION_H
#define INTERSECTION_H

class Intersection
{
public:
    Intersection(){}
    ~Intersection(){}
    virtual void processWaitingVehicles() = 0;
};

#endif // INTERSECTION_H
