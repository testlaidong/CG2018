#include "circleeditor.h"

CircleEditor::CircleEditor()
{
    box = nullptr;
    circle = nullptr;
    pcur = nullptr;
}

void CircleEditor::setEdit(IShape *shape, BoundingBox *b)
{
    circle = static_cast<Circle *>(shape);
    box = b;
    editMode = EditMode::NONE;
}


void CircleEditor::mousePressEvent(QMouseEvent *e)
{
    auto p0 = Point(e->x(), e->y());
    pcur = circle->onCircle(p0);
    if(pcur == nullptr)
    {
        editMode = EditMode::MOVE;
        pcur = new Point(e->x(), e->y());
    }
    else
        editMode = EditMode::EDIT_RADIUS;
}

void CircleEditor::mouseMoveEvent(QMouseEvent *e)
{
    if(editMode == EditMode::EDIT_RADIUS)
    {
        pcur->reset(e->x(), e->y());
        Point center = circle->getCenter();
        auto r = Point(e->x(), e->y()) - center;
        circle->setRadius(r);
    }
    else if(editMode == EditMode::MOVE)
    {
        auto dx = e->x() - pcur->getX();
        auto dy = e->y() - pcur->getY();
        circle->translate(dx, dy);
        delete pcur;
        pcur = new Point(e->x(), e->y());
    }
    circle->update();
    circle->bound(*box);
}

void CircleEditor::mouseReleaseEvent(QMouseEvent * e)
{
    editMode = EditMode::NONE;
}


