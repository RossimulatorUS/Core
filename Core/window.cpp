#include <QtWidgets>
#include <QAbstractButton>

#include <iostream>

#include "window.h"
#include "ui_window.h"

#include "map_fetcher.h"
#include "utils.h"

#include "simulationdata.h"
#include "simulationstatus.h"

Window::Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);

    //Add the root nodes
    addTreeRoot("Roads");
    //addTreeRoot("Lanes");
    //addTreeRoot("Nodes");

    //showBlockRoadButton();
    disable(ui->m_treeWidget);
    disable(ui->m_boutonBlockRoad);
    disable(ui->m_boutonUnblockRoad);

    update_actual_node_model();
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
    return ui->m_isOneWay->isChecked();
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

void Window::drawNode()
{
    update_actual_node_model();

    if(actual_node_model.is_source)
    {
        //SimulationData::getInstance().add_source();
    }
    else
    {
        //SimulationData::getInstance().add_node();
    }
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
    return ui->Display->currentIndex();
}

void Window::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
        case Qt::Key_Escape:
            close();
            break;
        case Qt::Key_W:
            ui->myGLWidget->UpdateOffset(8);
            break;
        case Qt::Key_A:
            ui->myGLWidget->UpdateOffset(4);
            break;
        case Qt::Key_S:
            ui->myGLWidget->UpdateOffset(2);
            break;
        case Qt::Key_D:
            ui->myGLWidget->UpdateOffset(6);
            break;
        default:
            QWidget::keyPressEvent(e);
            break;
    }
}

void Window::addTreeRoot(QString name)
{
    QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->m_treeWidget);
    rootItem_ = treeItem;
    treeItem->setText(0, name);
}

QTreeWidgetItem *Window::getRootItem()const
{
    return rootItem_;
}

void Window::setRootItem(QTreeWidgetItem *rootItem)
{
    rootItem_ = rootItem;
}

// Beginning the simulation
void Window::on_m_boutonStartSimulation_clicked()
{
    if(ui->m_boutonStartSimulation->text() == "Start")
    {
        // Put in function
        disable(ui->m_boutonSimulation1);
        disable(ui->m_boutonSimulation4);
        disable(ui->Display);
        enable(ui->m_treeWidget);
        enable(ui->m_boutonBlockRoad);
        enable(ui->m_boutonUnblockRoad);
        disable(ui->m_groupBoxImportation);

        SimulationData::getInstance().runDv(true);

        cortex = new Cortex();

        // OpenGL refresh
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), ui->myGLWidget, SLOT(updateGL()));
        timer->start(SimulationData::getInstance().opengl_fps());

        ui->m_boutonStartSimulation->setText("End");
    }
    // Terminate the simulation
    else
    {
        enable(ui->m_boutonSimulation1);
        enable(ui->m_boutonSimulation4);
        enable(ui->Display);
        disable(ui->m_treeWidget);
        disable(ui->m_boutonBlockRoad);
        disable(ui->m_boutonUnblockRoad);
        enable(ui->m_groupBoxImportation);

        timer->stop();
        cortex->terminate();
        delete cortex;
        cortex = nullptr;

        SimulationData::getInstance().resetAllData();
        ui->myGLWidget->updateGL();

        ui->m_boutonStartSimulation->setText("Start");
    }
}

void Window::connectListWidget()
{
    connect(ui->m_treeWidget, SIGNAL(itemClicked(QTreeWidgetItem *, int)),
            this, SLOT(onRoadListWidgetClicked(QTreeWidgetItem *, int)));
}

void Window::hideBlockRoadButton()
{
    ui->m_boutonBlockRoad->setVisible(false);
    ui->m_boutonUnblockRoad->setVisible(true);
}

void Window::showBlockRoadButton()
{
    ui->m_boutonBlockRoad->setVisible(true);
    ui->m_boutonUnblockRoad->setVisible(false);
}

void Window::on_m_boutonSimulation1_clicked()
{
    ui->myGLWidget->clearWidget();

    ui->myGLWidget->DrawSource(0.0f,1.6f);
    ui->myGLWidget->DrawSource(0.0f,-1.6f);
    auto road = ui->myGLWidget->AddRoad(0, 1, "Pas cool");

    connectListWidget();
    setRoadNameListWidget(SimulationData::getInstance().getRoads());

    ui->myGLWidget->updateGL();
}

