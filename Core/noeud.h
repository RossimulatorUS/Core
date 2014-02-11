#ifndef POINT_H
#define POINT_H

#include <QGLWidget>

class Noeud
{
public:
    Noeud();
    Noeud(GLfloat x, GLfloat y);

    GLfloat _x;
    GLfloat _y;
};

#endif // POINT_H
