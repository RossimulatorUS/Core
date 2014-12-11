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
    addTreeRoot("Nodes");
    //addTreeRoot("Lanes");

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

std::string Window::getRoadName()
{
    QString name = ui->m_editTextRoadName->text();
    std::string text = name.toLocal8Bit().constData();
    return text;
}

int Window::getNumberofLane()
{
    return ui->m_spinBoxNombreDeVoies->value();
}

simulation_traits::node_id_type Window::drawNode(GLfloat x, GLfloat y)
{
    update_actual_node_model();

    if(actual_node_model.is_source)
    {
        return SimulationData::getInstance().add_source(x,
                                                        y,
                                                        actual_node_model.intersection_type,
                                                        actual_node_model.distribution_law,
                                                        actual_node_model.law_coefficient);
    }
    else
    {
        return SimulationData::getInstance().add_intersection(x,
                                                              y,
                                                              actual_node_model.intersection_type);
    }
}

int Window::getCurrentTabIndex()
{
    return ui->Display->currentIndex();
}

void Window::keyPressEvent(QKeyEvent *e)
{
    qDebug() << e->key();
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
    rootItem_.push_back(treeItem);
    treeItem->setText(0, name);
}

std::vector<QTreeWidgetItem *> Window::getRootItem()const
{
    return rootItem_;
}

void Window::setRootItem(std::vector<QTreeWidgetItem *> rootItem)
{
    rootItem_ = rootItem;
}

// Beginning the simulation
void Window::on_m_boutonStartSimulation_clicked()
{
    connectListWidget();

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

    drawNode(0.0f, 1.6f);
    drawNode(0.0f, -1.6f);
    ui->myGLWidget->AddRoad(0, 1, "Pas cool");

    ui->myGLWidget->updateGL();
}

