#ifndef POLYEDITOR_H
#define POLYEDITOR_H

#include "editor.h"
#include "shapes/polygon.h"

class PolyEditor: public Editor
{
    BoundingBox *box;
    Poly *poly;
    enum class EditMode
    {
        NONE,
        MOVE,
        EDIT_VERTEX
    }editMode;
    Point *pcur;

public:
    PolyEditor();
    void setEdit(IShape *shape, BoundingBox *box) override;
    void mousePressEvent(QMouseEvent *)override;
    void mouseMoveEvent(QMouseEvent *)override;
    void mouseReleaseEvent(QMouseEvent * )override;
};


#endif // POLYEDITOR_H
