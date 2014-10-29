#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <QFile>
#include <vector>

#include "node.h"
#include "road.h"
#include "vehicle.h"
#include "simulationtraits.h"
#include "window.h"

class MyGLWidget : public QGLWidget
{
    Q_OBJECT
    friend class Window;

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

    void DrawRoadPressed();
    void DrawNodePressed();
    void DrawLanePressed();
    void DrawSourcePressed();

    void ClearWidget();
    void clearWidget();
    void draw();

signals:

private:
    constexpr static float ClickErrorTollerence = 0.1f;

    // pour test
    Vehicle* vehicule;

    std::vector<Node>& GetAllNodes();
    std::vector<Road>& GetAllRoads();
    std::list<Vehicle*>& GetAllVehicles();
    std::vector<Vehicle*> allVehicles_;

    node_id_type clickPressedNode;
    node_id_type FindAssociatedNode(Node noeud);

    bool isDrawNodePressed_;
    bool isDrawRoadPressed_;
    bool isDrawLanePressed_;
    bool isDrawSourcePressed_;

    void AddRoad(Node*, Node*);
    void AddRoad(node_id_type, node_id_type);
    void DrawSource(float *worldCoords);
    void DrawSource(float x, float y);
    void DrawNode(float *worldCoords);
    void DrawNode(float x, float y);
    void DrawRoadMousePressed(float *worldCoords);
    void DrawRoadMouseReleased(float *worldCoords);

    //Road* FindAssociatedRoad(Node* node1, Node* node2, Node &outStartNode, Node &outEndNode, bool &isInverted);

    void moveCar();

    QFile file;
};

#endif // MYGLWIDGET_H
