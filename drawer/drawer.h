#ifndef DRAWER_H
#define DRAWER_H

#include "shapes/shape.h"

#include <QMouseEvent>
#include <vector>

class FigureGenerator
{
public:
    virtual void mousePressEvent(QMouseEvent *event){}
    virtual void mouseMoveEvent(QMouseEvent *event){}
    virtual void mouseReleaseEvent(QMouseEvent * event){}
};

#endif // DRAWER_H
