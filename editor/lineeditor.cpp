#include "lineeditor.h"

LineEditor::LineEditor()
{
    box = nullptr;
    line = nullptr;
    pcur = nullptr;
    editMode = EditMode::NONE;
}

void LineEditor::setEdit(IShape *l, BoundingBox *b)
{
    line = static_cast<Line *>(l);
    box = b;
}

void LineEditor::mousePressEvent(QMouseEvent *e)
{
    auto p0 = Point(e->x(), e->y());
    pcur = line->boolEndPoint(p0);
    if(pcur == nullptr)
    {
        editMode = EditMode::MOVE;
        pcur = new Point(e->x(), e->y());
    }
    else
        editMode = EditMode::EDIT_POINT;
}

void LineEditor::mouseMoveEvent(QMouseEvent *e)
{
    if(editMode == EditMode::EDIT_POINT)
    {
        pcur->reset(e->x(), e->y());
    }
    else if(editMode == EditMode::MOVE)
    {
        auto dx = e->x() - pcur->getX();
        auto dy = e->y() - pcur->getY();
        line->translate(dx, dy);
        delete pcur;
        pcur = new Point(e->x(), e->y());
    }
    line->update();
    line->bound(*box);
}

void LineEditor::mouseReleaseEvent(QMouseEvent * e)
{
    editMode = EditMode::NONE;
}
