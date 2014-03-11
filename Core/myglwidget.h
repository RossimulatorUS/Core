#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
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

    //virtual void keyPressEvent(QKeyEvent *e);

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    //void mouseMoveEvent(QMouseEvent *event);

public slots:
    //slots for xyz-rotation slider
    void CreateSimulation1();
    void CreateSimulation2();
    void CreateSimulation3();
    void CreateSimulation4();
    void CreateSimulation5();

    void StartSimulation();

    void DrawRoadPressed();
    void DrawNodePressed();

    void ClearWidget();
    //void setXRotation(int angle);
    //void setYRotation(int angle);
    //void setZRotation(int angle);

signals:
    //signaling rotation from mouse movement
    //void xRotationChanged(int angle);
    //void yRotationChanged(int angle);
    //void zRotationChanged(int angle);

private:
    bool isDrawNodePressed_;
    bool isDrawRoadPressed_;

    constexpr static float ClickErrorTollerence = 0.3f;

    void AddRoad(Noeud*, Noeud*);
    void AddRoad(node_id_type, node_id_type);
    void DrawNode(float *worldCoords);
    void DrawNode(float x, float y);
    void DrawRoadMousePressed(float *worldCoords);
    void DrawRoadMouseReleased(float *worldCoords);

    node_id_type FindAssociatedNode(Noeud noeud);

    void clearWidget();
    void moveCar();
    void draw();

    // pour test
    Vehicule* vehicule;

    /*
    std::vector<Noeud> allNodes_ = std::vector<Noeud>();
    std::vector<Route> allRoads_ = std::vector<Route>();
    std::vector<Vehicule> allVehicules_ = std::vector<Vehicule>();
    */

    std::vector<Noeud> &GetAllNodes();
    std::vector<Route> GetAllRoads();
    std::list<Vehicule*> GetAllVehicules();
    //std::vector<Noeud> allNodes_;
    //std::vector<Route> allRoads_;
    std::vector<Vehicule*> allVehicules_;

    node_id_type ClickPressedNode;
};

#endif // MYGLWIDGET_H
