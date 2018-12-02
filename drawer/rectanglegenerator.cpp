#include "rectanglegenerator.h"

RectangleGenerator::RectangleGenerator(std::vector<IShape *>* v): shapes(v)
{
}

void RectangleGenerator::mousePressEvent(QMouseEvent *event)
{
    if(event->button() != Qt::LeftButton)
        return;
    if(rectangle == nullptr)
    {
        rectangle = new Rect(Point(event->x(), event->y()), Point(event->x(), event->y()));
        shapes->push_back(rectangle);
    }
}

void RectangleGenerator::mouseMoveEvent(QMouseEvent *event)
{
    if(rectangle)
        rectangle->setEndPoint(Point(event->x(), event->y()));
}

void RectangleGenerator::mouseReleaseEvent(QMouseEvent * )
{
    rectangle = nullptr;
}
