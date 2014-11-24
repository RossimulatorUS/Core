#include <QtWidgets>
#include <QtOpenGL>
#include <iostream>

#include "myglwidget.h"
#include "glutility.h"
#include "simulationdata.h"


MyGLWidget::MyGLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent), file("Vehicule data.txt"),
      scale(1.0f),xOffset(0.0f),yOffset(0.0f)
{
    glDisable(GL_DEPTH_TEST);
    setMouseTracking(true);
    isDrawNodePressed_ = true;
    isDrawRoadPressed_ = false;
    isDrawLanePressed_ = false;
    isDrawSourcePressed_ = false;

    selectedLaneItem_ = new QTreeWidgetItem();
    selectedRoadItem_ = new QTreeWidgetItem();

    isLaneSelected_ = false;
    isRoadSelected_ = false;

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
}

MyGLWidget::~MyGLWidget()
{

}

void MyGLWidget::BlockRoad()
{
    auto allNodes = GetAllNodes();
    for (auto itt = allNodes.begin(); itt != allNodes.end(); ++itt)
    {
        (*itt).second->resetCosts();
    }

    auto road = SimulationData::getInstance().getRoad(selectedRoad_.getRoadID());
    qDebug() << "Blocking road " << road.getRoadID();
    road.BlockRoad();
    road.isBlocked_ = true;
}

void MyGLWidget::UnBlockRoad()
{
    auto allNodes = GetAllNodes();
    for (auto itt = allNodes.begin(); itt != allNodes.end(); ++itt)
    {
        (*itt).second->resetCosts();
    }

    auto road = SimulationData::getInstance().getRoad(selectedRoad_.getRoadID());
    qDebug() << "UnBlocking road " << road.getRoadID();
    road.UnBlockRoad();
    road.isBlocked_ = false;
}

void MyGLWidget::initializeGL()
{
    //couleur du background
    qglClearColor(Qt::black);

    //2d means no depth!
    glDisable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;
}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0, 0, -10);

    draw();
}

void MyGLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //glOrtho(0,height,width,0,0,1);
#ifdef QT_OPENGL_ES_1
    glOrthof(-2, +2, -2, +2, 1.0, 15.0);
#else
    glOrtho(-2, +2, -2, +2, 1.0, 15.0);
#endif

    glMatrixMode(GL_MODELVIEW);
}

void MyGLWidget::mousePressEvent(QMouseEvent *event)
{
    int x = event->pos().x();
    int y = event->pos().y();

    GLint viewport[4]; //var to hold the viewport info
    GLfloat modelview[16]; //var to hold the modelview info
    GLfloat projection[16]; //var to hold the projection matrix info
    GLfloat winX, winY, winZ; //variables to hold screen x,y,z coordinates
    GLfloat worldCoords[3]; //variables to hold world x,y,z coordinates

    glGetFloatv( GL_MODELVIEW_MATRIX, modelview ); //get the modelview info
    glGetFloatv( GL_PROJECTION_MATRIX, projection ); //get the projection matrix info
    glGetIntegerv( GL_VIEWPORT, viewport ); //get the viewport info

    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    winZ = 0;

    GLUtility::unProject(winX, winY, winZ, modelview, projection, viewport, worldCoords );

    auto window = static_cast<Window*>(parent());

    if (window->isIntersectionChecked() && window->getCurrentTabIndex() == 0)
        DrawNode(worldCoords, nodeType);
    else if (isDrawRoadPressed_ && window->getCurrentTabIndex() == 1)
        DrawRoadMousePressed(worldCoords);
    /*else if (isDrawLanePressed_)
        DrawLaneMousePressed(worldCoords);*/
    else if (window->isSourceChecked())
        DrawSource(worldCoords, nodeType);
    else
    {
        //other things later (perturbation stats)
    }

    //Refresh le widget OpenGL
    updateGL();
}

void MyGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    int x = event->pos().x();
    int y = event->pos().y();

    GLint viewport[4]; //var to hold the viewport info
    GLfloat modelview[16]; //var to hold the modelview info
    GLfloat projection[16]; //var to hold the projection matrix info
    GLfloat winX, winY, winZ; //variables to hold screen x,y,z coordinates
    GLfloat worldCoords[3]; //variables to hold world x,y,z coordinates

    glGetFloatv( GL_MODELVIEW_MATRIX, modelview ); //get the modelview info
    glGetFloatv( GL_PROJECTION_MATRIX, projection ); //get the projection matrix info
    glGetIntegerv( GL_VIEWPORT, viewport ); //get the viewport info

    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    winZ = 0;

    GLUtility::unProject(winX, winY, winZ, modelview, projection, viewport, worldCoords );

    if (isDrawRoadPressed_)
    {
        DrawRoadMouseReleased(worldCoords);
        updateGL();
    }
}

void MyGLWidget::DrawRoadMouseReleased(float *worldCoords)
{
    auto window = static_cast<Window*>(parent());

    Node node = Node(worldCoords[0], worldCoords[1]);
    node_id_type associatedNode = FindAssociatedNode(node);

    if (clickPressedNode != associatedNode && clickPressedNode != 66666 && associatedNode != 66666)
    {
        std::string name = "JACYNTHE";
        auto newRoad = AddRoad(clickPressedNode, associatedNode, name);
        window->addNameToListWidget(newRoad);
    }
}

void MyGLWidget::DrawRoadMousePressed(float *worldCoords)
{
    Node node = Node(worldCoords[0], worldCoords[1]);
    node_id_type associatedNode = FindAssociatedNode(node);

    clickPressedNode = associatedNode;
}

MyGLWidget::node_id_type MyGLWidget::FindAssociatedNode(Node noeud)
{
    auto allNodes = GetAllNodes();
    for (auto it = allNodes.begin(); it != allNodes.end(); ++it)
    {
        float ErrorXPos = it->second->x() + ClickErrorTollerence;
        float ErrorXNeg = it->second->x() - ClickErrorTollerence;
        float ErrorYPos = it->second->y() + ClickErrorTollerence;
        float ErrorYNeg = it->second->y() - ClickErrorTollerence;

        if ((noeud.x() > ErrorXNeg && noeud.x() < ErrorXPos) &&
            (noeud.y() > ErrorYNeg && noeud.y() < ErrorYPos))
            return it->second->GetId();
    }
    return 66666;   //kinda lame
}

/*Road& MyGLWidget::FindAssociatedRoad(Node noeud1, Node noeud2, Node &outNoeudDepart, Node &outNoeudArrivee, bool &isInverted)
{
    Road returnValue;
    auto Roads = GetAllRoads();
    for (unsigned int i = 0; i < Roads.size(); ++i)
    {
        Node test = Roads.at(i).getStartNode();
        Node test2 = Roads.at(i).getEndNode();


        if (!Roads[i].isInSameDirection(test, test2, noeud1, noeud2))
        {
            isInverted = true;
            Node noeudTemp = Node(noeud2.x(), noeud2.y());
            noeud2 = noeud1;
            noeud1 = noeudTemp;
        }

        auto ErrorXPos1 = noeud1.x() + ClickErrorTollerence;
        auto ErrorYPos1 = noeud1.y() + ClickErrorTollerence;

        auto ErrorXNeg1 = noeud1.x() - ClickErrorTollerence;
        auto ErrorYNeg1 = noeud1.y() - ClickErrorTollerence;

        auto ErrorXPos2 = noeud2.x() + ClickErrorTollerence;
        auto ErrorYPos2 = noeud2.y() + ClickErrorTollerence;

        auto ErrorXNeg2 = noeud2.x() - ClickErrorTollerence;
        auto ErrorYNeg2 = noeud2.y() - ClickErrorTollerence;

        outNoeudDepart = noeud1;
        outNoeudArrivee = noeud2;

        if ((test.x() > ErrorXNeg1 && test.x() < ErrorXPos1) &&
             (test.y() > ErrorYNeg1 && test.y() < ErrorYPos1) &&
             (test2.x() > ErrorXNeg2 && test2.x() < ErrorXPos2) &&
             (test2.y() > ErrorYNeg2 && test2.y() < ErrorYPos2))
        {
            returnValue = SimulationData::getInstance().getRoad(i);
            return SimulationData::getInstance().getRoad(i);
        }

        //dé-inverser les voies pour la prochaine itération
        if(isInverted)
        {
            isInverted = false;
            Node noeudTemp = Node(noeud2.x(), noeud2.y());
            noeud2 = noeud1;
            noeud1 = noeudTemp;
        }

    }
    return returnValue; //si aucune route trouvé faire de quoi de brillant this is not brillant
}*/

