#include "circlegenerator.h"
#include <cmath>

CircleGenerator::CircleGenerator(std::vector<IShape *> *v): shapes(v)
{
}

void CircleGenerator::mousePressEvent(QMouseEvent *event)
{
    if(event->button() != Qt::LeftButton)
        return;
    if(circle == nullptr)
    {
        circle = new Circle(Point(event->x(), event->y()), 1);
        shapes->push_back(circle);
    }
}

void CircleGenerator::mouseMoveEvent(QMouseEvent *event)
{
    if(circle)
    {
        auto dx = event->x() - circle->getCenter().getX();
        auto dy = event->y() - circle->getCenter().getY();
        auto radius = (int)(sqrt(pow(dx, 2) + pow(dy, 2)));
        circle->setRadius(radius);
    }
}

void CircleGenerator::mouseReleaseEvent(QMouseEvent *event)
{
    circle = nullptr;
}
