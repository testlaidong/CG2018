#ifndef EDITOR_H
#define EDITOR_H

#include <QMouseEvent>
#include "common/box.h"
#include "shapes/shape.h"

class Editor
{
public:
    virtual void setEdit(IShape *, BoundingBox *){}
    virtual void mousePressEvent(QMouseEvent *){}
    virtual void mouseMoveEvent(QMouseEvent *){}
    virtual void mouseReleaseEvent(QMouseEvent * ){}
};

#endif // EDITOR_H
