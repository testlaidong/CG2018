#include "paintwidget.h"
#include "shapes/point.h"
#include "drawer/drawer.h"
#include "drawer/linegenerator.h"
#include "drawer/circlegenerator.h"
#include "drawer/ovalgenerator.h"
#include "drawer/curvegenerator.h"
#include "drawer/rectanglegenerator.h"
#include "drawer/polygongenerator.h"

#include <iostream>
using namespace std;

PaintWidget::PaintWidget(QWidget *parent): QOpenGLWidget(parent)
{
    drawers.insert(pair<Mode, FigureGenerator*>(Mode::MODE_DRAW_LINE,new LineGenerator(&shapes)));
    drawers.insert(pair<Mode, FigureGenerator*>(Mode::MODE_DRAW_CIRCLE, new CircleGenerator(&shapes)));
    drawers.insert(pair<Mode, FigureGenerator*>(Mode::MODE_DRAW_OVAL, new OvalGenerator(&shapes)));
    drawers.insert(pair<Mode, FigureGenerator*>(Mode::MODE_DRAW_CURVE, new CurveGenerator(&shapes)));
    drawers.insert(pair<Mode, FigureGenerator*>(Mode::MODE_DRAW_RECTANGLE, new RectangleGenerator(&shapes)));
    drawers.insert(pair<Mode, FigureGenerator*>(Mode::MODE_DRAW_POLYGON, new PolygonGenerator(&shapes)));
    drawers_ref = &drawers;
    setMouseTracking(true);
}

void PaintWidget::PaintWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1.0, 1.0, 1.0, 0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

void PaintWidget::paintGL()
{
        glClearColor(1.0, 1.0, 1.0, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBegin(GL_POINTS);

        for(auto shape: shapes)
            shape->draw();

        glEnd();
}

void PaintWidget::resizeGL(int width, int height)
{
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, 1, -1);
    glMatrixMode(GL_MODELVIEW);
}

void PaintWidget::mousePressEvent(QMouseEvent *event)
 {
    if(mode != Mode::MODE_NONE)
        drawers[mode]->mousePressEvent(event);
    this->update();
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(mode != Mode::MODE_NONE)
        drawers[mode]->mouseMoveEvent(event);
    this->update();
}

void PaintWidget::mouseReleaseEvent(QMouseEvent * event)
{
    if(mode != Mode::MODE_NONE)
        drawers[mode]->mouseReleaseEvent(event);
    this->update();
}
