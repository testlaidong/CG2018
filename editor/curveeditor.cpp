#include "curveeditor.h"

CurveEditor::CurveEditor()
{
    curve = nullptr;
    box = nullptr;
    pcur = nullptr;
}

void CurveEditor::setEdit(IShape *c, BoundingBox *b)
{
    curve = static_cast<Curve *>(c);
    box = b;
}

void CurveEditor::mousePressEvent(QMouseEvent *e)
{
    auto p0 = Point(e->x(), e->y());
    pcur = curve->boolControlPoint(p0);
    if(pcur == nullptr)
    {
        editMode = EditMode::MOVE;
        pcur = new Point(e->x(), e->y());
    }
    else
        editMode = EditMode::EDIT_CONTROL_POINT;
}

void CurveEditor::mouseMoveEvent(QMouseEvent *e)
{
    if(editMode == EditMode::EDIT_CONTROL_POINT)
    {
        pcur->reset(e->x(), e->y());
    }
    else if(editMode == EditMode::MOVE)
    {
        auto dx = e->x() - pcur->getX();
        auto dy = e->y() - pcur->getY();
        curve->translate(dx, dy);
        delete pcur;
        pcur = new Point(e->x(), e->y());
    }
    curve->update();
    curve->bound(*box);
}

void CurveEditor::mouseReleaseEvent(QMouseEvent *)
{
    editMode = EditMode::NONE;
}
