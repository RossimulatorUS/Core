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

/*QSize MyGLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize MyGLWidget::sizeHint() const
{
    return QSize(400, 400);
}*/

/*static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}*/

/*void MyGLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}*/

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
    Noeud node = Noeud(worldCoords[0], worldCoords[1], true);
    Noeud* associatedNode = FindAssociatedNode(node);

    if (associatedNode && ClickPressedNode && ClickPressedNode != associatedNode)
    {
        AddRoad(ClickPressedNode, associatedNode);
    }
}

void MyGLWidget::DrawRoadMousePressed(float *worldCoords)
{
    Noeud node = Noeud(worldCoords[0], worldCoords[1], true);
    Noeud* associatedNode = FindAssociatedNode(node);

    //attention, ça pourrait être NULL
    ClickPressedNode = associatedNode;
}

Noeud* MyGLWidget::FindAssociatedNode(Noeud noeud)
{
    for (unsigned int i = 0; i < allNodes_.size(); ++i)
    {
        float ErrorXPos = allNodes_[i].x() + ClickErrorTollerence;
        float ErrorXNeg = allNodes_[i].x() - ClickErrorTollerence;
        float ErrorYPos = allNodes_[i].y() + ClickErrorTollerence;
        float ErrorYNeg = allNodes_[i].y() - ClickErrorTollerence;

        if ((noeud.x() > ErrorXNeg && noeud.x() < ErrorXPos) &&
            (noeud.y() > ErrorYNeg && noeud.y() < ErrorYPos))
            return &allNodes_[i];
    }
    return NULL;
}

void MyGLWidget::DrawNode(float *worldCoords)
{
    //Ajouter un noeud pour le draw
    DrawNode(worldCoords[0], worldCoords[1]);
}

void MyGLWidget::DrawNode(float x, float y)
{
    //Ajouter un noeud pour le draw
    //Noeud noeud = Noeud(x, y);
    //allNodes_.push_back(noeud);
    allNodes_.emplace_back(x,y);//le vecteur crée lui-même le noeud en le plaçant
}

void MyGLWidget::AddRoad(Noeud *a, Noeud *b)
{
    //TODO si une route existe déjà, créer une voie

    allRoads_.push_back(Route(a, b));
    a->AddNeighbour(b, &allRoads_[allRoads_.size()-1]);
    b->AddNeighbour(a, &allRoads_[allRoads_.size()-1]);
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
    AddRoad(&allNodes_[0], &allNodes_[1]);

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
    AddRoad(&allNodes_[0], &allNodes_[1]);//A-B
    AddRoad(&allNodes_[2], &allNodes_[3]);//C-D

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
    AddRoad(&allNodes_[0], &allNodes_[1]);//A-B
    AddRoad(&allNodes_[2], &allNodes_[3]);//C-D
    AddRoad(&allNodes_[4], &allNodes_[5]);//E-F
    AddRoad(&allNodes_[6], &allNodes_[7]);//G-H

    updateGL();
}

//intersection 1 voie
void MyGLWidget::CreateSimulation4()
{
    clearWidget();

    DrawNode(0.0f,1.6f);
    DrawNode(0.0f,-1.6f);
    DrawNode(1.6f,0.0f);
    DrawNode(-1.6f,0.0f);
    DrawNode(0.0f,0.0f);
    AddRoad(&allNodes_[0], &allNodes_[4]);//A-E
    AddRoad(&allNodes_[1], &allNodes_[4]);//B-E
    AddRoad(&allNodes_[2], &allNodes_[4]);//C-E
    AddRoad(&allNodes_[3], &allNodes_[4]);//D-E

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

    AddRoad(&allNodes_[0], &allNodes_[8]);
    AddRoad(&allNodes_[1], &allNodes_[9]);

    AddRoad(&allNodes_[2], &allNodes_[9]);
    AddRoad(&allNodes_[3], &allNodes_[10]);

    AddRoad(&allNodes_[4], &allNodes_[10]);
    AddRoad(&allNodes_[5], &allNodes_[11]);

    AddRoad(&allNodes_[6], &allNodes_[11]);
    AddRoad(&allNodes_[7], &allNodes_[8]);

    //intersections
    AddRoad(&allNodes_[8], &allNodes_[9]);
    AddRoad(&allNodes_[9], &allNodes_[10]);
    AddRoad(&allNodes_[10], &allNodes_[11]);
    AddRoad(&allNodes_[11], &allNodes_[8]);

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
    for(auto itt = allNodes_.begin() ; itt != allNodes_.end() ; ++itt)
    {
        itt->StartDV();
    }
    while(dvEnCours)
    {
        dvEnCours = false;
        for(auto itt = allNodes_.begin() ; itt != allNodes_.end() ; ++itt)
        {
            dvEnCours |= itt->ProcessDVMessages();
        }
    }

    for(auto itt = allNodes_.begin() ; itt != allNodes_.end() ; ++itt)
    {
        itt->PrintDVResults();
    }

    // Creer le Cortex
    Cortex cortex(allNodes_, &allVehicules_);

    //auto-rafraichissement de OpenGL
    const int FPS = 30;
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
    allNodes_.clear();
    allRoads_.clear();
}

void MyGLWidget::draw()
{
    glPointSize(5.0f);
    for(unsigned int i = 0; i < allNodes_.size(); ++i)
    {
        glLoadIdentity();
        glTranslatef(0, 0, -10);
        qglColor(Qt::green);
        glColor3f(1,0,0);
        glBegin(GL_POINTS);
            glVertex2f(allNodes_[i].x(),allNodes_[i].y());
        glEnd();
    }

    for (unsigned int i = 0; i < allRoads_.size(); ++i)
    {
        glLoadIdentity();
        glTranslatef(0,0,-10);
        qglColor(Qt::green);
        glColor3f(1,0,0);
        glBegin(GL_LINES);
            glVertex2f(allRoads_[i].PointDepart_->x(), allRoads_[i].PointDepart_->y());
            glVertex2f(allRoads_[i].PointArrive_->x(), allRoads_[i].PointArrive_->y());
        glEnd();
    }

    for (unsigned int i = 0; i < allVehicules_.size(); ++i)
    {
        glLoadIdentity();
        glTranslatef(0,0,-10);
        qglColor(Qt::green);
        glColor3f(0,1,0);
        glBegin(GL_POINTS);
            glVertex2f(allVehicules_[i]->x_, allVehicules_[i]->y_);
        glEnd();

    }
}
