#include "polygenerator.h"

PolygonGenerator::PolygonGenerator(std::vector<IShape *>* v): shapes(v)
{
}

void PolygonGenerator::mousePressEvent(QMouseEvent *event)
{
    if(event->button() != Qt::LeftButton)
        return;
    if(polygon == nullptr)
    {
        polygon = new Poly(Point(event->x(), event->y()), Point(event->x(), event->y()));
        shapes->push_back(polygon);
    }
    else
    {
        polygon->addVertex(Point(event->x(), event->y()));
        if(polygon->close())
            polygon = nullptr;
    }
}

void PolygonGenerator::mouseMoveEvent(QMouseEvent *event)
{
    if(polygon)
        polygon->setLastVertex(Point(event->x(), event->y()));
}

void PolygonGenerator::mouseReleaseEvent(QMouseEvent * event)
{
}
