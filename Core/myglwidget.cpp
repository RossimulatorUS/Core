#include <QtWidgets>
#include <QtOpenGL>
#include <iostream>

#include "myglwidget.h"
#include "noeud.h" // Utile?
#include "route.h" // Utile?
#include "vehicule.h" // Utile?
#include "cortex.h"
#include "vehiculethread.h" // Utile?
#include "glutility.h"
#include "window.h"
#include "ui_window.h"
#include "simulationdata.h"

MyGLWidget::MyGLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    glDisable(GL_DEPTH_TEST);
    setMouseTracking(true);
    isDrawNodePressed_ = true;
    isDrawRoadPressed_ = false;
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

    if (isDrawNodePressed_)
        DrawNode(worldCoords);
    else if (isDrawRoadPressed_)
        DrawRoadMousePressed(worldCoords);
    else
    {
        //other things later (perturbation stats)
        //int i = 0;
    }

    //Refresh le widget OpenGL
    updateGL();
}

void MyGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (isDrawRoadPressed_)
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

        DrawRoadMouseReleased(worldCoords);
        updateGL();
    }
}

void MyGLWidget::DrawRoadMouseReleased(float *worldCoords)
{
    Noeud node = Noeud(worldCoords[0], worldCoords[1]);
    node_id_type associatedNode = FindAssociatedNode(node);

    if (ClickPressedNode != associatedNode && ClickPressedNode != 66666)
    {
        AddRoad(ClickPressedNode, associatedNode);
    }
}

void MyGLWidget::DrawRoadMousePressed(float *worldCoords)
{
    Noeud node = Noeud(worldCoords[0], worldCoords[1], true);
    node_id_type associatedNode = FindAssociatedNode(node);

    ClickPressedNode = associatedNode;
}

MyGLWidget::node_id_type MyGLWidget::FindAssociatedNode(Noeud noeud)
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

void MyGLWidget::DrawNode(float *worldCoords)
{
    //Ajouter un noeud pour le draw
    DrawNode(worldCoords[0], worldCoords[1]);
}

void MyGLWidget::DrawNode(float x, float y)
{
    //allNodes_.emplace_back(x,y, allNodes_.size());//le vecteur crée lui-même le noeud en le plaçant
    SimulationData::GetInstance().AddNode(x,y);
}

void MyGLWidget::AddRoad(node_id_type a, node_id_type b)
{
    //TODO si une route existe déjà, créer une voie

    //allRoads_.push_back(Route(a, b));
    auto roadId = SimulationData::GetInstance().AddRoute(Route(a, b));
    SimulationData::GetInstance().GetNoeud(a).AddNeighbour(b, roadId);
    SimulationData::GetInstance().GetNoeud(b).AddNeighbour(a, roadId);

}

/*void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }

    lastPos = event->pos();
}*/

void MyGLWidget::ClearWidget()
{
    clearWidget();
    updateGL();
}

//1 route 1 direction
void MyGLWidget::CreateSimulation1()
{
    clearWidget();

    DrawNode(0.0f,1.6f);
    DrawNode(0.0f,-1.6f);
    AddRoad(0, 1);

    updateGL();
}

//2 routes 2 directions
void MyGLWidget::CreateSimulation2()
{
    clearWidget();

    DrawNode(0.1f,1.6f);
    DrawNode(0.1f,-1.6f);
    DrawNode(-0.1f,1.6f);
    DrawNode(-0.1f,-1.6f);
    AddRoad(0, 1);
    AddRoad(2, 3);

    updateGL();
}

//4 routes 2 directions
void MyGLWidget::CreateSimulation3()
{
    clearWidget();

    DrawNode(0.4f,1.6f);
    DrawNode(0.4f,-1.6f);
    DrawNode(0.2f,1.6f);
    DrawNode(0.2f,-1.6f);
    DrawNode(-0.2f,1.6f);
    DrawNode(-0.2f,-1.6f);
    DrawNode(-0.4f,1.6f);
    DrawNode(-0.4f,-1.6f);
    AddRoad(0, 1);
    AddRoad(2, 3);
    AddRoad(4, 5);
    AddRoad(6, 7);

    updateGL();
}

