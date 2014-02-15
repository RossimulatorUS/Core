#ifndef POINT_H
#define POINT_H

#include <QGLWidget>

class Noeud
{
    bool est_source_;

public:
    Noeud(){} // Necessaire pour une raison obscure

    Noeud(bool est_source);
    Noeud(GLfloat x, GLfloat y);

    GLfloat x_;
    GLfloat y_;

    bool est_source();
    bool est_du();
};

#endif // POINT_H
