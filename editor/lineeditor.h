#ifndef LINEEDITOR_H
#define LINEEDITOR_H

#include "editor.h"
#include "shapes/line.h"

class LineEditor: public Editor
{
    BoundingBox *box;
    Line *line;
    enum class EditMode
    {
        NONE,
        MOVE,
        EDIT_POINT
    }editMode;
    Point *pcur;

public:
    LineEditor();
    void setEdit(IShape *shape, BoundingBox *box) override;
    void mousePressEvent(QMouseEvent *)override;
    void mouseMoveEvent(QMouseEvent *)override;
    void mouseReleaseEvent(QMouseEvent * )override;
};

#endif // LINEEDITOR_H