void MyGLWidget::DrawNode(float *worldCoords, int type)
{
    //Ajouter un noeud pour le draw
    DrawNode(worldCoords[0], worldCoords[1], type);
}

void MyGLWidget::DrawNode(float x, float y, int type)
{
    auto window = static_cast<Window*>(parent());
    window->drawNode(x,y);
    //SimulationData::getInstance().addNode(x,y, false, type);
}

void MyGLWidget::DrawNode(float x, float y, simulation_traits::node_id_type id, int type)
{
    auto window = static_cast<Window*>(parent());
    window->drawNode(x,y);
    //SimulationData::getInstance().addNode(x,y, false, id, type);
}

RoadSegment MyGLWidget::AddRoad(node_id_type a, node_id_type b, std::string name)
{
    auto window = static_cast<Window*>(parent());

    auto isOneWay = window->isOneWay();
    auto numberOfLane = window->getNumberofLane();

    RoadSegment newRoad = RoadSegment(a, b, isOneWay, numberOfLane, name);
    auto roadId = SimulationData::getInstance().addRoad(newRoad);
    SimulationData::getInstance().getNode(a).addNeighbour(b, roadId);
    SimulationData::getInstance().getNode(b).addNeighbour(a, roadId);

    auto& r0 = SimulationData::getInstance().getRoad(roadId);

    int cpt = 0;

    for(int i = 1; i <= numberOfLane; ++i)
    {
        r0.addLane(r0.getStartNode(), r0.getEndNode(), i, cpt);
        ++cpt;

        if (!isOneWay)
        {
            r0.addLane(r0.getEndNode(), r0.getStartNode(), i, cpt);
            ++cpt;
        }
    }

    SimulationData::getInstance().getNode(a).addLanes(roadId);
    SimulationData::getInstance().getNode(b).addLanes(roadId);

    return r0;
}

void MyGLWidget::onRoadListWidgetClicked(QTreeWidgetItem* item, int i)
{
    RoadSegment selectedRoad;
    auto window = static_cast<Window*>(parent());

    if (item->text(0) == window->getRootItem()->text(0))
    {
        //Just clicked on root element do nothing
        return;
    }

    //The selected item is a road because our parent is Road
    else if (item->parent()->text(0) == window->getRootItem()->text(0))
    {
        selectedRoadItem_ = item;
        isRoadSelected_ = true;
        isLaneSelected_ = false;
        selectedLaneItem_ = new QTreeWidgetItem();

        auto allRoads = GetAllRoads();
        for (auto i = 0; i < allRoads.size(); ++i)
        {
            if (allRoads[i].getRoadName() == selectedRoadItem_->text(0).toLocal8Bit().constData())
            {
                selectedRoad = allRoads[i];
                qDebug() << allRoads[i].isBlocked_;
            }
        }
        selectedRoad_ = selectedRoad;
        window->setStats(Window::Stats::Roads, selectedRoad, 0);


    }
    else //clicked on a lane
    {
        isRoadSelected_ = false;
        isLaneSelected_ = true;

        selectedLaneItem_ = item;
        selectedRoadItem_ = new QTreeWidgetItem();

        QString road = item->parent()->text(0);
        std::string parentRoad = road.toLocal8Bit().constData();
        auto allRoads = GetAllRoads();

        for (auto i = 0; i < allRoads.size(); ++i)
        {
            if (allRoads[i].getRoadName() == parentRoad)
            {
                std::vector<Lane*> allLanes = allRoads[i].getLanes();
                int laneNumber = atoi(selectedLaneItem_->text(0).toLocal8Bit().constData());
                for (auto i = 0; i < allLanes.size(); ++i)
                {
                    if (allLanes[i]->getLaneId() == laneNumber)
                    {
                        selectedLane = allLanes[i];
                    }
                }
            }
            this->selectedLane = selectedLane;
            window->setStats(Window::Stats::Lanes, selectedRoad, selectedLane);
        }
    }
}

