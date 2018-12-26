#ifndef GL3DWIDGET_H
#define GL3DWIDGET_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include <vector>
using namespace std;

struct Point3d
{
    float x, y, z;
    Point3d(){}
    Point3d(float _x, float _y, float _z):x(_x), y(_y), z(_z){}
};

class GL3Dwidget: public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    GL3Dwidget(QWidget *parent = nullptr, string path = nullptr);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
private:
    string path;
    vector<Point3d>vertices;
    vector<vector<int>>faces;
    int m_rotateRectangle = 0;
};

#endif // GL3DWIDGET_H
