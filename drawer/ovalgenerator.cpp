#include "ovalgenerator.h"
#include <cmath>


OvalGenerator::OvalGenerator(std::vector<IShape *> *v): shapes(v)
{
}

void OvalGenerator::mousePressEvent(QMouseEvent *event)
{
    if(event->button() != Qt::LeftButton)
        return;
    if(oval == nullptr)
    {
        auto x = event->x();
        auto y = event->y();
        oval = new Oval(Point(x, y), Point(x, y));
        shapes->push_back(oval);
    }
}

void OvalGenerator::mouseMoveEvent(QMouseEvent *event)
{
    if(oval)
    {
        oval->setEndPoint(Point(event->x(), event->y()));
    }
}

void OvalGenerator::mouseReleaseEvent(QMouseEvent *event)
{
    oval = nullptr;
}
