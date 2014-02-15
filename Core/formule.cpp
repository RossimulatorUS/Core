#include "formule.h"

Formule::Formule(){}

Formule::Formule(Noeud noeudA, Noeud noeudB)
{
    a = DeterminerPente(noeudA.x_, noeudB.x_, noeudA.y_, noeudB.y_);
    b = DeterminerB(noeudA.x_, noeudA.y_);
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
