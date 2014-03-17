#include "formule.h"
#include "qdebug.h"
#include "simulationdata.h"

Formule::Formule(){}

Formule::Formule(Noeud noeudA, Noeud noeudB)
{
    a = DeterminerPente(noeudA.x(), noeudB.x(), noeudA.y(), noeudB.y());
    b = DeterminerB(noeudA.x(), noeudA.y());
    Noeud noeudTemp = Noeud(noeudB.x(), noeudA.y());

    float distanceX = CalculerDistance(noeudA, noeudTemp);
    float distanceY = CalculerDistance(noeudB, noeudTemp);
    distanceDroite_ = CalculerDistance(noeudA, noeudB);

    variationX_ = (distanceX / distanceDroite_);
    variationY_ = (distanceY / distanceDroite_);

    //qDebug() << variationX_ << "," << variationY_;

    DeterminerPerpendiculaire(noeudA, noeudB);
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

bool Formule::IsInSameDirection(Noeud departRoute, Noeud arriveeRoute, Noeud departClick, Noeud arriveeClick)
{
    if (IsLeftToRight(departRoute, arriveeRoute) && IsLeftToRight(departClick, arriveeClick) ||
        !IsLeftToRight(departRoute, arriveeRoute) && !IsLeftToRight(departClick,arriveeClick))
        return true;
    return false;
}

bool Formule::IsTopToBottom(Noeud depart, Noeud arrivee)
{
    if (depart.y() < arrivee.y())
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

void Formule::DeterminerPerpendiculaire(Noeud noeud1, Noeud noeud2)
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
            LaneCoordinateX1_ = noeud1.x()+(5*(variationY_*0.01));
            LaneCoordinateX2_ = noeud2.x()+(5*(variationY_*0.01));

            LaneCoordinateY1_ = noeud1.y()-(5*(variationX_*0.01));
            LaneCoordinateY2_ = noeud2.y()-(5*(variationX_*0.01));
        }
        else
        {
            LaneCoordinateX1_ = noeud1.x()-(5*(variationY_*0.01));
            LaneCoordinateX2_ = noeud2.x()-(5*(variationY_*0.01));

            LaneCoordinateY1_ = noeud1.y()+(5*(variationX_*0.01));
            LaneCoordinateY2_ = noeud2.y()+(5*(variationX_*0.01));
        }
    }
    else
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
            LaneCoordinateX1_ = noeud1.x()-(5*(variationY_*0.01));
            LaneCoordinateX2_ = noeud2.x()-(5*(variationY_*0.01));

            LaneCoordinateY1_ = noeud1.y()-(5*(variationX_*0.01));
            LaneCoordinateY2_ = noeud2.y()-(5*(variationX_*0.01));
        }
        else
        {
            LaneCoordinateX1_ = noeud1.x()+(5*(variationY_*0.01));
            LaneCoordinateX2_ = noeud2.x()+(5*(variationY_*0.01));

            LaneCoordinateY1_ = noeud1.y()+(5*(variationX_*0.01));
            LaneCoordinateY2_ = noeud2.y()+(5*(variationX_*0.01));
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


