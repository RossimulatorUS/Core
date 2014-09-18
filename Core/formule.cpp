#include "formule.h"
#include "qdebug.h"
#include "simulationdata.h"

Formule::Formule(){}

Formule::Formule(Noeud noeudA, Noeud noeudB, int laneNumber)
{
    a = DeterminerPente(noeudA.x(), noeudB.x(), noeudA.y(), noeudB.y());
    b = DeterminerB(noeudA.x(), noeudA.y());
    Noeud noeudTemp = Noeud(noeudB.x(), noeudA.y());

    float distanceX = CalculerDistance(noeudA, noeudTemp);
    float distanceY = CalculerDistance(noeudB, noeudTemp);
    distanceDroite_ = CalculerDistance(noeudA, noeudB);

    variationX_ = (distanceX / distanceDroite_);
    variationY_ = (distanceY / distanceDroite_);

    DeterminerPerpendiculaire(noeudA, noeudB, laneNumber);
    DeterminerDirection(noeudA, noeudB);
}

float Formule::getPente()
{
    return a;
}

GLfloat Formule::DeterminerPente(GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2)
{
    GLfloat numerateur = y2-y1;
    GLfloat denominateur = x2-x1;

    return denominateur == 0 ? 0 : numerateur/denominateur;
}

GLfloat Formule::DeterminerB(GLfloat x, GLfloat y)
{
    //y = ax+b
    //y - ax = b
    return y - a*x;
}

bool Formule::IsLeftToRight(Noeud depart, Noeud arrivee)
{
    if (depart.x() < arrivee.x())
        return true;
    return false;
}

bool Formule::IsRightToLeft(Noeud depart, Noeud arrivee)
{
    if (depart.x() > arrivee.x())
        return true;
    return false;
}

bool Formule::IsInSameDirection(Noeud departRoute, Noeud arriveeRoute, Noeud departClick, Noeud arriveeClick)
{
    if ((IsLeftToRight(departRoute, arriveeRoute) && IsLeftToRight(departClick, arriveeClick)) ||
        (IsTopToBottom(departRoute, arriveeRoute) && IsTopToBottom(departClick,arriveeClick)) ||
        (IsRightToLeft(departRoute, arriveeRoute) && IsRightToLeft(departClick,arriveeClick)) ||
        (IsBottomToTop(departRoute, arriveeRoute) && IsBottomToTop(departClick,arriveeClick)))
        return true;
    return false;
}

bool Formule::IsTopToBottom(Noeud depart, Noeud arrivee)
{
    if (depart.y() < arrivee.y())
        return true;
    return false;
}

bool Formule::IsBottomToTop(Noeud depart, Noeud arrivee)
{
    if (depart.y() > arrivee.y())
        return true;
    return false;
}

float Formule::GetVariationX()
{
    return variationX_;
}

float Formule::GetVariationY()
{
    return variationY_;
}

float Formule::CalculerPythagore(float a, float b)
{
    float c = (a*a)+(b*b);
    return sqrtf(c);
}

float Formule::CalculerDistance(Noeud noeudA, Noeud noeudB)
{
    float a = noeudB.x() - noeudA.x();
    float b = noeudB.y() - noeudA.y();

    return CalculerPythagore(a,b);
}

void Formule::DeterminerDirection(Noeud depart, Noeud destination)
{
    //droite a gauche
    if (depart.x() > destination.x())
        variationX_ *= -1;
    //haut en bas
    if (depart.y() > destination.y())
        variationY_ *= -1;
}

