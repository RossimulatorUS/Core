#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QString>

#include <QtWidgets>
#include <QAbstractButton>

#include "cortex.h"
#include "simulationtraits.h"

#include "simulationstatus.h"

namespace Ui {
class Window;
}

class Window : public QWidget
{
    Q_OBJECT

public:
    struct selected_node_type{
        simulation_traits::intersection intersection_type;

        bool is_source;
        simulation_traits::law distribution_law;
        double law_coefficient;
    };

    selected_node_type actual_node_model;

    enum class Stats {Roads, Lanes};
    enum class TabWidget {Node = 0, Road = 1};

    explicit Window(QWidget *parent = 0);
    ~Window();

    using node_id_type = simulation_traits::node_id_type;

    QString getBernouilliAmount();
    QString getUniformAmount();
    QString getExponentialAmount();
    std::string getRoadName();

    bool isBernouilliChecked();
    bool isUniformChecked();
    bool isExponentialChecked();
    bool isIntersectionChecked();
    bool isSourceChecked();
    bool isDrawNodeChecked();
    bool isDrawRoadChecked();
    bool isStopSignChecked();
    bool isTrafficLightChecked();

    void addNameToListWidget(node_id_type id);
    void addNameToListWidget(RoadSegment roadName);
    void setStats(Stats type, RoadSegment road, Lane *lane);
    void setCurrentTab(TabWidget type, Node &selectedNode);
    void setCurrentTab(Window::TabWidget type, RoadSegment &selectedRoad);

    void connectListWidget();
    void hideBlockRoadButton();
    void showBlockRoadButton();

    std::vector<QTreeWidgetItem*> getRootItem() const;
    void setRootItem(std::vector<QTreeWidgetItem*> rootItem);

    int getCurrentTabIndex();
    int getNumberofLane();

    SimulationStatus simulation_status;
    Cortex* cortex;
    QTimer* timer;

    simulation_traits::node_id_type drawNode(GLfloat x, GLfloat y);



protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_m_boutonStartSimulation_clicked();
    void on_m_boutonSimulation1_clicked();
    void on_m_boutonSimulation4_clicked();

    void on_pushButton_clicked();
    void onRoadListWidgetClicked(QTreeWidgetItem *, int);

    void on_m_boutonBlockRoad_clicked();
    void on_m_boutonUnblockRoad_clicked();

    void wheelEvent(QWheelEvent *event);

    void on_noIntersection_clicked();

    void on_StopSign_clicked();

    void on_TrafficLight_clicked();

    void on_m_boutonDrawSource_clicked();

    void on_m_boutonDrawRoad_clicked();

    void on_m_boutonUpdateDistribution_clicked();

private:
    Ui::Window *ui;
    std::vector<QTreeWidgetItem*> rootItem_;
    QTreeWidgetItem* selectedItem_;

    void addTreeRoot(QString name);

    void setRoadNameListWidget(std::vector<RoadSegment> roadNames);
    QTreeWidgetItem *addTreeChild(QTreeWidgetItem *parent, QString name);

    void setTextEditRoad(RoadSegment road);
    void setTextEditLane(Lane *lane);

    // Utils
    void enable(QWidget*);
    void disable(QWidget*);
    bool is_checked(QAbstractButton*);
    QString get_text(QAbstractButton*);
    QString get_text(QLineEdit*);

    void update_actual_node_model();
};

#endif // WINDOW_H
