#include "linedrawer.h"
#include <iostream>
using namespace std;

LineDrawer::LineDrawer(vector<IShape *>* v): shapes(v)
{
}

void LineDrawer::mousePressEvent(QMouseEvent *event)
{
    if(event->button() != Qt::LeftButton)
        return;
    if(line == nullptr)
    {
        line = new Line(Point(event->x(), event->y()), Point(event->x(), event->y()));
        shapes->push_back(line);
    }
    else
    {
        line = nullptr;
    }
}

void LineDrawer::mouseMoveEvent(QMouseEvent *event)
{
    if(line)
        line->setEnd(event->x(), event->y());
}

void LineDrawer::mouseReleaseEvent(QMouseEvent * event)
{
    line = nullptr;
}
