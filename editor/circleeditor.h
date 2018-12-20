#ifndef CIRCLEEDITOR_H
#define CIRCLEEDITOR_H

#include "editor.h"
#include "shapes/circle.h"

class CircleEditor: public Editor
{
    BoundingBox *box;
    Circle *circle;
    enum class EditMode
    {
        NONE,
        MOVE,       //如果没有拉动圆上的点，则应对圆进行平移
        EDIT_RADIUS //在选中模式下，如果点击了圆周上的点
    }editMode;
    Point *pcur;

public:
    CircleEditor();
    void setEdit(IShape *shape, BoundingBox *box) override;
    void mousePressEvent(QMouseEvent *)override;
    void mouseMoveEvent(QMouseEvent *)override;
    void mouseReleaseEvent(QMouseEvent * )override;
};

#endif // CIRCLEEDITOR_H
