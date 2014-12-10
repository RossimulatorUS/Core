#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <QFile>
#include <vector>

#include "node.h"
#include "road_segment.h"
#include "vehicle.h"
#include "simulationtraits.h"
#include "window.h"

#include <map>

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

    void BlockRoad();
    void UnBlockRoad();
    node_id_type selectedNode() const;
    void setSelectedNode(const node_id_type &selectedNode);

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
    void UpdateScale(float s);
    void UpdateXOffset(float x);
    void UpdateYOffset(float y);
    void UpdateOffset(int which);
    void setNodeType(int what);

    void onRoadListWidgetClicked(QTreeWidgetItem *item, int i);

signals:

private:
    constexpr static float ClickErrorTollerence = 0.1f;

    // pour test
    Vehicle* vehicule;

    std::map<node_id_type,Node*>& GetAllNodes();
    std::vector<RoadSegment>& GetAllRoads();
    std::list<Vehicle*>& GetAllVehicles();
    std::vector<Vehicle*> allVehicles_;

    node_id_type clickPressedNode;
    node_id_type FindAssociatedNode(float x, float y);

    QTreeWidgetItem* selectedRoadItem_;
    QTreeWidgetItem* selectedLaneItem_;

    RoadSegment selectedRoad_;
    Lane *selectedLane;
    node_id_type selectedNode_;

    bool isDrawNodePressed_;
    bool isDrawRoadPressed_;
    bool isDrawLanePressed_;
    bool isDrawSourcePressed_;
    bool isLaneSelected_;
    bool isRoadSelected_;

    int nodeType;

    float scale,xOffset,yOffset;

    void AddRoad(Node*, Node*);
    RoadSegment AddRoad(node_id_type, node_id_type, std::string name);
    void DrawSource(float *worldCoords, int type=0);
    void DrawSource(float x, float y, int type=0);
    void DrawSource(float x, float y, node_id_type id, int type=0);
    void DrawNode(float *worldCoords, int type=0);
    void DrawNode(float x, float y, int type=0);
    void DrawNode(float x, float y, node_id_type id, int type=0);
    void DrawRoadMousePressed(float *worldCoords);
    void DrawRoadMouseReleased(float *worldCoords);

    //Road* FindAssociatedRoad(Node* node1, Node* node2, Node &outStartNode, Node &outEndNode, bool &isInverted);

    void moveCar();

    QFile file;
};

#endif // MYGLWIDGET_H
