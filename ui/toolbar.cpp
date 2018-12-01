#include "toolbar.h"
#include "paintwidget.h"
#include "common.h"

#include <iostream>
using namespace std;

ToolBar::ToolBar(QWidget *parent):QToolBar (parent)
{
    m_Line = new QAction(QIcon(":/images/line.png"), nullptr,this);
    m_Circle = new QAction(QIcon(":/images/circle.png"), nullptr, this);
    m_Oval = new QAction(QIcon(":/images/oval.png"), nullptr, this);
    m_Curve = new QAction(QIcon(":/images/curve.png"), nullptr, this);
    m_Polygon = new QAction(QIcon(":/images/polygon.png"), nullptr, this);
    this->addAction(m_Line);
    this->addAction(m_Circle);
    this->addAction(m_Oval);
    this->addAction(m_Curve);
    this->addAction(m_Polygon);
    connect(m_Line, SIGNAL(triggered()), this, SLOT(onLineClicked()));
    connect(m_Circle, SIGNAL(triggered()), this, SLOT(onCircleClicked()));
    connect(m_Oval, SIGNAL(triggered()), this, SLOT(onOvalClicked()));
    connect(m_Curve, SIGNAL(triggered()), this, SLOT(onCurveClicked()));
    connect(m_Polygon, SIGNAL(triggered()), this, SLOT(onPolygonClicked()));
}

void ToolBar::onLineClicked()
{
    mode = Mode::MODE_DRAW_LINE;
    m_Line->setChecked(TRUE);
}

void ToolBar::onCircleClicked()
{
    mode = Mode::MODE_DRAW_CIRCLE;
    m_Circle->setChecked(true);
}

void ToolBar::onOvalClicked()
{
    mode = Mode::MODE_DRAW_OVAL;
    m_Oval->setChecked(true);
}

void ToolBar::onCurveClicked()
{
    mode = Mode::MODE_DRAW_CURVE;
    drawers_ref->at(mode)->reset();
}

void ToolBar::onPolygonClicked()
{

}
