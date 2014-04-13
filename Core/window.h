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

    QString getTauxBernouilli();
    QString getTauxUniforme();

    bool isBernouilliChecked();
    bool isUniformeChecked();
    bool isIntersectionChecked();
    bool isSourceChecked();

    int getCurrentTabIndex();
protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::Window *ui;
};

#endif // WINDOW_H
