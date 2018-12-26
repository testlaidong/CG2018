#include "toolbar.h"
#include "paintwidget.h"
#include "common/common.h"
#include "gl3dwidget.h"

#include <iostream>
#include <cmath>
using namespace std;

#include <QColorDialog>
#include <QFileDialog>
#include <QTextCodec>

ToolBar::ToolBar(QWidget *parent):QToolBar (parent)
{
    setFocusPolicy(Qt::StrongFocus);
    m_Line = new QAction(QIcon(":/images/line.png"), nullptr,this);
    m_Circle = new QAction(QIcon(":/images/circle.png"), nullptr, this);
    m_Oval = new QAction(QIcon(":/images/oval.png"), nullptr, this);
    m_Curve = new QAction(QIcon(":/images/curve.png"), nullptr, this);
    m_Polygon = new QAction(QIcon(":/images/polygon.png"), nullptr, this);
    m_Rectangle = new QAction(QIcon(":/images/rectangle.png"), nullptr, this);
    m_Select = new QAction(QIcon(":/images/select.png"), nullptr, this);
    m_Fill = new QAction(QIcon(":/images/fill.png"), nullptr, this);
    m_enlarge = new QAction(QIcon(":/images/add.png"), nullptr, this);
    m_narrow = new QAction(QIcon(":/images/minus.png"), nullptr, this);
    m_rotateRight = new QAction(QIcon(":/images/rotate_right.png"), nullptr, this);
    m_rotateLeft = new QAction(QIcon(":/images/rotate_left.png"), nullptr, this);
    m_Cut = new QAction(QIcon(":/images/cut.png"), nullptr, this);
    m_Delete = new QAction(QIcon(":/images/clear.png"), nullptr, this);
    m_Save = new QAction(QIcon(":/images/save.png"), nullptr, this);
    m_ColorPicker = new QAction(QIcon(":/images/colorpicker.png"), nullptr, this);
    m_3dWidget = new QAction(QIcon(":/images/3d.png"),nullptr, this);

    this->addAction(m_Line);
    this->addAction(m_Circle);
    this->addAction(m_Oval);
    this->addAction(m_Curve);
    this->addAction(m_Rectangle);
    this->addAction(m_Polygon);
    this->addSeparator();
    this->addAction(m_Select);
    this->addAction(m_narrow);
    this->addAction(m_enlarge);
    this->addAction(m_rotateRight);
    this->addAction(m_rotateLeft);
    this->addAction(m_Cut);
    this->addAction(m_Fill);
    this->addAction(m_ColorPicker);
    this->addSeparator();
    this->addAction(m_Delete);
    this->addAction(m_Save);
    this->addSeparator();
    this->addAction(m_3dWidget);


    connect(m_Line, SIGNAL(triggered()), this, SLOT(onLineClicked()));
    connect(m_Circle, SIGNAL(triggered()), this, SLOT(onCircleClicked()));
    connect(m_Oval, SIGNAL(triggered()), this, SLOT(onOvalClicked()));
    connect(m_Curve, SIGNAL(triggered()), this, SLOT(onCurveClicked()));
    connect(m_Polygon, SIGNAL(triggered()), this, SLOT(onPolygonClicked()));
    connect(m_Rectangle, SIGNAL(triggered()), this, SLOT(onRectangleClicked()));
    connect(m_Select, SIGNAL(triggered()), this, SLOT(onSelectClicked()));
    connect(m_enlarge, SIGNAL(triggered()), this, SLOT(onEnlargeClicked()));
    connect(m_narrow, SIGNAL(triggered()), this, SLOT(onNarrowClicked()));
    connect(m_rotateLeft, SIGNAL(triggered()), this, SLOT(onRotateLeftClicked()));
    connect(m_rotateRight, SIGNAL(triggered()), this, SLOT(onRotateRightClicked()));
    connect(m_Cut, SIGNAL(triggered()), this, SLOT(onCutClicked()));
    connect(m_Fill, SIGNAL(triggered()), this, SLOT(onFillClicked()));
    connect(m_Delete, SIGNAL(triggered()), this, SLOT(onDeleteClicked()));
    connect(m_ColorPicker, SIGNAL(triggered()), this,SLOT(pickColor()));
    connect(m_Save, SIGNAL(triggered()), this, SLOT(onSaveClicked()));
    connect(m_3dWidget, SIGNAL(triggered()), this, SLOT(on3dWidgetClicked()));
}

