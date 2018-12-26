#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <QOpenGLWidget>
#include <map>
#include <vector>
#include "QOpenGLFunctions"
#include "common/common.h"
#include "drawer/drawer.h"
#include "common/box.h"
#include "editor/editor.h"

using namespace std;

class PaintWidget: public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    PaintWidget(QWidget *parent = nullptr);
    void resetSelector();
    void saveTo(string filename);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent * event);

private:
    vector<IShape *>shapes;
    BoundingBox box;
    map<Mode, FigureGenerator *>drawers;
    map<Mode, Editor *>editors;
};

#endif // PAINTWIDGET_H
