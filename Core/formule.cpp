#include "formule.h"

Formule::Formule(){}

Formule::Formule(Noeud noeudA, Noeud noeudB)
{
    a = DeterminerPente(noeudA._x, noeudB._x, noeudA._y, noeudB._y);
    b = DeterminerB(noeudA._x, noeudA._y);
}

void Formule::DeterminerFormule()
{

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
