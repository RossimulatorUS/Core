#include <QtWidgets>
#include <iostream>

#include "window.h"
#include "ui_window.h"

#include "node.h"
#include "road.h"
#include "simulationdata.h"

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

QString Window::getBernouilliAmount()
{
    return ui->m_lineEditTauxBernouilli->text();
}

QString Window::getUniformAmount()
{
    return ui->m_lineEditTauxUniforme->text();
}

QString Window::getExponentialAmount()
{
    return ui->m_lineEditTauxExponentielle->text();
}

bool Window::isBernouilliChecked()
{
    return ui->m_radioButtonBernouilli->isChecked();
}

bool Window::isOneWay()
{
    return ui->m_checkboxOneWay->isChecked();
}

bool Window::isUniformChecked()
{
    return ui->m_radioButtonUniforme->isChecked();
}

bool Window::isExponentialChecked()
{
    return ui->m_radioButtonExponentielle->isChecked();
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

// Beginning the simulation
void Window::on_m_boutonStartSimulation_clicked()
{
    if(ui->m_boutonStartSimulation->text() == "Start")
    {
        bool dvEnCours = true;

        auto& allNodes = SimulationData::getInstance().getNodes();
        for(auto itt = allNodes.begin() ; itt != allNodes.end() ; ++itt)
        {
            itt->startDV();
        }
        while(dvEnCours)
        {
            dvEnCours = false;
            for(auto itt = allNodes.begin() ; itt != allNodes.end() ; ++itt)
            {
                dvEnCours |= itt->processDVMessages();
            }
        }

        for(auto itt = allNodes.begin() ; itt != allNodes.end() ; ++itt)
        {
            itt->printDVResults();
        }

        cortex = new Cortex(SimulationData::getInstance().getNodes(), SimulationData::getInstance().getVehiclesPointer());

        ui->m_boutonStartSimulation->setText("End");
    }
    else
    {
        ui->m_boutonStartSimulation->setText("Start");
    }

}


// Drawing stuff
void Window::DrawNode(float *worldCoords)
{
    DrawNode(worldCoords[0], worldCoords[1]);
}

void Window::DrawNode(float x, float y)
{
    SimulationData::getInstance().addNode(x,y, false);
}

void Window::AddRoad(node_id_type a, node_id_type b)
{

    auto isOneWay_ = isOneWay();
    auto numberOfLane = getNumberofLane();

    Road newRoad = Road(a, b, isOneWay_, numberOfLane);
    auto roadId = SimulationData::getInstance().addRoad(newRoad);
    SimulationData::getInstance().getNode(a).addNeighbour(b, roadId);
    SimulationData::getInstance().getNode(b).addNeighbour(a, roadId);

    auto& r0 = SimulationData::getInstance().getRoad(roadId);

    for(int i = 1; i <= numberOfLane; ++i)
    {
        r0.addLane(r0.getStartNode(), r0.getEndNode(), i);

        if (!isOneWay_)
            r0.addLane(r0.getEndNode(), r0.getStartNode(), i);
    }

    SimulationData::getInstance().getNode(a).addLanes(roadId);
    SimulationData::getInstance().getNode(b).addLanes(roadId);
}

void Window::DrawSource(float *worldCoords)
{
    DrawSource(worldCoords[0], worldCoords[1]);
}

void Window::DrawSource(float x, float y)
{
    auto distribution = Node::DistributionInfo();

    distribution.isBernouilli = isBernouilliChecked();
    distribution.isUniform = isUniformChecked();
    distribution.isExponential =isExponentialChecked();

    distribution.bernouilliAmount = getBernouilliAmount();
    distribution.uniformAmount = getUniformAmount();
    distribution.exponentialAmount = getExponentialAmount();

    SimulationData::getInstance().addNode(x,y, true, distribution);
}

void Window::on_m_boutonSimulation1_clicked()
{
    ui->myGLWidget->clearWidget();

    DrawSource(0.0f,1.6f);
    DrawSource(0.0f,-1.6f);
    AddRoad(0, 1);

    ui->myGLWidget->updateGL();
}

void Window::on_m_boutonSimulation4_clicked()
{
    ui->myGLWidget->clearWidget();

    DrawSource(0.0f,1.6f);
    DrawSource(1.6f,0.0f);
    DrawSource(-1.6f,0.0f);
    DrawSource(0.0f,-1.6f);

    DrawNode(0.0f,0.0f);
    AddRoad(0, 4);
    AddRoad(1, 4);
    AddRoad(2, 4);
    AddRoad(3, 4);

    ui->myGLWidget->updateGL();
}