void Window::on_m_boutonSimulation4_clicked()
{
    ui->myGLWidget->clearWidget();

    ui->myGLWidget->DrawSource(0.0f,1.6f);
    ui->myGLWidget->DrawSource(1.6f,0.0f);
    ui->myGLWidget->DrawSource(-1.6f,0.0f);
    ui->myGLWidget->DrawSource(0.0f,-1.6f);

    ui->myGLWidget->DrawNode(0.0f,0.0f,1);
    auto road1 = ui->myGLWidget->AddRoad(0, 4, "Thibault");
    auto road2 = ui->myGLWidget->AddRoad(1, 4, "Bertrand");
    auto road3 = ui->myGLWidget->AddRoad(2, 4, "Thibodeau");
    auto road4 = ui->myGLWidget->AddRoad(3, 4, "T LAITE");

    connectListWidget();
    setRoadNameListWidget(SimulationData::getInstance().getRoads());

    ui->myGLWidget->updateGL();
}

void Window::on_pushButton_clicked() // Works only for north western quadran
{
    std::cout << "initialising\n" << std::flush;
    ui->myGLWidget->clearWidget();

    double south = get_text(ui->m_lineEditSouth).toDouble();
    double west = get_text(ui->m_lineEditWest).toDouble();
    double north = get_text(ui->m_lineEditNorth).toDouble();
    double east = get_text(ui->m_lineEditEast).toDouble();

    float scale = ui->m_scale->text().toDouble();

    auto hauteur_carte = std::abs(north - south);
    auto largeur_carte = std::abs(east - west);

    std::cout << "fetching\n" << std::flush;
    map_fetcher map(south, west, north, east);
    map.fetch();

    std::cout << "adding nodes\n" << std::flush;
    std::map<node_id_type, map_node> nodes = map.get_nodes();

    std::cout << "adding roads\n" << std::flush;
    std::vector<map_way> ways = map.get_ways();
    for(int i=0;i<ways.size(); ++i)
    {
        std::vector<node_id_type> path = ways[i].path;
        std::map<node_id_type,Node*> allNodes = SimulationData::getInstance().getNodes();

        for(auto j = 0; j < (path.size() - 1); ++j)
        {
            //if((allNodes.find(path[j]) != allNodes.end()) && (allNodes.find(path[j+1]) != allNodes.end()))
            if((nodes.find(path[j]) != nodes.end()) && (nodes.find(path[j+1]) != nodes.end()))
            {
                if(allNodes.find(path[j]) == allNodes.end())
                {
                    double longitude = scale * (nodes[path[j]].longitude() - east) / largeur_carte;
                    double lattitude = scale * (nodes[path[j]].lattitude() - south) / hauteur_carte;

                    (j == 0) ? ui->myGLWidget->DrawSource(longitude, lattitude,path[j]) : ui->myGLWidget->DrawNode(longitude, lattitude,path[j]);
                }
                if(allNodes.find(path[j+1]) == allNodes.end())
                {
                    double longitude = scale * (nodes[path[j+1]].longitude() - east) / largeur_carte;
                    double lattitude = scale * (nodes[path[j+1]].lattitude() - south) / hauteur_carte;

                    (j == (path.size() - 1)) ? ui->myGLWidget->DrawNode(longitude, lattitude,path[j+1]) : ui->myGLWidget->DrawSource(longitude, lattitude,path[j+1]);
                }
                ui->myGLWidget->AddRoad(path[j],path[j+1], "MATYLDE");
            }
        }

        // Create road in the system
        //Road(path);
    }

    std::cout << "updating gl\n" << std::flush;
    ui->myGLWidget->updateGL();
}

void Window::wheelEvent(QWheelEvent *event)
{
    int delta = event->delta();
    float scale = (float)delta/1000;
    ui->myGLWidget->UpdateScale(scale);
}

void Window::onRoadListWidgetClicked(QTreeWidgetItem *item, int i)
{
    ui->myGLWidget->onRoadListWidgetClicked(item, i);
    selectedItem_ = item;
}

QTreeWidgetItem* Window::addTreeChild(QTreeWidgetItem *parent, QString name)
{
    QTreeWidgetItem *treeItem = new QTreeWidgetItem();
    treeItem->setText(0, name);
    parent->addChild(treeItem);
    return treeItem;
}

void Window::setRoadNameListWidget(vector<RoadSegment> roadNames)
{
    for (auto i = 0; i < roadNames.size(); ++i)
    {
        QString qstr = QString::fromStdString(roadNames[i].getRoadName());
        auto roadTreeItem = addTreeChild(rootItem_, qstr);
        for(auto i = 0; i < roadNames[i].getLanes().size(); ++i)
        {
            QString laneName = QString::fromStdString(stringify(i));
            auto item = addTreeChild(roadTreeItem, laneName);
        }
    }
}

void Window::addNameToListWidget(RoadSegment roadName)
{
    QString qstr = QString::fromStdString(roadName.getRoadName());
    auto roadTreeItem = addTreeChild(rootItem_, qstr);
    for(auto i = 0; i < roadName.getLanes().size(); ++i)
    {
        QString laneName = QString::fromStdString(stringify(i));
        auto item = addTreeChild(roadTreeItem, laneName);
    }
}

