#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QString>
#include <QtWidgets>
#include "cortex.h"
#include "simulationtraits.h"

namespace Ui {
class Window;
}

class Window : public QWidget
{
    Q_OBJECT

public:
    enum class Stats {Roads, Lanes};

    explicit Window(QWidget *parent = 0);
    ~Window();

    using node_id_type = simulation_traits::node_id_type;

    QString getBernouilliAmount();
    QString getUniformAmount();
    QString getExponentialAmount();

    bool isBernouilliChecked();
    bool isUniformChecked();
    bool isExponentialChecked();
    bool isIntersectionChecked();
    bool isSourceChecked();

    bool isOneWay();

    void setRoadNameListWidget(vector<RoadSegment> roadNames);
    void addNameToListWidget(RoadSegment roadName);
    void setStats(Stats type, RoadSegment road, Lane *lane);

    void connectListWidget();
    void hideBlockRoadButton();
    void showBlockRoadButton();

    QTreeWidgetItem *getRootItem() const;
    void setRootItem(QTreeWidgetItem *rootItem);

    int getCurrentTabIndex();
    int getNumberofLane();

    Cortex* cortex;
    QTimer* timer;

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
    void on_currentScale_textChanged(const QString &arg1);

    void on_xOffset_textChanged(const QString &arg1);

    void on_yOffset_textChanged(const QString &arg1);

    void on_offsetUp_clicked();

    void on_offsetRight_clicked();

    void on_offsetDown_clicked();

    void on_offsetLeft_clicked();

private:
    Ui::Window *ui;
    QTreeWidgetItem* rootItem_;
    QTreeWidgetItem* selectedItem_;

    void addTreeRoot(QString name);

    QTreeWidgetItem *addTreeChild(QTreeWidgetItem *parent, QString name);

    void setTextEditRoad(RoadSegment road);
    void setTextEditLane(Lane *lane);
};

#endif // WINDOW_H
