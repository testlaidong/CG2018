#include "linegenerator.h"

LineGenerator::LineGenerator(std::vector<IShape *>* v): shapes(v)
{
}

void LineGenerator::mousePressEvent(QMouseEvent *event)
{
    if(event->button() != Qt::LeftButton)
        return;
    if(line == nullptr)
    {
        line = new Line(Point(event->x(), event->y()), Point(event->x(), event->y()));
        shapes->push_back(line);
    }
}

void LineGenerator::mouseMoveEvent(QMouseEvent *event)
{
    if(line)
        line->setEnd(event->x(), event->y());
}

void LineGenerator::mouseReleaseEvent(QMouseEvent * )
{
    line = nullptr;
}
