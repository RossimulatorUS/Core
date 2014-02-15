#include "noeud.h"
#include "myglwidget.h"


Noeud::Noeud(bool est_source)
    : est_source_(est_source)
{

}

Noeud::Noeud(GLfloat x, GLfloat y)
    : x_(x), y_(y)
{

}

bool Noeud::est_source()
{
    return est_source_;
}

bool Noeud::est_du()
{
    static bool tmp(true);
    tmp = !tmp;
    return tmp;
}


