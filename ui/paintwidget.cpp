#include "paintwidget.h"
#include "common/box.h"
#include "shapes/point.h"
#include "drawer/drawer.h"
#include "drawer/linegenerator.h"
#include "drawer/circlegenerator.h"
#include "drawer/ovalgenerator.h"
#include "drawer/curvegenerator.h"
#include "drawer/rectgenerator.h"
#include "drawer/polygenerator.h"

#include <iostream>
using namespace std;

PaintWidget::PaintWidget(QWidget *parent): QOpenGLWidget(parent)
{
    drawers[Mode::MODE_DRAW_LINE] = new LineGenerator(&shapes);
    drawers[Mode::MODE_DRAW_CIRCLE] = new CircleGenerator(&shapes);
    drawers[Mode::MODE_DRAW_CURVE] = new CurveGenerator(&shapes);
    drawers[Mode::MODE_DRAW_OVAL] = new OvalGenerator(&shapes);
    drawers[Mode::MODE_DRAW_POLYGON] = new PolygonGenerator(&shapes);
    drawers[Mode::MODE_DRAW_RECTANGLE] = new RectangleGenerator(&shapes);
    drawers_ref = &drawers;
    pWidget = this;
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

void PaintWidget::resetSelector()
{
    this->selected = nullptr;
    update();
}

void PaintWidget::paintGL()
{
        glClearColor(1.0, 1.0, 1.0, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBegin(GL_POINTS);


        if(selected && mode == Mode::MODE_SELECT)
            box.draw();
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
    if(mode == Mode::MODE_SELECT)
    {
        bool selectedOne = false;
        for(auto s: shapes)
            if(s->selected(Point(event->x(), event->y())))
            {
                s->bound(box);
                selected = s;
                selectedOne = true;
                break;
            }
        if(!selectedOne)
            selected = nullptr;
    }
    else
    {
        if(mode != Mode::MODE_NONE)
            drawers[mode]->mousePressEvent(event);
    }
    update();
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(mode == Mode::MODE_SELECT)
    {

    }
    else{
        if(mode != Mode::MODE_NONE)
            drawers[mode]->mouseMoveEvent(event);
    }
    update();
}

void PaintWidget::mouseReleaseEvent(QMouseEvent * event)
{
    if(mode == Mode::MODE_SELECT)
    {

    }
    else
    {
        if(mode != Mode::MODE_NONE)
            drawers[mode]->mouseReleaseEvent(event);
    }
    update();
}
