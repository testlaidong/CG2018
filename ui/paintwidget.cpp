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
#include "editor/lineeditor.h"
#include "editor/circleeditor.h"
#include "editor/ovaleditor.h"
#include "editor/curveeditor.h"
#include "editor/recteditor.h"
#include "editor/polyeditor.h"

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
    editors[Mode::MODE_DRAW_LINE] = new LineEditor();
    editors[Mode::MODE_DRAW_CIRCLE] = new CircleEditor();
    editors[Mode::MODE_DRAW_OVAL] = new OvalEditor();
    editors[Mode::MODE_DRAW_CURVE] = new CurveEditor();
    editors[Mode::MODE_DRAW_RECTANGLE] = new RectEditor();
    editors[Mode::MODE_DRAW_POLYGON] = new PolyEditor();
    drawers_ref = &drawers;
    pWidget = this;
    selected = nullptr;
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
    selected = nullptr;
    update();
}

void PaintWidget::paintGL()
{
        glClearColor(1.0, 1.0, 1.0, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(selected != nullptr)
        {
            box.draw();
            selected->drawControlPoints();
        }
        for(auto shape: shapes)
            shape->draw();
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
        auto p = Point(event->x(), event->y());
        //如果在图形选择模式下，如果selected不为空(已经有图形处于选中状态)，且点击位置位于box内部，选中的图形不变
        if(selected != nullptr and (selected->spectialPoint(p) or box.in(event->x(), event->y())))
            editors[selected->type()]->mousePressEvent(event);
        //否则需要重新判断是否选中了其它图形
        else
        {
            bool selectedOne = false;
            selected = nullptr;
            for(auto s: shapes)
                if(s->selected(p))
                {
                    s->bound(box);
                    selected = s;
                    boundingBox = &box;
                    selectedOne = true;
                    editors[selected->type()]->setEdit(selected, &box);
                    break;
                }
        }
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
        setMouseTracking(false);
        if(selected != nullptr)
            editors[selected->type()]->mouseMoveEvent(event);
        setMouseTracking(true);
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
        if(selected != nullptr)
            editors[selected->type()]->mouseReleaseEvent(event);
    }
    else
    {
        if(mode != Mode::MODE_NONE)
            drawers[mode]->mouseReleaseEvent(event);
    }
    update();
}
