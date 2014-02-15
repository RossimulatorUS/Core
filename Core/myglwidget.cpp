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
    Noeud node = Noeud(worldCoords[0], worldCoords[1]);
    Noeud associatedNode = FindAssociatedNode(node);

    //if (ClickPressedNode != NULL)
    if (associatedNode.x_ != 10.0f)
        allRoads_.push_back(Route(ClickPressedNode, associatedNode));
}

void MyGLWidget::DrawRoadMousePressed(float *worldCoords)
{
    Noeud node = Noeud(worldCoords[0], worldCoords[1]);
    Noeud associatedNode = FindAssociatedNode(node);

    /*if (associatedNode == NULL)
        ClickPressedNode = NULL;
    else*/
        ClickPressedNode = associatedNode;
}

Noeud MyGLWidget::FindAssociatedNode(Noeud noeud)
{
    for (unsigned int i = 0; i < allNodes_.size(); ++i)
    {
        float ErrorXPos = allNodes_[i].x_ + ClickErrorTollerence;
        float ErrorXNeg = allNodes_[i].x_ - ClickErrorTollerence;
        float ErrorYPos = allNodes_[i].y_ + ClickErrorTollerence;
        float ErrorYNeg = allNodes_[i].y_ - ClickErrorTollerence;

        if ((noeud.x_ > ErrorXNeg && noeud.x_ < ErrorXPos) &&
            (noeud.y_ > ErrorYNeg && noeud.y_ < ErrorYPos))
            return allNodes_[i];
    }
    //invalid node laid a revoir
    //return NULL;
    return Noeud(10.0f,10.0f);
}

void MyGLWidget::DrawNode(float *worldCoords)
{
    //Ajouter un noeud pour le draw
    Noeud noeud = Noeud(worldCoords[0], worldCoords[1]);
    allNodes_.push_back(noeud);
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

    Noeud noeudA = Noeud(0,1.6);
    Noeud noeudB = Noeud(0,-1.6);

    allNodes_.push_back(noeudA);
    allNodes_.push_back(noeudB);

    allRoads_.push_back(Route(noeudA, noeudB));

    updateGL();
}

//2 routes 2 directions
void MyGLWidget::CreateSimulation2()
{
    clearWidget();

    Noeud noeudA = Noeud(0.1,1.6);
    Noeud noeudB = Noeud(0.1,-1.6);

    Noeud noeudC = Noeud(-0.1,1.6);
    Noeud noeudD = Noeud(-0.1,-1.6);

    allNodes_.push_back(noeudA);
    allNodes_.push_back(noeudB);
    allNodes_.push_back(noeudC);
    allNodes_.push_back(noeudD);

    allRoads_.push_back(Route(noeudA, noeudB));
    allRoads_.push_back(Route(noeudC, noeudD));

    updateGL();
}

//4 routes 2 directions
void MyGLWidget::CreateSimulation3()
{
    clearWidget();

    Noeud noeudA = Noeud(0.4,1.6);
    Noeud noeudB = Noeud(0.4,-1.6);

    Noeud noeudC = Noeud(0.2,1.6);
    Noeud noeudD = Noeud(0.2,-1.6);

    Noeud noeudE = Noeud(-0.2,1.6);
    Noeud noeudF = Noeud(-0.2,-1.6);

    Noeud noeudG = Noeud(-0.4,1.6);
    Noeud noeudH = Noeud(-0.4,-1.6);

    allNodes_.push_back(noeudA);
    allNodes_.push_back(noeudB);
    allNodes_.push_back(noeudC);
    allNodes_.push_back(noeudD);
    allNodes_.push_back(noeudE);
    allNodes_.push_back(noeudF);
    allNodes_.push_back(noeudG);
    allNodes_.push_back(noeudH);

    allRoads_.push_back(Route(noeudA, noeudB));
    allRoads_.push_back(Route(noeudC, noeudD));
    allRoads_.push_back(Route(noeudE, noeudF));
    allRoads_.push_back(Route(noeudG, noeudH));

    updateGL();
}

//intersection 1 voie
void MyGLWidget::CreateSimulation4()
{
    clearWidget();

    Noeud noeudA = Noeud(0,1.6);
    Noeud noeudB = Noeud(0,-1.6);

    Noeud noeudC = Noeud(1.6,0);
    Noeud noeudD = Noeud(-1.6,0);

    allNodes_.push_back(noeudA);
    allNodes_.push_back(noeudB);
    allNodes_.push_back(noeudC);
    allNodes_.push_back(noeudD);

    allRoads_.push_back(Route(noeudA, noeudB));
    allRoads_.push_back(Route(noeudC, noeudD));

    updateGL();

}

//intersection 2 voie
void MyGLWidget::CreateSimulation5()
{
    clearWidget();

    Noeud noeudA = Noeud(0.1,1.6);
    Noeud noeudB = Noeud(0.1,-1.6);

    Noeud noeudC = Noeud(-0.1,1.6);
    Noeud noeudD = Noeud(-0.1,-1.6);

    Noeud noeudE = Noeud(1.6,0.1);
    Noeud noeudF = Noeud(-1.6,0.1);

    Noeud noeudG = Noeud(1.6,-0.1);
    Noeud noeudH = Noeud(-1.6, -0.1);

    allNodes_.push_back(noeudA);
    allNodes_.push_back(noeudB);
    allNodes_.push_back(noeudC);
    allNodes_.push_back(noeudD);
    allNodes_.push_back(noeudE);
    allNodes_.push_back(noeudF);
    allNodes_.push_back(noeudG);
    allNodes_.push_back(noeudH);

    allRoads_.push_back(Route(noeudA, noeudB));
    allRoads_.push_back(Route(noeudC, noeudD));
    allRoads_.push_back(Route(noeudE, noeudF));
    allRoads_.push_back(Route(noeudG, noeudH));

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
    // Creer le Cortex
    std::cout << "Creation du cortex" << std::endl;
    Cortex cortex(allNodes_);

    // Transformer bouton start en bouton end


    // Tout se fait dans le cortex
    /*
    Noeud noeudA = Noeud(0,1.6);
    Noeud noeudB = Noeud(0,-1.6);

    vehicule = new Vehicule(noeudA, noeudB);

    allVehicules_.push_back(*vehicule);

    VehiculeThread thread;
    thread.vehicule = vehicule;
    thread.start();
    */

    updateGL();
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
    for(unsigned int i = 0; i < allNodes_.size(); ++i)
    {
        glLoadIdentity();
        glTranslatef(0, 0, -10);
        qglColor(Qt::green);
        glColor3f(1,0,0);
        glBegin(GL_POINTS);
            glVertex2f(allNodes_[i].x_,allNodes_[i].y_);
        glEnd();
    }

    for (unsigned int i = 0; i < allRoads_.size(); ++i)
    {
        glLoadIdentity();
        glTranslatef(0,0,-10);
        qglColor(Qt::green);
        glColor3f(1,0,0);
        glBegin(GL_LINES);
            glVertex2f(allRoads_[i].PointDepart_.x_, allRoads_[i].PointDepart_.y_);
            glVertex2f(allRoads_[i].PointArrive_.x_, allRoads_[i].PointArrive_.y_);
        glEnd();
    }

    for (unsigned int i = 0; i < allVehicules_.size(); ++i)
    {
        glLoadIdentity();
        glTranslatef(0,0,-10);
        qglColor(Qt::green);
        glColor3f(0,1,0);
        glBegin(GL_POINTS);
            glVertex2f(allVehicules_[i].x_, allVehicules_[i].y_);
        glEnd();
    }
}
