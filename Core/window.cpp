#include <QtWidgets>
#include <iostream>

#include "window.h"
#include "ui_window.h"
#include "utils.h"

#include "simulationdata.h"
#include "map_fetcher.h"

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
    ui->m_treeWidget->setEnabled(false);
    ui->m_boutonBlockRoad->setEnabled(false);
    ui->m_boutonUnblockRoad->setEnabled(false);
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
        ui->m_boutonSimulation1->setEnabled(false);
        ui->m_boutonSimulation4->setEnabled(false);
        ui->Display->setEnabled(false);
        ui->m_treeWidget->setEnabled(true);
        ui->m_boutonBlockRoad->setEnabled(true);
        ui->m_boutonUnblockRoad->setEnabled(true);
        ui->m_groupBoxImportation->setEnabled(false);

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
        ui->m_boutonSimulation1->setEnabled(true);
        ui->m_boutonSimulation4->setEnabled(true);
        ui->Display->setEnabled(true);
        ui->m_treeWidget->setEnabled(false);
        ui->m_boutonBlockRoad->setEnabled(false);
        ui->m_boutonUnblockRoad->setEnabled(false);
        ui->m_groupBoxImportation->setEnabled(true);

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
    //ui->m_treeWidget->clear();

    ui->myGLWidget->DrawSource(0.0f,1.6f);
    ui->myGLWidget->DrawSource(1.6f,0.0f);
    ui->myGLWidget->DrawSource(-1.6f,0.0f);
    ui->myGLWidget->DrawSource(0.0f,-1.6f);

    ui->myGLWidget->DrawNode(0.0f,0.0f);
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

    double south = ui->m_lineEditSouth->text().toDouble();
    double west = ui->m_lineEditWest->text().toDouble();
    double north = ui->m_lineEditNorth->text().toDouble();
    double east = ui->m_lineEditEast->text().toDouble();

    auto map_height = std::abs(north - south);
    auto map_width = std::abs(east - west);

    std::cout << "fetching\n" << std::flush;
    map_fetcher map(south, west, north, east);
    map.fetch();

    std::cout << "adding nodes\n" << std::flush;
    auto nodes = map.get_nodes();

    float scale = ui->m_scale->text().toDouble();
    for(auto it = nodes.begin(); it != nodes.end(); ++it)
    {
        double longitude = scale * (it->second.longitude() - (it->second.longitude() < 0 ? east : west)) / map_width;
        double lattitude = scale * (it->second.lattitude() - (it->second.lattitude() < 0 ? north : south)) / map_height;

        ui->myGLWidget->DrawSource(longitude, lattitude, it->first);
    }

    std::cout << "adding roads\n" << std::flush;
    // Create road class that takes a vector<road_segment>

    SimulationData::getInstance().print_nodes();

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

    QString output = "Number of car on road : " + actualNumberOfCar + '\n' +
                     "Total number of car : " + totalNumberOfCar + '\n' +
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

void Window::on_m_boutonBlockRoad_clicked()
{
    bool dvEnCours = true;

    ui->myGLWidget->BlockRoad();

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

    selectedItem_->setBackground(0, QBrush(QColor(1,0,0), Qt::BrushStyle::FDiagPattern));
    //Qt::BrushStyle::NoBrush
}

void Window::on_m_boutonUnblockRoad_clicked()
{
    bool dvEnCours = true;

    ui->myGLWidget->UnBlockRoad();

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

    selectedItem_->setBackground(0, QBrush(QColor(1,0,0), Qt::BrushStyle::NoBrush));
}
