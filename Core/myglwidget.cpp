#include <QtWidgets>
#include <QtOpenGL>

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
        float ErrorXPos = allNodes[i]->x() + ClickErrorTollerence;
        float ErrorXNeg = allNodes[i]->x() - ClickErrorTollerence;
        float ErrorYPos = allNodes[i]->y() + ClickErrorTollerence;
        float ErrorYNeg = allNodes[i]->y() - ClickErrorTollerence;

        if ((noeud.x() > ErrorXNeg && noeud.x() < ErrorXPos) &&
            (noeud.y() > ErrorYNeg && noeud.y() < ErrorYPos))
            return allNodes[i]->GetId();
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

void MyGLWidget::DrawNode(float *worldCoords)
{
    //Ajouter un noeud pour le draw
    DrawNode(worldCoords[0], worldCoords[1]);
}

void MyGLWidget::DrawNode(float x, float y)
{
    SimulationData::getInstance().addNode(x,y, false);
}

void MyGLWidget::DrawNode(float x, float y, simulation_traits::node_id_type id)
{
    SimulationData::getInstance().addNode(x,y, false, id);
}

void MyGLWidget::AddRoad(node_id_type a, node_id_type b)
{
    auto window = static_cast<Window*>(parent());

    auto isOneWay = window->isOneWay();
    auto numberOfLane = window->getNumberofLane();

    //allRoads_.push_back(Route(a, b));
    RoadSegment newRoad = RoadSegment(a, b, isOneWay, numberOfLane);
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
    distribution.isExponential = window->isExponentialChecked();

    distribution.bernouilliAmount = window->getBernouilliAmount();
    distribution.uniformAmount = window->getUniformAmount();
    distribution.exponentialAmount = window->getExponentialAmount();

    SimulationData::getInstance().addNode(x,y, true, distribution);
}

void MyGLWidget::DrawSource(float x, float y, node_id_type id)
{
    auto window = static_cast<Window*>(parent());

    auto distribution = Node::DistributionInfo();

    distribution.isBernouilli = window->isBernouilliChecked();
    distribution.isUniform = window->isUniformChecked();
    distribution.isExponential = window->isExponentialChecked();

    distribution.bernouilliAmount = window->getBernouilliAmount();
    distribution.uniformAmount = window->getUniformAmount();
    distribution.exponentialAmount = window->getExponentialAmount();

    SimulationData::getInstance().addNode(x,y, true, distribution, id);
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
                glVertex2f((allLanes[i]->getLineFormula().getLaneCoordinate(X1)*scale)+xOffset, (allLanes[i]->getLineFormula().getLaneCoordinate(Y1)*scale)+yOffset);
                glVertex2f((allLanes[i]->getLineFormula().getLaneCoordinate(X2)*scale)+xOffset, (allLanes[i]->getLineFormula().getLaneCoordinate(Y2)*scale)+yOffset);
            glEnd();
            out << "Number of cars on lane : " << allLanes[i]->getNumberOfVehicle() << "\n";
        }
    }

    //draw nodes
    glPointSize(20.0f*std::min(1.0f,scale));
    auto allNodes = GetAllNodes();
    for(unsigned int i = 0; i < allNodes.size(); ++i)
    {
        glLoadIdentity();
        glTranslatef(0, 0, -9);
        if(allNodes[i]->is_source())
            qglColor(Qt::red);
        else
            glColor3f(0.9f,0.3f,0.1f);
        glBegin(GL_POINTS);
            glVertex2f((allNodes[i]->x()*scale)+xOffset,(allNodes[i]->y()*scale)+yOffset);
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
        //if((*itt)->getPositionInLane() < 5)
            qglColor(Qt::blue);
        //else
        //    qglColor(Qt::green);

        /*if ((*itt)->isCarBehind())
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
            glVertex2f(((*itt)->x_*scale)+xOffset, ((*itt)->y_*scale)+yOffset);
        glEnd();

        /*out << "Position of vehicle #"
            << (*itt)->id()
            << " : "
            << "x = " << (*itt)->x_
            << " y = " << (*itt)->y_
            << " car position : " << (*itt)->getPositionInLane()
            <<"\n";*/
        ++i;
    }
}

std::vector<Node*>& MyGLWidget::GetAllNodes()
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
    scale = s;
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