///pointControleX1 et autre correspond au coordonnee de la zone pour la route
/// LaneCoordinateX1 et autre correspond au coordonnee de la zone pour la voie
void Formule::DeterminerPerpendiculaire(Noeud noeud1, Noeud noeud2, int laneNumber)
{
    if (a > 0)
    {
        pointControleX1_ = noeud1.x()-(10*(variationY_*0.01));
        pointControleY1_ = noeud1.y()+(10*(variationX_*0.01));

        pointControleX2_ = noeud1.x()+(10*(variationY_*0.01));
        pointControleY2_ = noeud1.y()-(10*(variationX_*0.01));

        pointControleX3_ = noeud2.x()-(10*(variationY_*0.01));
        pointControleY3_ = noeud2.y()+(10*(variationX_*0.01));

        pointControleX4_ = noeud2.x()+(10*(variationY_*0.01));
        pointControleY4_ = noeud2.y()-(10*(variationX_*0.01));

        if (IsLeftToRight(noeud1, noeud2))
        {
            LaneCoordinateX1_ = noeud1.x()+(5*((laneNumber*variationY_)*0.01)) + (10*(variationX_*0.01));
            LaneCoordinateX2_ = noeud2.x()+(5*((laneNumber*variationY_)*0.01)) - (10*(variationX_*0.01));

            LaneCoordinateY1_ = noeud1.y()-(5*((laneNumber*variationX_)*0.01)) + (10*(variationY_*0.01));
            LaneCoordinateY2_ = noeud2.y()-(5*((laneNumber*variationX_)*0.01)) - (10*(variationY_*0.01));
        }
        else
        {
            LaneCoordinateX1_ = noeud1.x()-(5*((laneNumber*variationY_)*0.01)) - (10*(variationX_*0.01));
            LaneCoordinateX2_ = noeud2.x()-(5*((laneNumber*variationY_)*0.01)) + (10*(variationX_*0.01));

            LaneCoordinateY1_ = noeud1.y()+(5*((laneNumber*variationX_)*0.01)) - (10*(variationY_*0.01));
            LaneCoordinateY2_ = noeud2.y()+(5*((laneNumber*variationX_)*0.01)) + (10*(variationY_*0.01));
        }
    }
    else if (a < 0)
    {
        pointControleX1_ = noeud1.x()-(10*(variationY_*0.01));
        pointControleY1_ = noeud1.y()-(10*(variationX_*0.01));

        pointControleX2_ = noeud1.x()+(10*(variationY_*0.01));
        pointControleY2_ = noeud1.y()+(10*(variationX_*0.01));

        pointControleX3_ = noeud2.x()-(10*(variationY_*0.01));
        pointControleY3_ = noeud2.y()-(10*(variationX_*0.01));

        pointControleX4_ = noeud2.x()+(10*(variationY_*0.01));
        pointControleY4_ = noeud2.y()+(10*(variationX_*0.01));

        if (IsLeftToRight(noeud1, noeud2))
        {
            LaneCoordinateX1_ = noeud1.x()-(5*((laneNumber*variationY_)*0.01)) + (10*(variationX_*0.01));
            LaneCoordinateX2_ = noeud2.x()-(5*((laneNumber*variationY_)*0.01)) - (10*(variationX_*0.01));

            LaneCoordinateY1_ = noeud1.y()-(5*((laneNumber*variationX_)*0.01)) - (10*(variationY_*0.01));
            LaneCoordinateY2_ = noeud2.y()-(5*((laneNumber*variationX_)*0.01)) + (10*(variationY_*0.01));
        }
        else
        {
            LaneCoordinateX1_ = noeud1.x()+(5*((laneNumber*variationY_)*0.01)) - (10*(variationX_*0.01));
            LaneCoordinateX2_ = noeud2.x()+(5*((laneNumber*variationY_)*0.01)) + (10*(variationX_*0.01));

            LaneCoordinateY1_ = noeud1.y()+(5*((laneNumber*variationX_)*0.01)) + (10*(variationY_*0.01));
            LaneCoordinateY2_ = noeud2.y()+(5*((laneNumber*variationX_)*0.01)) - (10*(variationY_*0.01));
        }
    }
    //horizontal
    else if(IsLeftToRight(noeud1, noeud2) || IsLeftToRight(noeud2, noeud1))
    {
        pointControleX1_ = noeud1.x();
        pointControleY1_ = noeud1.y()-10*0.01;

        pointControleX2_ = noeud1.x();
        pointControleY2_ = noeud1.y()+10*0.01;

        pointControleX3_ = noeud2.x();
        pointControleY3_ = noeud2.y()-10*0.01;

        pointControleX4_ = noeud2.x();
        pointControleY4_ = noeud2.y()+10*0.01;

        if(noeud1.x() < noeud2.x())
        {
            LaneCoordinateY1_ = noeud1.y()-5*(laneNumber*0.01);
            LaneCoordinateY2_ = noeud1.y()-5*(laneNumber*0.01);

            LaneCoordinateX1_ = noeud1.x() + 0.1;
            LaneCoordinateX2_ = noeud2.x() - 0.1;
        }
        else
        {
            LaneCoordinateY1_ = noeud1.y()+5*(laneNumber*0.01);
            LaneCoordinateY2_ = noeud1.y()+5*(laneNumber*0.01);

            LaneCoordinateX1_ = noeud1.x() - 0.1;
            LaneCoordinateX2_ = noeud2.x() + 0.1;
        }
    }
    //vertical
    else
    {
        pointControleX1_ = noeud1.x()-10*0.01;
        pointControleY1_ = noeud1.y();

        pointControleX2_ = noeud1.x()+10*0.01;
        pointControleY2_ = noeud1.y();

        pointControleX3_ = noeud2.x()-10*0.01;
        pointControleY3_ = noeud2.y();

        pointControleX4_ = noeud2.x()+10*0.01;
        pointControleY4_ = noeud2.y();

        if(noeud1.y() < noeud2.y())
        {
            LaneCoordinateX1_ = noeud1.x()+5*(laneNumber*0.01);
            LaneCoordinateX2_ = noeud1.x()+5*(laneNumber*0.01);

            LaneCoordinateY1_ = noeud1.y() + 0.1;
            LaneCoordinateY2_ = noeud2.y() - 0.1;
        }
        else
        {
            LaneCoordinateX1_ = noeud1.x()-5*(laneNumber*0.01);
            LaneCoordinateX2_ = noeud1.x()-5*(laneNumber*0.01);

            LaneCoordinateY1_ = noeud1.y() - 0.1;
            LaneCoordinateY2_ = noeud2.y() + 0.1;
        }
    }
}

float Formule::GetPointControleX1()
{
    return pointControleX1_;
}

float Formule::GetPointControleY1()
{
    return pointControleY1_;
}

float Formule::GetPointControleX2()
{
    return pointControleX2_;
}

float Formule::GetPointControleY2()
{
    return pointControleY2_;
}

float Formule::GetPointControleX3()
{
    return pointControleX3_;
}

float Formule::GetPointControleY3()
{
    return pointControleY3_;
}

float Formule::GetPointControleX4()
{
    return pointControleX4_;
}

float Formule::GetPointControleY4()
{
    return pointControleY4_;
}

float Formule::GetLaneCoordinateX1()
{
    return LaneCoordinateX1_;
}

float Formule::GetLaneCoordinateX2()
{
    return LaneCoordinateX2_;
}

float Formule::GetLaneCoordinateY1()
{
    return LaneCoordinateY1_;
}

float Formule::GetLaneCoordinateY2()
{
    return LaneCoordinateY2_;
}

float Formule::GetLongueur()
{
    return distanceDroite_;
}


