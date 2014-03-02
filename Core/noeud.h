#ifndef POINT_H
#define POINT_H

#include <QGLWidget>

class Noeud
{
    bool est_source_;
    bool est_du_;

public:
    Noeud(){}

    Noeud(bool est_source);
    Noeud(GLfloat x, GLfloat y);

    GLfloat x_;
    GLfloat y_;

    bool est_source();
    bool est_du();

    GLfloat x() const;
    GLfloat y() const;
};

#endif // POINT_H
