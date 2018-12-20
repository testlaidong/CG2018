#include "rectangle.h"
#include "line.h"

Rect::Rect(Point p0, Point p1)
{
    start = p0;
    end = p1;
    calcPoints();
    _type = Mode::MODE_DRAW_RECTANGLE;
}

void Rect::setEndPoint(Point p)
{
    end = p;
    calcPoints();
}

void Rect::calcPoints()
{
    points.clear();
    int x1 = start.getX();
    int x2 = end.getX();
    int y1 = start.getY();
    int y2 = end.getY();
    auto p1 = Point(x1, y2);
    auto p2 = Point(x2, y1);
    Point ps[] = {start, p1, end, p2, start};
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
    start.drawCircle();
    end.drawCircle();
    Point(end.getX(), start.getY()).drawCircle();
    Point(start.getX(), end.getY()).drawCircle();
}

void Rect::bound(BoundingBox & box)
{
    box.setLeft(min(start.getX(), end.getX()) - 1);
    box.setRight(max(start.getX(), end.getX()) + 1);
    box.setTop(min(start.getY(), end.getY()) - 1);
    box.setBottom(max(start.getY(), end.getY()) + 1);
}

void Rect::update()
{
    calcPoints();
}

Point& Rect::topleft()
{
    if(start <= end)
        return start;
    return end;
}

Point& Rect::bottomRight()
{
    if(start <= end)
        return end;
    return start;
}

bool Rect::isTopLeft(Point p)
{
    return p == topleft();
}

void Rect::moveTopLeft(Point p)
{
    topleft() = p;
}

bool Rect::isTopRight(Point p)
{
   return Point(bottomRight().getX(), topleft().getY()) == p;
}

void Rect::moveTopRight(Point p)
{
    topleft().translate(0, p.getY() - topleft().getY());
    bottomRight().translate(p.getX() - bottomRight().getX(), 0);
}

bool Rect::isBottomLeft(Point p)
{
    return Point(topleft().getX(), bottomRight().getY()) == p;
}

void Rect::moveBottomLeft(Point p)
{
    topleft().translate(p.getX() - topleft().getX(), 0);
    bottomRight().translate(0, p.getY() - bottomRight().getY());
}

bool Rect::isBottomRight(Point p)
{
    return p == bottomRight();
}

void Rect::moveBottomRight(Point p)
{
    bottomRight() = p;
}

void Rect::translate(int dx, int dy)
{
    start.translate(dx, dy);
    end.translate(dx, dy);
}


