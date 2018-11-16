#include "paintwidget.h"
#include "shapes/point.h"
#include "drawer/drawer.h"
#include "drawer/linedrawer.h"

#include <iostream>
using namespace std;

PaintWidget::PaintWidget(QWidget *parent): QOpenGLWidget(parent)
{
    drawers.insert(pair<Mode, IDrawer *>(Mode::MODE_DRAW_LINE,new LineDrawer(&shapes)));
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
    {
        drawers[mode]->mousePressEvent(event);
    }
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
}
