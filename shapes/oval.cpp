#include "oval.h"
#include "line.h"
#include <math.h>
#include <algorithm>

#define ROUND(a) (static_cast<int>(a + 0.5))

Oval::Oval(Point start, Point end)
{
    this->start = start;
    this->end = end;
    calcPoints();
    _type = Mode::MODE_DRAW_OVAL;
}

void Oval::setEndPoint(Point p)
{
    this->end = p;
    calcPoints();
}

void Oval::plot(int xcenter, int ycenter, int x, int y)
{
    int d1[] = {1, -1, 1, -1};
    int d2[] = {1, 1, -1, -1};
    for(int i = 0; i < 4; i++)
        points.push_back(Point(xcenter + d1[i] * x, ycenter + d2[i] * y));
}

void Oval::calcPoints()
{
    points.clear();
    //calculate center point
    int xcenter = (start.getX() + end.getX()) >> 1;
    int ycenter = (start.getY() + end.getY()) >> 1;
    //calculate rx and ry
    int rx = abs(end.getX() - start.getX()) >> 1;
    int ry = abs(end.getY() - start.getY()) >> 1;

    int rx2 = static_cast<int>(pow(rx, 2));
    int ry2 = static_cast<int>(pow(ry, 2));
    int tworx2 = 2 * rx2;
    int twory2 = 2 * ry2;
    int p;
    int x = 0;
    int y = ry;
    int px = 0;
    int py = tworx2 * y;
    plot(xcenter, ycenter, x, y);
    p = ROUND(ry2 - (rx2 * ry) + (0.25 * rx2));
    while(px < py)
    {
        x ++;

        px += twory2;
        if(p < 0)
            p += ry2 + px;
        else{
            y--;
            py -= tworx2;
            p += ry2 + px - py;
        }
        plot(xcenter, ycenter, x , y);
    }
    p = ROUND(ry2 * (x + 0.5) * (x + 0.5) + rx2 * (y-1) * (y-1) - rx2 * ry2);
    while(y > 0)
    {
        y--;
        py -= tworx2;
        if(p > 0)
            p += rx2 - py;
        else
        {
            x++;
            px += tworx2;
            p += rx2 - py + px;
        }
        plot(xcenter, ycenter, x , y);
    }
}

void Oval::draw()
{
    for(auto p: points)
        p.draw();
    for(auto p: fillPoints)
        p.draw();
}

void Oval::drawControlPoints()
{
    auto center = getCenter();
    drawCenter();
    int rx = abs(end.getX() - start.getX()) >> 1;
    int ry = abs(end.getY() - start.getY()) >> 1;
    auto pl = Point(center.getX() - rx, center.getY());
    auto pr = Point(center.getX() + rx, center.getY());
    Line(pl, pr, true, BLUE).draw();
    auto pt = Point(center.getX(), center.getY() - ry);
    auto pb = Point(center.getX(), center.getY() + ry);
    Line(pt, pb, true, BLUE).draw();
    start.drawCircle();
    end.drawCircle();
    Point(end.getX(), start.getY()).drawCircle();
    Point(start.getX(), end.getY()).drawCircle();
}

void Oval::bound(BoundingBox & box)
{
    auto minx = 10000;
    auto miny = 10000;
    auto maxx = 0;
    auto maxy = 0;
    for(auto p: points)
    {
        minx = min(minx, p.getX());
        maxx = max(maxx, p.getX());
        miny = min(miny, p.getY());
        maxy = max(maxy, p.getY());
    }
    box.setLeft(minx);
    box.setRight(maxx);
    box.setTop(miny);
    box.setBottom(maxy);
}

void Oval::update()
{
    calcPoints();
}

//TODO() 这两个函数有bug
Point& Oval::topleft()
{
    if(start <= end)
        return start;
    return end;
}

Point& Oval::bottomRight()
{
    if(start <= end)
        return end;
    return start;
}

bool Oval::isTopLeft(Point p)
{
    return p == topleft();
}

void Oval::moveTopLeft(Point p)
{
    topleft() = p;
}

bool Oval::isTopRight(Point p)
{
   return Point(bottomRight().getX(), topleft().getY()) == p;
}

void Oval::moveTopRight(Point p)
{
    topleft().translate(0, p.getY() - topleft().getY());
    bottomRight().translate(p.getX() - bottomRight().getX(), 0);
}

bool Oval::isBottomLeft(Point p)
{
    return Point(topleft().getX(), bottomRight().getY()) == p;
}

void Oval::moveBottomLeft(Point p)
{
    topleft().translate(p.getX() - topleft().getX(), 0);
    bottomRight().translate(0, p.getY() - bottomRight().getY());
}

bool Oval::isBottomRight(Point p)
{
    return p == bottomRight();
}

void Oval::moveBottomRight(Point p)
{
    bottomRight() = p;
}

void Oval::translate(int dx, int dy)
{
    start.translate(dx, dy);
    end.translate(dx, dy);
}

bool Oval::spectialPoint(Point p)
{
    return isTopLeft(p) || isTopRight(p) || isBottomLeft(p) || isBottomRight(p);
}

void Oval::scale(double s)
{
    auto center = getCenter();
    start.scale(center, s);
    end.scale(center, s);
}

void Oval::rotate(double angle)
{
    auto center = getCenter();
    start.rotate(center, angle);
    end.rotate(center, angle);
}

Point Oval::getCenter()
{
    return Point((start.getX() + end.getX()) >> 1, (start.getY() + end.getY()) >> 1);
}

void Oval::fill(Color)
{

}
