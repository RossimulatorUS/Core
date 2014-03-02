#include "formule.h"
#include "qdebug.h"

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

    DeterminerDirection(noeudA, noeudB);
}

void Formule::DeterminerFormule()
{

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

float Formule::GetVariationX()
{
    return variationX_;
}

float Formule::GetVariationY()
{
    return variationY_;
}

float Formule::GetDirectionX()
{
    return directionX_;
}

float Formule::GetDirectionY()
{
    return directionY_;
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
    if (depart.x() > destination.x())
        variationX_ *= -1;
    if (depart.y() > destination.y())
        variationY_ *= -1;
}


