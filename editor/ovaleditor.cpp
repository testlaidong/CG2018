#include "ovaleditor.h"

OvalEditor::OvalEditor()
{
    box = nullptr;
    oval = nullptr;
    pold = nullptr;
    editMode = EditMode::NONE;
}

void OvalEditor::setEdit(IShape *o, BoundingBox *b)
{
    oval = static_cast<Oval *>(o);
    box = b;
    editMode = EditMode::NONE;
}

void OvalEditor::mousePressEvent(QMouseEvent *e)
{
    auto p = Point(e->x(), e->y());
    if(oval->isTopLeft(p))
        editMode = EditMode::TOP_LEFT;
    else if(oval->isTopRight(p))
        editMode = EditMode::TOP_RIGHT;
    else if(oval->isBottomLeft(p))
        editMode = EditMode::BOTTOM_LEFT;
    else if(oval->isBottomRight(p))
        editMode = EditMode::BOTTOM_RIGHT;
    else
    {
        editMode = EditMode::MOVE;
        pold = new Point(e->x(), e->y());
    }
}

void OvalEditor::mouseMoveEvent(QMouseEvent *e)
{
    auto p = Point(e->x(), e->y());
    if(editMode == EditMode::TOP_LEFT)
        oval->moveTopLeft(p);
    else if(editMode == EditMode::TOP_RIGHT)
        oval->moveTopRight(p);
    else if(editMode == EditMode::BOTTOM_LEFT)
        oval->moveBottomLeft(p);
    else if(editMode == EditMode::BOTTOM_RIGHT)
        oval->moveBottomRight(p);
    else if(editMode == EditMode::MOVE)
    {
        auto dx = e->x() - pold->getX();
        auto dy = e->y() - pold->getY();
        oval->translate(dx, dy);
        delete pold;
        pold = new Point(e->x(), e->y());
    }
    oval->update();
    oval->bound(*box);
}

void OvalEditor::mouseReleaseEvent(QMouseEvent * )
{
    editMode = EditMode::NONE;
}