void MyGLWidget::DrawSource(float *worldCoords, int type)
{
    DrawSource(worldCoords[0], worldCoords[1], type);
}

void MyGLWidget::DrawSource(float x, float y, int type)
{
    auto window = static_cast<Window*>(parent());
    window->drawNode(x,y);

    /*auto distribution = Node::DistributionInfo();

    distribution.isBernouilli = window->isBernouilliChecked();
    distribution.isUniform = window->isUniformChecked();
    distribution.isExponential = window->isExponentialChecked();

    distribution.bernouilliAmount = window->getBernouilliAmount();
    distribution.uniformAmount = window->getUniformAmount();
    distribution.exponentialAmount = window->getExponentialAmount();

    SimulationData::getInstance().addNode(x,y, true, distribution, type);*/
}

void MyGLWidget::DrawSource(float x, float y, node_id_type id, int type)
{

    auto window = static_cast<Window*>(parent());
    window->drawNode(x,y);
    /*auto distribution = Node::DistributionInfo();

    distribution.isBernouilli = window->isBernouilliChecked();
    distribution.isUniform = window->isUniformChecked();
    distribution.isExponential = window->isExponentialChecked();

    distribution.bernouilliAmount = window->getBernouilliAmount();
    distribution.uniformAmount = window->getUniformAmount();
    distribution.exponentialAmount = window->getExponentialAmount();

    SimulationData::getInstance().addNode(x,y, true, distribution, id, type);*/
}

void MyGLWidget::ClearWidget()
{
    clearWidget();
    updateGL();
}

void MyGLWidget::DrawNodePressed()
{
    isDrawNodePressed_ = true;
    isDrawRoadPressed_ = false;
    isDrawLanePressed_ = false;
    isDrawSourcePressed_ = false;
}

void MyGLWidget::DrawRoadPressed()
{
    isDrawRoadPressed_ = true;
    isDrawNodePressed_ = false;
    isDrawLanePressed_ = false;
    isDrawSourcePressed_ = false;
}

void MyGLWidget::DrawLanePressed()
{
    isDrawLanePressed_ = true;
    isDrawRoadPressed_ = false;
    isDrawNodePressed_ = false;
    isDrawSourcePressed_ = false;
}

void MyGLWidget::DrawSourcePressed()
{
    isDrawLanePressed_ = false;
    isDrawRoadPressed_ = false;
    isDrawNodePressed_ = false;
    isDrawSourcePressed_ = true;
}

void MyGLWidget::moveCar()
{
}


void MyGLWidget::clearWidget()
{
    SimulationData::getInstance().resetAllData();
}