void Window::on_m_boutonSimulation4_clicked()
{
    ui->myGLWidget->clearWidget();

    drawNode(0.0, 1.6);
    drawNode(1.6, 0.0);
    drawNode(-1.6, 0.0);
    drawNode(0.0, -1.6);
    drawNode(0.0f, 0.0f);

    ui->myGLWidget->AddRoad(0, 4, "Thibault");
    ui->myGLWidget->AddRoad(1, 4, "Bertrand");
    ui->myGLWidget->AddRoad(2, 4, "Thibodeau");
    ui->myGLWidget->AddRoad(3, 4, "T LAITE");

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
    for(size_t i=0; i < ways.size(); ++i)
    {
        std::vector<node_id_type> path = ways[i].path;
        std::map<node_id_type,Node*>& allNodes = SimulationData::getInstance().getNodes();

        for(size_t j = 0; j < (path.size() - 1); ++j)
        {
            if((nodes.find(path[j]) != nodes.end()) && (nodes.find(path[j+1]) != nodes.end()))
            {
                if(allNodes.find(path[j]) == allNodes.end())
                {
                    double longitude = scale * (nodes[path[j]].longitude() - east) / largeur_carte;
                    double lattitude = scale * (nodes[path[j]].lattitude() - south) / hauteur_carte;

                    // TODO : Check coefficients
                    (j == 0) ? SimulationData::getInstance().add_source(longitude, lattitude, simulation_traits::STOPSIGN, simulation_traits::BERNOUILLI, 0.08, path[j])
                             : SimulationData::getInstance().add_intersection(longitude, lattitude, simulation_traits::STOPSIGN, path[j]);
                }
                if(allNodes.find(path[j+1]) == allNodes.end())
                {
                    qDebug() << "SECOND IF = " << path[j+1];
                    double longitude = scale * (nodes[path[j+1]].longitude() - east) / largeur_carte;
                    double lattitude = scale * (nodes[path[j+1]].lattitude() - south) / hauteur_carte;

                    (j == (path.size() - 1)) ? SimulationData::getInstance().add_intersection(longitude, lattitude, simulation_traits::STOPSIGN, path[j+1])
                                             : SimulationData::getInstance().add_source(longitude, lattitude, simulation_traits::STOPSIGN, simulation_traits::BERNOUILLI, 0.08, path[j+1]);
                }
                ui->myGLWidget->AddRoad(path[j],path[j+1], ways[i].attributes["name"]);
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
    for (size_t i = 0; i < roadNames.size(); ++i)
    {
        auto roadTreeItem = addTreeChild(rootItem_[0], QString::fromStdString(roadNames[i].getRoadName()));
        for(size_t i = 0; i < roadNames[i].getLanes().size(); ++i)
        {
            QString laneName = QString::fromStdString(stringify(i));
            addTreeChild(roadTreeItem, laneName);
        }
    }
}

void Window::addNameToListWidget(RoadSegment roadName)
{
    auto roadTreeItem = addTreeChild(rootItem_[0], QString::fromStdString(roadName.getRoadName()));
    for(size_t i = 0; i < roadName.getLanes().size(); ++i)
    {
        QString laneName = QString::fromStdString(stringify(i));
        addTreeChild(roadTreeItem, laneName);
    }

}

void Window::addNameToListWidget(node_id_type id)
{
    QString qstr = QString::fromStdString(stringify(id));
    addTreeChild(rootItem_[1], qstr);
}

void Window::setStats(Stats type, RoadSegment road, Lane *lane)
{
    if (type == Stats::Roads)
        setTextEditRoad(road);
    else if (type == Stats::Lanes)
        setTextEditLane(lane);

}

void Window::setCurrentTab(Window::TabWidget type, Node &selectedNode)
{
    ui->Display->setCurrentIndex((int)type);

    ui->is_source->setChecked(selectedNode.is_source());
    ui->distribution_law->setCurrentIndex(law_to_comboboxindex(selectedNode.loi_distribution()));
    ui->law_coefficient->setText(QString::fromStdString(stringify(selectedNode.law_coefficient())));
    ui->intersection_behavior->setCurrentIndex(intersectionbehavior_to_comboboxindex(selectedNode.intersection_behavior()));
}

void Window::setCurrentTab(Window::TabWidget type, RoadSegment &selectedRoad)
{
    ui->Display->setCurrentIndex((int)type);

    QString roadName = QString::fromStdString(selectedRoad.getRoadName());

    ui->m_editTextRoadName->setText(roadName);
    ui->m_spinBoxNombreDeVoies->setValue(selectedRoad.GetNumberOfLanes());
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
    return widget->isChecked();
}

QString Window::get_text(QLineEdit* widget)
{
    return widget->text();
}

// Should be integrated to simulation status
void Window::update_actual_node_model()
{
    actual_node_model.is_source = ui->is_source->isChecked();
    actual_node_model.law_coefficient = (actual_node_model.is_source ? ui->law_coefficient->text().toDouble() : 0);

    switch(ui->distribution_law->currentIndex())
    {
        case 0 : actual_node_model.distribution_law = simulation_traits::UNIFORM; break;
        case 1 : actual_node_model.distribution_law = simulation_traits::BERNOUILLI; break;
        case 2 : actual_node_model.distribution_law = simulation_traits::EXPONENTIAL; break;
    }

    switch(ui->intersection_behavior->currentIndex())
    {
        case 0 : actual_node_model.intersection_type = simulation_traits::GO; break;
        case 1 : actual_node_model.intersection_type = simulation_traits::STOPSIGN; break;
        case 2 : actual_node_model.intersection_type = simulation_traits::TLIGHT; break;
    }
}

void Window::on_m_boutonBlockRoad_clicked()
{
    bool dvEnCours = true;

    ui->myGLWidget->BlockRoad();

    auto allNodes = SimulationData::getInstance().getNodes();
    for(auto itt = allNodes.begin() ; itt != allNodes.end() ; ++itt)
    {
        (*itt).second->startDV();
    }
    while(dvEnCours)
    {
        dvEnCours = false;
        for(auto itt = allNodes.begin() ; itt != allNodes.end() ; ++itt)
        {
            dvEnCours |= (*itt).second->processDVMessages();
        }
    }

    for(auto itt = allNodes.begin() ; itt != allNodes.end() ; ++itt)
    {
        (*itt).second->printDVResults();
    }

    selectedItem_->setBackground(0, QBrush(QColor(1,0,0), Qt::BrushStyle::FDiagPattern));
}

void Window::on_m_boutonUnblockRoad_clicked()
{
    bool dvEnCours = true;

    ui->myGLWidget->UnBlockRoad();

    auto allNodes = SimulationData::getInstance().getNodes();
    for(auto itt = allNodes.begin() ; itt != allNodes.end() ; ++itt)
    {
        (*itt).second->startDV();
    }
    while(dvEnCours)
    {
        dvEnCours = false;
        for(auto itt = allNodes.begin() ; itt != allNodes.end() ; ++itt)
        {
            dvEnCours |= (*itt).second->processDVMessages();
        }
    }

    for(auto itt = allNodes.begin() ; itt != allNodes.end() ; ++itt)
    {
        (*itt).second->printDVResults();
    }

    selectedItem_->setBackground(0, QBrush(QColor(1,0,0), Qt::BrushStyle::NoBrush));
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

void Window::on_m_boutonDrawSource_clicked()
{
    ui->myGLWidget->isDrawNodePressed_ = true;
    ui->myGLWidget->isDrawRoadPressed_ = false;
    ui->myGLWidget->isDrawLanePressed_ = false;
    ui->myGLWidget->isDrawSourcePressed_ = false;
}

void Window::on_m_boutonDrawRoad_clicked()
{
    ui->myGLWidget->isDrawNodePressed_ = false;
    ui->myGLWidget->isDrawRoadPressed_ = true;
    ui->myGLWidget->isDrawLanePressed_ = false;
    ui->myGLWidget->isDrawSourcePressed_ = false;
}

void Window::on_m_boutonUpdateDistribution_clicked()
{
    if (ui->myGLWidget->selectedNode() < 0)
        return;

    // TODO give to option to update
    /*Node& selectedNode = SimulationData::getInstance().getNode(ui->myGLWidget->selectedNode());

    if (ui->m_radioButtonBernouilli->isChecked())
        selectedNode.setBernouilliAmount(ui->m_lineEditTauxBernouilli->text().toDouble());
    else if (ui->m_radioButtonExponentielle->isChecked())
        selectedNode.setExponentialAmount(ui->m_lineEditTauxExponentielle->text().toDouble());
    else if (ui->m_radioButtonUniforme->isChecked())
        selectedNode.setUniformAmount(ui->m_lineEditTauxUniforme->text().toDouble());*/
}