//intersection 1 voie
void MyGLWidget::CreateSimulation4()
{
    clearWidget();

    DrawNode(0.0f,1.6f);
    DrawNode(1.6f,0.0f);
    DrawNode(-1.6f,0.0f);
    DrawNode(0.0f,-1.6f);

    DrawNode(0.0f,0.0f);
    AddRoad(0, 4);
    AddRoad(1, 4);
    AddRoad(2, 4);
    AddRoad(3, 4);

    updateGL();

}

//intersection 2 voie
void MyGLWidget::CreateSimulation5()
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
}

void MyGLWidget::DrawNodePressed()
{
    isDrawNodePressed_ = true;
    isDrawRoadPressed_ = false;
}

void MyGLWidget::DrawRoadPressed()
{
    isDrawRoadPressed_ = true;
    isDrawNodePressed_ = false;
}

void MyGLWidget::StartSimulation() // Fonction appelee lors du clic sur le bouton
{
    bool dvEnCours = true;

    auto& allNodes = GetAllNodes(); //ben oui, auto&, c'est pas un typo
    for(auto itt = allNodes.begin() ; itt != allNodes.end() ; ++itt)
    {
        itt->StartDV();
    }
    while(dvEnCours)
    {
        dvEnCours = false;
        for(auto itt = allNodes.begin() ; itt != allNodes.end() ; ++itt)
        {
            dvEnCours |= itt->ProcessDVMessages();
        }
    }

    for(auto itt = allNodes.begin() ; itt != allNodes.end() ; ++itt)
    {
        itt->PrintDVResults();
    }

    // Creer le Cortex
    Cortex cortex(allNodes, SimulationData::GetInstance().GetVehiculesPointer());

    //auto-rafraichissement de OpenGL
    const int FPS = 30; // Devrait pouvoir etre modifier depuis le Cortex
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
    SimulationData::GetInstance().ResetAllData();
}

void MyGLWidget::draw()
{
    glPointSize(5.0f);
    auto allNodes = GetAllNodes();
    for(unsigned int i = 0; i < allNodes.size(); ++i)
    {
        glLoadIdentity();
        glTranslatef(0, 0, -10);
        qglColor(Qt::green);
        glColor3f(1,0,0);
        glBegin(GL_POINTS);
            glVertex2f(allNodes[i].x(),allNodes[i].y());
        glEnd();
    }

    auto allRoads = GetAllRoads();
    for (unsigned int i = 0; i < allRoads.size(); ++i)
    {
        glLoadIdentity();
        glTranslatef(0,0,-10);
        qglColor(Qt::green);
        glColor3f(1,0,0);
        glBegin(GL_LINES);
            glVertex2f(allRoads[i].GetNoeudDepart().x(), allRoads[i].GetNoeudDepart().y());
            glVertex2f(allRoads[i].GetNoeudArrivee().x(), allRoads[i].GetNoeudArrivee().y());
        glEnd();
    }

    auto allVehicules = GetAllVehicules();
    for (auto itt = allVehicules.begin(); itt!= allVehicules.end(); ++itt)
    {
        glLoadIdentity();
        glTranslatef(0,0,-10);
        qglColor(Qt::green);
        glColor3f(0,1,0);
        glBegin(GL_POINTS);
            glVertex2f((*itt)->x_, (*itt)->y_);
        glEnd();

    }
}

std::vector<Noeud>& MyGLWidget::GetAllNodes()
{
    return SimulationData::GetInstance().GetNoeuds();
}

std::vector<Route> MyGLWidget::GetAllRoads()
{
    return SimulationData::GetInstance().GetRoutes();
}

std::list<Vehicule *> MyGLWidget::GetAllVehicules()
{
    return SimulationData::GetInstance().GetVehicules();
}
