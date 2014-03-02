#include "noeud.h"
#include "myglwidget.h"


Noeud::Noeud(bool est_source)
    : est_source_(est_source), est_du_(false)
{

}

Noeud::Noeud(GLfloat x, GLfloat y)
    : x_(x), y_(y)
{

}


GLfloat Noeud::x() const
{
    return x_;
}

GLfloat Noeud::y() const
{
    return y_;
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


