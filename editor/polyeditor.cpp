#include"polyeditor.h"

PolyEditor::PolyEditor()
{
    poly = nullptr;
    box = nullptr;
    pcur = nullptr;
}

void PolyEditor::setEdit(IShape *c, BoundingBox *b)
{
    poly = static_cast<Poly *>(c);
    box = b;
}

void PolyEditor::mousePressEvent(QMouseEvent *e)
{
    auto p0 = Point(e->x(), e->y());
    pcur = poly->boolVertex(p0);
    if(pcur == nullptr)
    {
        editMode = EditMode::MOVE;
        pcur = new Point(e->x(), e->y());
    }
    else
        editMode = EditMode::EDIT_VERTEX;
}

void PolyEditor::mouseMoveEvent(QMouseEvent *e)
{
    if(editMode == EditMode::EDIT_VERTEX)
    {
        if(poly->firstVertex(*pcur))
            poly->setLastVertex(Point(e->x(), e->y()));
        pcur->reset(e->x(), e->y());
        poly->refill();
    }
    else if(editMode == EditMode::MOVE)
    {
        auto dx = e->x() - pcur->getX();
        auto dy = e->y() - pcur->getY();
        poly->translate(dx, dy);
        delete pcur;
        pcur = new Point(e->x(), e->y());
    }
    poly->update();
    poly->bound(*box);
}

void PolyEditor::mouseReleaseEvent(QMouseEvent *)
{
    editMode = EditMode::NONE;
}
