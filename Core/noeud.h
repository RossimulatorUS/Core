#ifndef POINT_H
#define POINT_H

#include <QGLWidget>

#include <map>
#include <queue>
#include "dvutility.h"
#include <mutex>
#include "simulationtraits.h"

class Route;    //forward declaration pour éviter un include cyclique ; include de route dans le cpp

class Noeud
{
public:
    using node_id_type = typename simulation_traits::node_id_type;
    using road_id_type = typename simulation_traits::road_id_type;
    using road_cost_type = typename simulation_traits::road_cost_type;
private:
    bool est_source_;
    bool est_du_;

    GLfloat x_;
    GLfloat y_;

    static std::mutex mtx;

    node_id_type id_;
    std::map<node_id_type, road_id_type> neighbours_;
    std::map<node_id_type, node_id_type> nextHopForDestination_;
    std::map<node_id_type, road_cost_type> costs_;
    std::queue<DVMessage> pendingDVMessages_;

    bool ReceiveDVMessage(DVMessage);
    void SendDVMessageToNeighbours();
public:
    //Noeud(){}

    //Noeud(bool est_source);
    Noeud(GLfloat x, GLfloat y);
    Noeud(GLfloat x, GLfloat y, node_id_type id);

    bool est_source();
    bool est_du();

    GLfloat x() const;
    GLfloat y() const;
    node_id_type GetId();

    void StartDV();
    bool ProcessDVMessages();
    void AddNeighbour(node_id_type, road_id_type);
    void PrintDVResults();
    node_id_type GetProchaineEtape(node_id_type destination);
    road_id_type GetProchaineRoute(node_id_type destination);

    Noeud& GetNoeud(node_id_type);
    Route& GetRoute(road_id_type);
};

#endif // POINT_H
