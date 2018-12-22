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
    drawCenter();
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

bool Rect::spectialPoint(Point p)
{
    return isTopLeft(p) || isTopRight(p) || isBottomLeft(p) || isBottomRight(p);
}

void Rect::scale(double s)
{
    auto center = getCenter();
    start.scale(center, s);
    end.scale(center, s);
}

void Rect::rotate(double angle)
{
    auto center = getCenter();
    start.rotate(center, angle);
    end.rotate(center, angle);
}

Point Rect::getCenter()
{
    return Point((start.getX() + end.getX()) >> 1, (start.getY() + end.getY()) >> 1);
}

void Rect::clip(int xmin, int ymin, int xmax, int ymax)
{
    //计算待裁剪矩形的四个边界
    auto xa1 = min(start.getX(), end.getX());
    auto xa2 = max(start.getX(), end.getX());
    auto ya1 = min(start.getY(), end.getY());
    auto ya2 = max(start.getY(), end.getY());

    auto xc1 = max(xa1, xmin);
    auto yc1 = max(ya1, ymin);
    auto xc2 = min(xa2, xmax);
    auto yc2 = min(ya2, ymax);

    if(not (xc1 <= xc2 and yc1 <= yc2))
        return;
    start = Point(xc1, yc1);
    end = Point(xc2, yc2);
    update();
}
