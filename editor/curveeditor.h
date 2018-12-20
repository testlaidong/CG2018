#ifndef CURVEEDITOR_H
#define CURVEEDITOR_H

#include "editor.h"
#include "shapes/curve.h"

class CurveEditor: public Editor
{
    BoundingBox *box;
    Curve *curve;
    enum class EditMode
    {
        NONE,
        MOVE,
        EDIT_CONTROL_POINT
    }editMode;
    Point *pcur;

public:
    CurveEditor();
    void setEdit(IShape *shape, BoundingBox *box) override;
    void mousePressEvent(QMouseEvent *)override;
    void mouseMoveEvent(QMouseEvent *)override;
    void mouseReleaseEvent(QMouseEvent * )override;
};

#endif // CURVEEDITOR_H
