#include <QtWidgets>

#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
}

Window::~Window()
{
    delete ui;
}

QString Window::getTauxBernouilli()
{
    return ui->m_lineEditTauxBernouilli->text();
}

QString Window::getTauxUniforme()
{
    return ui->m_lineEditTauxUniforme->text();
}

bool Window::isBernouilliChecked()
{
    return ui->m_radioButtonBernouilli->isChecked();
}

bool Window::isOneWay()
{
    return ui->m_checkboxOneWay->isChecked();
}

bool Window::isUniformeChecked()
{
    return ui->m_radioButtonUniforme->isChecked();
}

int Window::getNumberofLane()
{
    return ui->m_spinBoxNombreDeVoies->value();
}

bool Window::isIntersectionChecked()
{
    return ui->m_radioButtonIntersection->isChecked();
}

bool Window::isSourceChecked()
{
    return ui->m_radioButtonSource->isChecked();
}

int Window::getCurrentTabIndex()
{
    return ui->m_tabSimulation->currentIndex();
}

void Window::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}

