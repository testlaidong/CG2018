#ifndef DRAWER_H
#define DRAWER_H

#include "shapes/shape.h"

#include <QMouseEvent>
#include <vector>

class FigureGenerator
{
public:
    virtual void mousePressEvent(QMouseEvent *){}
    virtual void mouseMoveEvent(QMouseEvent *){}
    virtual void mouseReleaseEvent(QMouseEvent * ){}
    virtual void reset(){}
};

#endif // DRAWER_H
