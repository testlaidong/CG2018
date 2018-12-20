#ifndef RECTEDITOR_H
#define RECTEDITOR_H

#include "editor.h"
#include "shapes/rectangle.h"

class RectEditor: public Editor
{
    BoundingBox *box;
    Rect *rect;
    enum class EditMode
    {
        NONE,
        MOVE,
        //编辑各个位置的点
        TOP_LEFT,
        TOP_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_RIGHT,
        TOP,
        LEFT,
        RIGHT,
        BOTTOM
    }editMode;
    Point *pold;

public:
    RectEditor();
    void setEdit(IShape *shape, BoundingBox *box) override;
    void mousePressEvent(QMouseEvent *)override;
    void mouseMoveEvent(QMouseEvent *)override;
    void mouseReleaseEvent(QMouseEvent * )override;
};

#endif // RECTEDITOR_H
