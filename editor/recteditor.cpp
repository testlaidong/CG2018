#include "recteditor.h"

RectEditor::RectEditor()
{
    box = nullptr;
    rect = nullptr;
    pold = nullptr;
    editMode = EditMode::NONE;
}

void RectEditor::setEdit(IShape *r, BoundingBox *b)
{
    rect = static_cast<Rect *>(r);
    box = b;
    editMode = EditMode::NONE;
}

void RectEditor::mousePressEvent(QMouseEvent *e)
{
    auto p = Point(e->x(), e->y());
    if(rect->isTopLeft(p))
        editMode = EditMode::TOP_LEFT;
    else if(rect->isTopRight(p))
        editMode = EditMode::TOP_RIGHT;
    else if(rect->isBottomLeft(p))
        editMode = EditMode::BOTTOM_LEFT;
    else if(rect->isBottomRight(p))
        editMode = EditMode::BOTTOM_RIGHT;
    else
    {
        editMode = EditMode::MOVE;
        pold = new Point(e->x(), e->y());
    }
}

void RectEditor::mouseMoveEvent(QMouseEvent *e)
{
    auto p = Point(e->x(), e->y());
    if(editMode == EditMode::TOP_LEFT)
        rect->moveTopLeft(p);
    else if(editMode == EditMode::TOP_RIGHT)
        rect->moveTopRight(p);
    else if(editMode == EditMode::BOTTOM_LEFT)
        rect->moveBottomLeft(p);
    else if(editMode == EditMode::BOTTOM_RIGHT)
        rect->moveBottomRight(p);
    else if(editMode == EditMode::MOVE)
    {
        auto dx = e->x() - pold->getX();
        auto dy = e->y() - pold->getY();
        rect->translate(dx, dy);
        delete pold;
        pold = new Point(e->x(), e->y());
    }
    rect->update();
    rect->bound(*box);
}

void RectEditor::mouseReleaseEvent(QMouseEvent * )
{
    editMode = EditMode::NONE;
}
