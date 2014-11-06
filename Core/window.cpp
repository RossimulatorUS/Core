#include <QtWidgets>
#include <iostream>
#include <cmath>

#include "window.h"
#include "ui_window.h"

#include "simulationdata.h"
#include "map_fetcher.h"

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

        std::vector<Node*> allNodes = SimulationData::getInstance().getNodes();
        for(auto itt = allNodes.begin() ; itt != allNodes.end() ; ++itt)
        {
            (*itt)->startDV();
        }
        while(dvEnCours)
        {
            dvEnCours = false;
            for(auto itt = allNodes.begin() ; itt != allNodes.end() ; ++itt)
            {
                dvEnCours |= (*itt)->processDVMessages();
            }
        }

        for(auto itt = allNodes.begin() ; itt != allNodes.end() ; ++itt)
        {
            (*itt)->printDVResults();
        }

        cortex = new Cortex(SimulationData::getInstance().getNodes(), SimulationData::getInstance().getVehiclesPointer());

        // OpenGL refresh
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), ui->myGLWidget, SLOT(updateGL()));
        timer->start(cortex->opengl_fps());

        ui->m_boutonStartSimulation->setText("End");
    }
    // Terminate the simulation
    else
    {
        timer->stop();
        cortex->terminate();
        delete cortex;
        cortex = nullptr;

        SimulationData::getInstance().resetAllData();
        ui->myGLWidget->updateGL();

        ui->m_boutonStartSimulation->setText("Start");
    }

}

void Window::on_m_boutonSimulation1_clicked()
{
    ui->myGLWidget->clearWidget();

    ui->myGLWidget->DrawSource(0.0f,1.6f);
    ui->myGLWidget->DrawSource(0.0f,-1.6f);
    ui->myGLWidget->AddRoad(0, 1);

    ui->myGLWidget->updateGL();
}

void Window::on_m_boutonSimulation4_clicked()
{
    ui->myGLWidget->clearWidget();

    ui->myGLWidget->DrawSource(0.0f,1.6f);
    ui->myGLWidget->DrawSource(1.6f,0.0f);
    ui->myGLWidget->DrawSource(-1.6f,0.0f);
    ui->myGLWidget->DrawSource(0.0f,-1.6f);

    ui->myGLWidget->DrawNode(0.0f,0.0f);
    ui->myGLWidget->AddRoad(0, 4);
    ui->myGLWidget->AddRoad(1, 4);
    ui->myGLWidget->AddRoad(2, 4);
    ui->myGLWidget->AddRoad(3, 4);

    ui->myGLWidget->updateGL();
}

void Window::on_pushButton_clicked() // Works only for north western quadran
{
    std::cout << "initialising\n" << std::flush;
    ui->myGLWidget->clearWidget();

    double south = ui->m_lineEditSouth->text().toDouble();
    double west = ui->m_lineEditWest->text().toDouble();
    double north = ui->m_lineEditNorth->text().toDouble();
    double east = ui->m_lineEditEast->text().toDouble();

    auto hauteur_carte = std::abs(north - south);
    auto largeur_carte = std::abs(east - west);

    std::cout << "fetching\n" << std::flush;
    map_fetcher map(south, west, north, east);
    map.fetch();

    std::cout << "adding nodes\n" << std::flush;
    auto nodes = map.get_nodes();
    for(auto it = nodes.begin(); it != nodes.end(); ++it)
    {
        double longitude = (it->second.longitude() - east) / largeur_carte;
        double lattitude = (it->second.lattitude() - south) / hauteur_carte;

        ui->myGLWidget->DrawSource(longitude, lattitude);
    }

    std::cout << "adding roads\n" << std::flush;
    // Create road class that takes a vector<road_segment>

    std::cout << "updating gl\n" << std::flush;
    ui->myGLWidget->updateGL();
}
