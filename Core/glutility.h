#ifndef GLUTILITY_H
#define GLUTILITY_H

//https://www.opengl.org/wiki/GluProject_and_gluUnProject_code
class GLUtility
{
public:
    static int unProject(float winx, float winy, float winz, float *modelview, float *projection, int *viewport, float *objectCoordinate);
private:
    GLUtility();
};

#endif // GLUTILITY_H
