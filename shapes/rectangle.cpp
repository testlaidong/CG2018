#include "rectangle.h"
#include "line.h"

Rect::Rect(Point p0, Point p1)
{
    pstart = p0;
    pend = p1;
    calcPoints();
    _type = Mode::MODE_DRAW_RECTANGLE;
}

void Rect::setEndPoint(Point p)
{
    pend = p;
    calcPoints();
}

void Rect::calcPoints()
{
    points.clear();
    int x1 = pstart.getX();
    int x2 = pend.getX();
    int y1 = pstart.getY();
    int y2 = pend.getY();
    auto p1 = Point(x1, y2);
    auto p2 = Point(x2, y1);
    Point ps[] = {pstart, p1, pend, p2, pstart};
    for(int i = 0; i < 4; i++)
    {
        auto v = Line(ps[i], ps[i+1]).getPoints();
        points.insert(points.end(), v.begin(), v.end());
    }
}

void Rect::draw()
{
    for(auto p: points)
        p.draw();
}

void Rect::drawControlPoints()
{

}

void Rect::bound(BoundingBox & box)
{
    box.setLeft(min(pstart.getX(), pend.getX()) - 1);
    box.setRight(max(pstart.getX(), pend.getX()) + 1);
    box.setTop(min(pstart.getY(), pend.getY()) - 1);
    box.setBottom(max(pstart.getY(), pend.getY()) + 1);
}
