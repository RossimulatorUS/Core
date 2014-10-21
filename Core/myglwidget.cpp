#include <QtWidgets>
#include <QDebug>
#include <QtOpenGL>
#include <iostream>

#include "myglwidget.h"
#include "node.h" // Utile?
#include "road.h" // Utile?
#include "vehicle.h" // Utile?
#include "cortex.h"
#include "vehiclethread.h" // Utile?
#include "glutility.h"
#include "window.h"
#include "ui_window.h"
#include "simulationdata.h"
#include "qdebug.h"

MyGLWidget::MyGLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent), file("Vehicule data.txt")
{
    glDisable(GL_DEPTH_TEST);
    setMouseTracking(true);
    isDrawNodePressed_ = true;
    isDrawRoadPressed_ = false;
    isDrawLanePressed_ = false;
    isDrawSourcePressed_ = false;

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
}

MyGLWidget::~MyGLWidget()
{

}

void MyGLWidget::initializeGL()
{
    //couleur du background
    qglClearColor(Qt::black);

    //2d means no depth!
    glDisable(GL_DEPTH_TEST);

    //glEnable(GL_CULL_FACE);
    //glShadeModel(GL_SMOOTH);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);

    //static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
    //glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;
}

void MyGLWidget::paintGL()
{
    //glClearColor(1,1,1,1); //décommenter pour fond blanc
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
        DrawNode(worldCoords);
    else if (isDrawRoadPressed_ && window->getCurrentTabIndex() == 1)
        DrawRoadMousePressed(worldCoords);
    /*else if (isDrawLanePressed_)
        DrawLaneMousePressed(worldCoords);*/
    else if (window->isSourceChecked())
        DrawSource(worldCoords);
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

    auto isOneWay = window->isOneWay();
    auto numberOfLane = window->getNumberofLane();

    Node node = Node(worldCoords[0], worldCoords[1]);
    node_id_type associatedNode = FindAssociatedNode(node);

    if (clickPressedNode != associatedNode && clickPressedNode != 66666 && associatedNode != 66666)
    {
        AddRoad(clickPressedNode, associatedNode);
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
    for (unsigned int i = 0; i < allNodes.size(); ++i)
    {
        float ErrorXPos = allNodes[i].x() + ClickErrorTollerence;
        float ErrorXNeg = allNodes[i].x() - ClickErrorTollerence;
        float ErrorYPos = allNodes[i].y() + ClickErrorTollerence;
        float ErrorYNeg = allNodes[i].y() - ClickErrorTollerence;

        if ((noeud.x() > ErrorXNeg && noeud.x() < ErrorXPos) &&
            (noeud.y() > ErrorYNeg && noeud.y() < ErrorYPos))
            return allNodes[i].GetId();
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

void MyGLWidget::PrintNodeCoordinates(Node depart, Node arrivee)
{
    qDebug() << "depart : " << depart.x() << ", " << depart.y() << endl <<
                "arrivee: " << arrivee.x() << ", " << arrivee.y() << endl;
}

void MyGLWidget::DrawNode(float *worldCoords)
{
    //Ajouter un noeud pour le draw
    DrawNode(worldCoords[0], worldCoords[1]);
}

void MyGLWidget::DrawNode(float x, float y)
{
    //allNodes_.emplace_back(x,y, allNodes_.size());//le vecteur crée lui-même le noeud en le plaçant
    SimulationData::getInstance().addNode(x,y, false);
}

void MyGLWidget::AddRoad(node_id_type a, node_id_type b)
{
    auto window = static_cast<Window*>(parent());

    auto isOneWay = window->isOneWay();
    auto numberOfLane = window->getNumberofLane();

    //allRoads_.push_back(Route(a, b));
    Road newRoad = Road(a, b, isOneWay, numberOfLane);
    auto roadId = SimulationData::getInstance().addRoad(newRoad);
    SimulationData::getInstance().getNode(a).addNeighbour(b, roadId);
    SimulationData::getInstance().getNode(b).addNeighbour(a, roadId);

    //qDebug()<<"WTF";
    auto& r0 = SimulationData::getInstance().getRoad(roadId);

    for(int i = 1; i <= numberOfLane; ++i)
    {
        r0.addLane(r0.getStartNode(), r0.getEndNode(), i);

        if (!isOneWay)
            r0.addLane(r0.getEndNode(), r0.getStartNode(), i);
    }

    SimulationData::getInstance().getNode(a).addLanes(roadId);
    SimulationData::getInstance().getNode(b).addLanes(roadId);
}

void MyGLWidget::DrawSource(float *worldCoords)
{
    DrawSource(worldCoords[0], worldCoords[1]);
}

void MyGLWidget::DrawSource(float x, float y)
{
    auto window = static_cast<Window*>(parent());

    auto distribution = Node::DistributionInfo();

    distribution.isBernouilli = window->isBernouilliChecked();
    distribution.isUniform = window->isUniformChecked();
    distribution.bernouilliAmount = window->getBernouilliAmount();
    distribution.uniformAmount = window->getUniformAmount();

    SimulationData::getInstance().addNode(x,y, true, distribution);
}

void MyGLWidget::ClearWidget()
{
    clearWidget();
    updateGL();
}

//1 route 1 direction
void MyGLWidget::CreateSimulation1()
{
    clearWidget();

    DrawSource(0.0f,1.6f);
    DrawSource(0.0f,-1.6f);
    AddRoad(0, 1);

    updateGL();
}

//intersection 1 voie
void MyGLWidget::CreateSimulation4()
{
    clearWidget();

    DrawSource(0.0f,1.6f);
    DrawSource(1.6f,0.0f);
    DrawSource(-1.6f,0.0f);
    DrawSource(0.0f,-1.6f);

    DrawNode(0.0f,0.0f);
    AddRoad(0, 4);
    AddRoad(1, 4);
    AddRoad(2, 4);
    AddRoad(3, 4);

    updateGL();
}

//intersection 2 voie
/*void MyGLWidget::CreateSimulation5()
{
    clearWidget();

    //tout est clockwise
    //noeuds haut
    DrawNode(-0.1f,1.6f);
    DrawNode(0.1f,1.6f);
    //noeuds droite
    DrawNode(1.6f,0.1f);
    DrawNode(1.6f,-0.1f);
    //noeuds bas
    DrawNode(0.1f,-1.6f);
    DrawNode(-0.1f,-1.6f);
    //noeuds gauche
    DrawNode(-1.6f,-0.1f);
    DrawNode(-1.6f,0.1f);

    //intersections
    DrawNode(-0.1f,0.1f);
    DrawNode(0.1f,0.1f);
    DrawNode(0.1f,-0.1f);
    DrawNode(-0.1f,-0.1f);

    AddRoad(0, 8);
    AddRoad(1, 9);

    AddRoad(2, 9);
    AddRoad(3, 10);

    AddRoad(4, 10);
    AddRoad(5, 11);

    AddRoad(6, 11);
    AddRoad(7, 8);

    AddRoad(8, 9);
    AddRoad(9, 10);
    AddRoad(10, 11);
    AddRoad(11, 8);

    updateGL();
}*/

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

void MyGLWidget::StartSimulation() // Fonction appelee lors du clic sur le bouton
{
    bool dvEnCours = true;

    auto& allNodes = GetAllNodes(); //ben oui, auto&, c'est pas un typo
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

    // Creer le Cortex
    Cortex* cortex = new Cortex(allNodes, SimulationData::getInstance().getVehiclesPointer());

    //auto-rafraichissement de OpenGL
    const int FPS = 15; // Devrait pouvoir etre modifier depuis le Cortex
    const int FREQ_RAFRAICHISSMENT_MS = 1000/FPS;
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer->start(FREQ_RAFRAICHISSMENT_MS);

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
        glColor4f(1,0,0,0.5f);
        glBegin(GL_QUADS);
            glVertex2f(allRoads[i].getLineFormula().getControlPoint(X1), allRoads[i].getLineFormula().getControlPoint(Y1));
            glVertex2f(allRoads[i].getLineFormula().getControlPoint(X2), allRoads[i].getLineFormula().getControlPoint(Y2));
            glVertex2f(allRoads[i].getLineFormula().getControlPoint(X4), allRoads[i].getLineFormula().getControlPoint(Y4));
            glVertex2f(allRoads[i].getLineFormula().getControlPoint(X3), allRoads[i].getLineFormula().getControlPoint(Y3));
        glEnd();

        //Drawing lanes
        std::vector<Lane*> allLanes = allRoads.at(i).getLanes();
        //for (auto itt = allLanes.begin(); itt != allLanes.end(); ++i)
        for (unsigned int i = 0; i < allLanes.size(); ++i)
        {
            glLoadIdentity();
            glLineWidth(3);
            glTranslatef(0,0,-9);
            glColor4f(0.75f,0,0, 0.75f);
            //qglColor(Qt::blue);
            glBegin(GL_LINES);
                //glVertex2f(allLanes[i]->getStartNode().x(), allLanes[i]->getStartNode().y());
                //glVertex2f(allLanes[i]->getEndNode().x(), allLanes[i]->getEndNode().y());
                glVertex2f(allLanes[i]->getLineFormula().getLaneCoordinate(X1), allLanes[i]->getLineFormula().getLaneCoordinate(Y1));
                glVertex2f(allLanes[i]->getLineFormula().getLaneCoordinate(X2), allLanes[i]->getLineFormula().getLaneCoordinate(Y2));
            glEnd();
            out << "Number of cars on lane : " << allLanes[i]->getNumberOfVehicle() << "\n";
        }
    }

    //draw nodes
    glPointSize(25.0f);
    auto allNodes = GetAllNodes();
    for(unsigned int i = 0; i < allNodes.size(); ++i)
    {
        glLoadIdentity();
        glTranslatef(0, 0, -9);
        if(allNodes[i].is_source())
            qglColor(Qt::red);
        else
            glColor3f(0.9f,0.3f,0.1f);
        glBegin(GL_POINTS);
            glVertex2f(allNodes[i].x(),allNodes[i].y());
        glEnd();
    }

    //draw vehicules
    glPointSize(5.0f);
    int i = 1;
    auto allVehicles = GetAllVehicles();
    Vehicle* vehicleInFront;
    Vehicle* vehicleBehind;

    out << "----------------------- DRAWING VEHICULE ----------------------------------" << "\n";
    for (auto itt = allVehicles.begin(); itt!= allVehicles.end(); ++itt)
    {
        glLoadIdentity();
        glTranslatef(0,0,-8);
        if((*itt)->getPositionInLane() < 5)
            qglColor(Qt::blue);
        else
            qglColor(Qt::green);

        if ((*itt)->isCarBehind())
        {
            out << " car in back : yep ";
            vehicleBehind = (*itt)->getVehicleBehind();
            out << " vehicle behind id" << vehicleBehind->id();
        }
        else
            out << " car in back : nop ";

        if ((*itt)->isCarInFront())
        {
            out << " car in front : yep ";
            vehicleInFront = (*itt)->getVehicleInFront();
            out << " vehicle behind id" << vehicleInFront->id();
        }
        else
        {
            out << " car in front : nop ";
        }

        /*if((*itt)->isOnLastStretch())
            qglColor(Qt::yellow );
        else
            qglColor(Qt::green);*/

        glBegin(GL_POINTS);
            glVertex2f((*itt)->x_, (*itt)->y_);
        glEnd();

        out << "Position of vehicle #"
            << (*itt)->id()
            << " : "
            << "x = " << (*itt)->x_
            << " y = " << (*itt)->y_
            << " car position : " << (*itt)->getPositionInLane()
            <<"\n";
        ++i;
    }
}

std::vector<Node>& MyGLWidget::GetAllNodes()
{
    return SimulationData::getInstance().getNodes();
}

std::vector<Road>& MyGLWidget::GetAllRoads()
{
    return SimulationData::getInstance().getRoads();
}

std::list<Vehicle*>& MyGLWidget::GetAllVehicles()
{
    return SimulationData::getInstance().getVehicles();
}
