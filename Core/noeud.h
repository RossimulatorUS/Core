#ifndef POINT_H
#define POINT_H

#include <QGLWidget>

#include <map>
#include <queue>
#include "dvutility.h"
#include <mutex>

class Route;    //forward declaration pour éviter un include cyclique ; include de route dans le cpp

class Noeud
{
public:
    using id_type = unsigned long long;
private:
    bool est_source_;
    bool est_du_;

    GLfloat x_;
    GLfloat y_;

    static std::mutex mtx;

    id_type id_;
    static id_type nextId_;
    std::map<Noeud*, Route*> neighbours_;
    std::map<Noeud*, Noeud*> nextHopForDestination_;
    std::map<Noeud*, typename DVMessage::cost_type> costs_;
    std::queue<DVMessage> pendingDVMessages_;

    bool ReceiveDVMessage(DVMessage);
    void SendDVMessageToNeighbours();
public:
    //Noeud(){}

    //Noeud(bool est_source);
    Noeud(GLfloat x, GLfloat y, bool isDummy = false);



    bool est_source();
    bool est_du();

    GLfloat x() const;
    GLfloat y() const;

    void StartDV();
    bool ProcessDVMessages();
    void AddNeighbour(Noeud*, Route*);
    void PrintDVResults();
    Noeud* GetProchaineEtape(Noeud* destination);
};

#endif // POINT_H
