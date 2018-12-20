#include "toolbar.h"
#include "paintwidget.h"
#include "common/common.h"

#include <iostream>
using namespace std;

ToolBar::ToolBar(QWidget *parent):QToolBar (parent)
{
    setFocusPolicy(Qt::StrongFocus);
    BACKGROUND_BLUE;
    m_Line = new QAction(QIcon(":/images/line.png"), nullptr,this);
    m_Circle = new QAction(QIcon(":/images/circle.png"), nullptr, this);
    m_Oval = new QAction(QIcon(":/images/oval.png"), nullptr, this);
    m_Curve = new QAction(QIcon(":/images/curve.png"), nullptr, this);
    m_Polygon = new QAction(QIcon(":/images/polygon.png"), nullptr, this);
    m_Rectangle = new QAction(QIcon(":/images/rectangle.png"), nullptr, this);
    m_Select = new QAction(QIcon(":/images/select.png"), nullptr, this);
    m_Fill = new QAction(QIcon(":/images/fill.jpg"), nullptr, this);

    this->addAction(m_Line);
    this->addAction(m_Circle);
    this->addAction(m_Oval);
    this->addAction(m_Curve);
    this->addAction(m_Rectangle);
    this->addAction(m_Polygon);
    this->addSeparator();
    this->addAction(m_Select);
    this->addAction(m_Fill);
    this->addSeparator();


    connect(m_Line, SIGNAL(triggered()), this, SLOT(onLineClicked()));
    connect(m_Circle, SIGNAL(triggered()), this, SLOT(onCircleClicked()));
    connect(m_Oval, SIGNAL(triggered()), this, SLOT(onOvalClicked()));
    connect(m_Curve, SIGNAL(triggered()), this, SLOT(onCurveClicked()));
    connect(m_Polygon, SIGNAL(triggered()), this, SLOT(onPolygonClicked()));
    connect(m_Rectangle, SIGNAL(triggered()), this, SLOT(onRectangleClicked()));
    connect(m_Select, SIGNAL(triggered()), this, SLOT(onSelectClicked()));
}

void ToolBar::onLineClicked()
{
    mode = Mode::MODE_DRAW_LINE;
    m_Line->setChecked(TRUE);
    pWidget->resetSelector();
    m_Line->setEnabled(true);
}

void ToolBar::onCircleClicked()
{
    mode = Mode::MODE_DRAW_CIRCLE;
    m_Circle->setChecked(true);
    pWidget->resetSelector();
}

void ToolBar::onOvalClicked()
{
    mode = Mode::MODE_DRAW_OVAL;
    m_Oval->setChecked(true);
    pWidget->resetSelector();
}

void ToolBar::onCurveClicked()
{
    mode = Mode::MODE_DRAW_CURVE;
    m_Curve->setChecked(true);
    drawers_ref->at(mode)->reset();
    pWidget->resetSelector();
}

void ToolBar::onRectangleClicked()
{
    mode = Mode::MODE_DRAW_RECTANGLE;
    m_Rectangle->setChecked(true);
    pWidget->resetSelector();
}

void ToolBar::onPolygonClicked()
{
    mode = Mode::MODE_DRAW_POLYGON;
    m_Polygon->setChecked(true);
    pWidget->resetSelector();
}

void ToolBar::onSelectClicked()
{
    m_Select->setChecked(true);
    mode = Mode::MODE_SELECT;
}