void MyGLWidget::draw()
{
    QTextStream out(&file);
    //draw roads
    auto allRoads = GetAllRoads();
    out << "----------------------- DRAWING ROAD & LANES ----------------------------------" << "\n";
    for (unsigned int i = 0; i < allRoads.size(); ++i)
    {
        glLoadIdentity();
        glTranslatef(0,0,-10);
        //qglColor(Qt::red);
        if (isRoadSelected_ && allRoads[i].getRoadName() == selectedRoadItem_->text(0).toLocal8Bit().constData())
            glColor4f(0,1,0,0.5f);
        else
            glColor4f(1,0,0,0.5f);

        glBegin(GL_QUADS);
            glVertex2f((allRoads[i].getLineFormula().getControlPoint(X1)*scale)+xOffset, (allRoads[i].getLineFormula().getControlPoint(Y1)*scale)+yOffset);
            glVertex2f((allRoads[i].getLineFormula().getControlPoint(X2)*scale)+xOffset, (allRoads[i].getLineFormula().getControlPoint(Y2)*scale)+yOffset);
            glVertex2f((allRoads[i].getLineFormula().getControlPoint(X4)*scale)+xOffset, (allRoads[i].getLineFormula().getControlPoint(Y4)*scale)+yOffset);
            glVertex2f((allRoads[i].getLineFormula().getControlPoint(X3)*scale)+xOffset, (allRoads[i].getLineFormula().getControlPoint(Y3)*scale)+yOffset);
        glEnd();

        //Drawing lanes
        std::vector<Lane*> allLanes = allRoads.at(i).getLanes();
        //for (auto itt = allLanes.begin(); itt != allLanes.end(); ++i)
        for (unsigned int j = 0; j < allLanes.size(); ++j)
        {
            glLoadIdentity();
            glLineWidth(3);
            glTranslatef(0,0,-9);
            if (isLaneSelected_ && allLanes[j]->getLaneId() == atoi(selectedLaneItem_->text(0).toLocal8Bit().constData()) &&
                    selectedLaneItem_->parent()->text(0).toLocal8Bit().constData() == allRoads[j].getRoadName())
                glColor4f(0,0.75f,0, 0.75f);
            else
                glColor4f(0.75f,0,0, 0.75f);
            //qglColor(Qt::blue);
            glBegin(GL_LINES);
                glVertex2f((allLanes[j]->getLineFormula().getLaneCoordinate(X1)*scale)+xOffset, (allLanes[j]->getLineFormula().getLaneCoordinate(Y1)*scale)+yOffset);
                glVertex2f((allLanes[j]->getLineFormula().getLaneCoordinate(X2)*scale)+xOffset, (allLanes[j]->getLineFormula().getLaneCoordinate(Y2)*scale)+yOffset);
            glEnd();
            out << "Number of cars on lane : " << allLanes[j]->getNumberOfVehicle() << "\n";
        }
    }

    //draw nodes
    glPointSize(20.0f*std::min(1.0f,scale));
    auto allNodes = GetAllNodes();
    for(auto it = allNodes.begin(); it!= allNodes.end(); ++it)
    {
        glLoadIdentity();
        glTranslatef(0, 0, -9);
        if(it->second->is_source())
            qglColor(Qt::red);
        else
            glColor3f(0.9f,0.3f,0.1f);
        glBegin(GL_POINTS);
            glVertex2f((it->second->x()*scale)+xOffset,(it->second->y()*scale)+yOffset);
        glEnd();
    }

    //draw vehicules
    glPointSize(5.0f);
    int i = 1;
    auto allVehicles = GetAllVehicles();

    out << "----------------------- DRAWING VEHICULE ----------------------------------" << "\n";
    for (auto itt = allVehicles.begin(); itt!= allVehicles.end(); ++itt)
    {
        glLoadIdentity();
        glTranslatef(0,0,-8);
        if ((*itt)->isOnLastStretch())
            qglColor(Qt::yellow);
        else
            qglColor(Qt::blue);

        glBegin(GL_POINTS);
            glVertex2f(((*itt)->x_*scale)+xOffset, ((*itt)->y_*scale)+yOffset);
        glEnd();

        ++i;
    }
}

std::map<simulation_traits::node_id_type,Node*>& MyGLWidget::GetAllNodes()
{
    return SimulationData::getInstance().getNodes();
}

std::vector<RoadSegment>& MyGLWidget::GetAllRoads()
{
    return SimulationData::getInstance().getRoads();
}

std::list<Vehicle*>& MyGLWidget::GetAllVehicles()
{
    return SimulationData::getInstance().getVehicles();
}

void MyGLWidget::UpdateScale(float s)
{
    scale += s;
}

void MyGLWidget::UpdateXOffset(float x)
{
    xOffset = x;
}

void MyGLWidget::UpdateYOffset(float y)
{
    yOffset = y;
}

void MyGLWidget::UpdateOffset(int which)
{
    switch(which)
    {
    case 8:
        yOffset+=0.1;
        break;
    case 2:
        yOffset-=0.1;
        break;
    case 4:
        xOffset-=0.1;
        break;
    case 6:
        xOffset+=0.1;
        break;
    default:
        break;
    }
}

void MyGLWidget::setNodeType(int what)
{
    nodeType = what;
}