void ToolBar::on3dWidgetClicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("选择三维模型文件"), ".", tr("OFF Files(*.off)"));
    if(!path.isNull())
    {
        QTextCodec *code = QTextCodec::codecForName("GB2312");//解决中文路径问题
        string name = code->fromUnicode(path).data();
        auto widget = new GL3Dwidget(nullptr, name);
        int nWidth = GetSystemMetrics(SM_CXSCREEN);
        int nHeight = GetSystemMetrics(SM_CYSCREEN);
        widget->resize(nWidth, nHeight);
        widget->show();
    }
}

void ToolBar::onSaveClicked()
{
    QString path = QFileDialog::getSaveFileName(this, tr("保存文件"), ".", tr("BMP Files(*.bmp)"));
    if(!path.isNull())
    {
        string file =  path.toStdString().data();
        pWidget->saveTo(file);
    }
}

void ToolBar::pickColor()
{
    QColorDialog color;
    QColor c = color.getRgba();
    if(c.isValid())
    {
        fillColor.set(c.redF(), c.greenF(), c.blueF());
    }
}

void ToolBar::onFillClicked()
{
    if(selected != nullptr)
    {
        selected->fill(fillColor);
        selected->update();
    }
    pWidget->update();
}

void ToolBar::onCutClicked()
{
    if(cutBox != nullptr)
    {
        if(selected != nullptr)
        {
            selected->clip(cutBox->left(), cutBox->top(), cutBox->right(), cutBox->bottom());
            selected->bound(*boundingBox);
        }
        else
        {
            for(size_t i = 0; i < shapes_ref->size(); i++)
            {
                shapes_ref->at(i)->clip(cutBox->left(), cutBox->top(), cutBox->right(), cutBox->bottom());
            }
        }
    }
    pWidget->update();
    mode = Mode::MODE_CUT;
}

void ToolBar::onLineClicked()
{
    mode = Mode::MODE_DRAW_LINE;
    m_Line->setChecked(TRUE);
    pWidget->resetSelector();
    m_Line->setEnabled(true);
    resetCutBox();
}

void ToolBar::onCircleClicked()
{
    mode = Mode::MODE_DRAW_CIRCLE;
    m_Circle->setChecked(true);
    pWidget->resetSelector();
    resetCutBox();
}

void ToolBar::onOvalClicked()
{
    mode = Mode::MODE_DRAW_OVAL;
    m_Oval->setChecked(true);
    pWidget->resetSelector();
    resetCutBox();
}

void ToolBar::onCurveClicked()
{
    mode = Mode::MODE_DRAW_CURVE;
    m_Curve->setChecked(true);
    drawers_ref->at(mode)->reset();
    pWidget->resetSelector();
    resetCutBox();
}

void ToolBar::onRectangleClicked()
{
    mode = Mode::MODE_DRAW_RECTANGLE;
    m_Rectangle->setChecked(true);
    pWidget->resetSelector();
    resetCutBox();
}

void ToolBar::onPolygonClicked()
{
    mode = Mode::MODE_DRAW_POLYGON;
    m_Polygon->setChecked(true);
    pWidget->resetSelector();
    resetCutBox();
}

void ToolBar::onSelectClicked()
{
    m_Select->setChecked(true);
    mode = Mode::MODE_SELECT;
    resetCutBox();
}

void ToolBar::onNarrowClicked()
{
    if(selected)
    {
        selected->scale(0.9);
        selected->update();
        selected->bound(*boundingBox);
        pWidget->update();
    }
    resetCutBox();
}

void ToolBar::onEnlargeClicked()
{
    if(selected)
    {
        selected->scale(1.1);
        selected->update();
        selected->bound(*boundingBox);
        pWidget->update();
    }
    resetCutBox();
}

void ToolBar::onRotateRightClicked()
{
    if(selected)
    {
        selected->rotate(M_PI / 2);
        selected->update();
        selected->bound(*boundingBox);
        pWidget->update();
    }
    resetCutBox();
}

void ToolBar::onRotateLeftClicked()
{
    if(selected)
    {
        selected->rotate( - M_PI / 2);
        selected->update();
        selected->bound(*boundingBox);
        pWidget->update();
    }
    resetCutBox();
}

void ToolBar::onDeleteClicked()
{
    if(selected != nullptr)
    {
        auto loc = shapes_ref->cbegin();
        for(; loc != shapes_ref->cend(); loc ++)
            if(*loc == selected)
                break;
        boundingBox = nullptr;
        selected = nullptr;
        shapes_ref->erase(loc);
        pWidget->update();
    }
}
