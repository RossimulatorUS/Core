#ifndef POINT_H
#define POINT_H

#include <QGLWidget>

#include <map>
#include <mutex>
#include <queue>
#include <stack>

#include "dvutility.h"
#include "execution_history.h"
#include "simulationtraits.h"

class Vehicle;
class Road;    //forward declaration pour éviter un include cyclique ; include de route dans le cpp

class Node
{
public:
    using node_id_type = typename simulation_traits::node_id_type;
    using road_id_type = typename simulation_traits::road_id_type;
    using road_cost_type = typename simulation_traits::road_cost_type;

    enum loi{BERNOUILLI = 0, UNIFORM = 1};

        struct DistributionInfo {
            bool isBernouilli;
            bool isUniform;
            QString bernouilliAmount;
            QString uniformAmount;
        };
protected:
    bool ok;
    bool is_source_;
    bool is_due_;

    DistributionInfo distributionInfo_;

    GLfloat x_;
    GLfloat y_;

    static std::mutex mtx;

    node_id_type id_;
    Execution_history::time last_creation_;

    std::map<road_id_type, std::vector<Vehicle*>> waitingVehicles_;
    std::map<node_id_type, road_id_type> neighbours_;
    std::map<node_id_type, node_id_type> nextHopForDestination_;
    std::map<node_id_type, road_cost_type> costs_;
    std::queue<DVMessage> pendingDVMessages_;

    bool receiveDVMessage(DVMessage);
    void sendDVMessageToNeighbours();

    int currentWaitingVehicleIndex;
    // Utilises pour la generation des voitures

    std::default_random_engine generator_;
    std::bernoulli_distribution bernouilli_distribution_;

public:
    Node();
    ~Node(){}

    //Noeud(bool est_source);
    Node(GLfloat x, GLfloat y);
    Node(GLfloat x, GLfloat y, node_id_type id, bool isSource);
    Node(GLfloat x, GLfloat y, node_id_type id, bool isSource, DistributionInfo distributionInfo);

    bool is_source();
    bool is_due();
    Vehicle* create_vehicle();

    GLfloat x() const;
    GLfloat y() const;
    node_id_type GetId();

    bool processDVMessages();

    void startDV();
    void addNeighbour(node_id_type, road_id_type);
    void printDVResults();

    node_id_type getNextStep(node_id_type destination);
    road_id_type getNextRoad(node_id_type destination);

    Node& getNode(node_id_type);
    Road& getRoad(road_id_type);
    std::vector<Vehicle*> getWaitingVehicles(road_id_type);

    void addToWaitingVehicles(Vehicle*);
    virtual void processWaitingVehicles();
};

#endif // POINT_H
