#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <QFile>
#include <vector>

#include "noeud.h"
#include "route.h"
#include "vehicule.h"
#include "simulationtraits.h"

class MyGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    MyGLWidget(QWidget *parent = 0);
    ~MyGLWidget();
    using node_id_type = typename simulation_traits::node_id_type;
    using road_id_type = typename simulation_traits::road_id_type;
    using road_cost_type = typename simulation_traits::road_cost_type;
signals:

public slots:

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

public slots:
    //slots for xyz-rotation slider
    void CreateSimulation1();
    void CreateSimulation4();
    //void CreateSimulation5();

    void StartSimulation();

    void DrawRoadPressed();
    void DrawNodePressed();
    void DrawLanePressed();
    void DrawSourcePressed();

    void ClearWidget();

signals:

private:
    constexpr static float ClickErrorTollerence = 0.1f;

    // pour test
    Vehicule* vehicule;

    std::vector<Noeud> &GetAllNodes();
    std::vector<Route> GetAllRoads();
    std::list<Vehicule*> GetAllVehicules();
    std::vector<Vehicule*> allVehicules_;

    node_id_type ClickPressedNode;
    node_id_type FindAssociatedNode(Noeud noeud);

    bool isDrawNodePressed_;
    bool isDrawRoadPressed_;
    bool isDrawLanePressed_;
    bool isDrawSourcePressed_;

    void AddRoad(Noeud*, Noeud*);
    void AddRoad(node_id_type, node_id_type);
    void DrawSource(float *worldCoords);
    void DrawSource(float x, float y);
    void DrawNode(float *worldCoords);
    void DrawNode(float x, float y);
    void DrawRoadMousePressed(float *worldCoords);
    void DrawRoadMouseReleased(float *worldCoords);
    void DrawLaneMousePressed(float *worldCoords);
    void DrawLaneMouseReleased(float *worldCoords);

    Route &FindAssociatedRoad(Noeud noeud1, Noeud noeud2, Noeud &outNoeudDepart, Noeud &outNoeudArrivee, bool &isInverted);

    void clearWidget();
    void moveCar();
    void draw();
    void PrintNodeCoordinates(Noeud depart, Noeud arrivee);

    QFile file;
};

#endif // MYGLWIDGET_H