bool Window::isDrawNodeChecked()
{
    ui->m_radioButtonSource->isChecked();
}

bool Window::isDrawRoadChecked()
{
    ui->m_boutonDrawRoad->isChecked();
}

bool Window::isStopSignChecked()
{
    ui->StopSign->isChecked();
}

bool Window::isTrafficLightChecked()
{
    ui->TrafficLight->isChecked();
}

void Window::setStats(Stats type, RoadSegment road, Lane *lane)
{
    if (type == Stats::Roads)
        setTextEditRoad(road);
    else if (type == Stats::Lanes)
        setTextEditLane(lane);
}

void Window::setTextEditRoad(RoadSegment road)
{
    auto textEdit = ui->m_statsTextEdit;

    QString actualNumberOfCar = QString::fromStdString(stringify(road.GetActualNumberOfCar()));
    QString totalNumberOfCar = QString::fromStdString(stringify(road.GetTotalNumberOfCar()));

    QString waitingCars = QString::fromStdString(stringify(road.getWaitingCars()));

    QString output = "Number of car on road : " + actualNumberOfCar + '\n' +
                     "Total number of car : " + totalNumberOfCar + '\n' +
                     "Number of unspawned cars: " + waitingCars + '\n' +
                     "Average elapsed time on road : TODO" + '\n';

    QString qstr = QString::fromStdString(road.getRoadName());
    textEdit->setText(output);
}

void Window::setTextEditLane(Lane *lane)
{
    auto textEdit = ui->m_statsTextEdit;

    QString actualNumberOfCar = QString::fromStdString(stringify(lane->getNumberOfVehicle()));
    QString totalNumberOfCar = QString::fromStdString(stringify(lane->getTotalNumberOfVehicle()));

    QString output = "Number of car on lane : " + actualNumberOfCar + '\n' +
                     "Total number of car : " + totalNumberOfCar + '\n' +
                     "Average elapsed time on road : TODO" + '\n';

    //QString qstr = QString::fromStdString(lane.getRoadName());
    textEdit->setText(output);
}

void Window::enable(QWidget* widget)
{
    widget->setEnabled(true);
}

void Window::disable(QWidget* widget)
{
    widget->setEnabled(false);
}

bool Window::is_checked(QAbstractButton* widget)
{
    widget->isChecked();
}

QString Window::get_text(QLineEdit* widget)
{
    widget->text();
}

void Window::update_actual_node_model()
{
    actual_node_model.is_source = isSourceChecked();

    if(isBernouilliChecked())
    {
        actual_node_model.distribution_law = simulation_traits::BERNOUILLI;
        actual_node_model.law_coefficient = getBernouilliAmount().toDouble();
    }
    else if(isUniformChecked())
    {
        actual_node_model.distribution_law = simulation_traits::UNIFORM;
        actual_node_model.law_coefficient = getUniformAmount().toDouble();
    }
    else if(isExponentialChecked())
    {
        actual_node_model.distribution_law = simulation_traits::EXPONENTIAL;
        actual_node_model.law_coefficient = getExponentialAmount().toDouble();
    }

    if(isStopSignChecked())
        actual_node_model.intersection_type = simulation_traits::STOPSIGN;
    else if(isTrafficLightChecked())
        actual_node_model.intersection_type = simulation_traits::TLIGHT;
    else
        actual_node_model.intersection_type = simulation_traits::GO;
}

void Window::on_m_boutonBlockRoad_clicked()
{
    /*bool dvEnCours = true;

    ui->myGLWidget->BlockRoad();

    auto allNodes = SimulationData::getInstance().getNodes();
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

    selectedItem_->setBackground(0, QBrush(QColor(1,0,0), Qt::BrushStyle::FDiagPattern));
    //Qt::BrushStyle::NoBrush*/

    //ui->myGLWidget->UpdateOffset(2);
    //ui->myGLWidget->updateGL();
}

void Window::on_m_boutonUnblockRoad_clicked()
{
    /*bool dvEnCours = true;

    ui->myGLWidget->UnBlockRoad();

    auto allNodes = SimulationData::getInstance().getNodes();
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

    selectedItem_->setBackground(0, QBrush(QColor(1,0,0), Qt::BrushStyle::NoBrush));*/

    //ui->myGLWidget->UpdateOffset(4);
    //ui->myGLWidget->updateGL();
}

void Window::on_noIntersection_clicked()
{
    ui->myGLWidget->setNodeType(0);
}

void Window::on_StopSign_clicked()
{
    ui->myGLWidget->setNodeType(1);
}

void Window::on_TrafficLight_clicked()
{
    ui->myGLWidget->setNodeType(2);
}
