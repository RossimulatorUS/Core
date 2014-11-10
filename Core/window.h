#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QString>

#include "cortex.h"
#include "simulationtraits.h"

namespace Ui {
class Window;
}

class Window : public QWidget
{
    Q_OBJECT

public:
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

    void on_currentScale_textChanged(const QString &arg1);

    void on_xOffset_textChanged(const QString &arg1);

    void on_yOffset_textChanged(const QString &arg1);

    void on_offsetUp_clicked();

    void on_offsetRight_clicked();

    void on_offsetDown_clicked();

    void on_offsetLeft_clicked();

private:
    Ui::Window *ui;
};

#endif // WINDOW_H
