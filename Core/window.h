#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QString>

namespace Ui {
class Window;
}

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();

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
protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::Window *ui;
};

#endif // WINDOW_H
