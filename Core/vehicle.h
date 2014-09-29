#ifndef VEHICLE_H
#define VEHICLE_H

#include <QGLWidget>

#include "node.h"
#include "road.h"
#include "lane.h"
#include "simulationtraits.h"

class Vehicle
{
public:
    using node_id_type = typename simulation_traits::node_id_type;
    using road_id_type = typename simulation_traits::road_id_type;
private:
    static std::mutex mtx;

    static const float baseSpeed_;
    static const float maxSpeed_;
    static const float accelerationRate_;
    static const float decelerationRate_;
    static unsigned int id_to_date_;
    unsigned int id_;
    bool isWaiting;

    //0 to 100
    float progress_;

    static road_id_type chose_road(node_id_type, node_id_type);

    void decelerateVehicle();
    void accelerateVehicle();
    void resetVehicleSpeed();
    void evaluateProgress();

    void advance();
    void switchRoad();
    Node getImmediateDestination();
    void printNodeCoordinates(Node start, Node end);
    Node &getNextStep();
public:
    Vehicle();
    Vehicle(node_id_type start, node_id_type end);

    float xVariation_;
    float yVariation_;
    float actualSpeed_;

    node_id_type startNode_;
    node_id_type endNode_;

    road_id_type currentRoad_;
    QSharedPointer<Lane> currentLane_;

    bool isAccelerating_;
    bool isDecelerating_;

    bool isCarBehind();
    bool isCarInFront();

    GLfloat x_;
    GLfloat y_;
    unsigned int id() const;

    Node getStartNode();
    Node getEndNode();
    Road getCurrentRoad();
    QSharedPointer<Lane> getCurrentLane();

    float getProgress();
    float getSpeed();
    int getPositionInLane();

    road_id_type getCurrentRoadId();
    road_id_type getNextRoadID();

    Vehicle *getVehicleInFront();
    Vehicle *getVehicleBehind();

    bool process();
    void intersectionGo();
    bool isOnLastStretch();
};

#endif // VEHICULE_H
