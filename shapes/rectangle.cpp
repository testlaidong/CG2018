#include "rectangle.h"
#include "line.h"

Rect::Rect(Point p0, Point p1)
{
    pstart = p0;
    pend = p1;
}

void Rect::setEndPoint(Point p)
{
    pend = p;
}

void Rect::draw()
{
    int x1 = pstart.getX();
    int x2 = pend.getX();
    int y1 = pstart.getY();
    int y2 = pend.getY();
    auto p1 = Point(x1, y2);
    auto p2 = Point(x2, y1);
    Line(pstart, p1).draw();
    Line(p1, pend).draw();
    Line(pend, p2).draw();
    Line(p2, pstart).draw();
}
