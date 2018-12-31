#include "line.h"

#include <cmath>
#include <iostream>
using namespace std;

Line::Line(Point p0)
{
    this->p0 = p0;
    this->p1 = p0;
    _type = Mode::MODE_DRAW_LINE;
}

Line::Line(Point p0, Point p1, bool dash, Color color)
{
    this->p0 = p0;
    this->p1 = p1;
    this->dash = dash;
    this->color = color;
    calcPoints();
    _type = Mode::MODE_DRAW_LINE;
}

void Line::setEnd(int x, int y)
{
    this->p1.reset(x, y);
    calcPoints();
}

void Line::calcPoints()
{
    points.clear();
    int x0 = p0.getX();
    int y0 = p0.getY();
    int x1 = p1.getX();
    int y1 = p1.getY();

    int dx, dy;
    int stepx = 1 , stepy = 1;

    dx = x1 - x0;
    dy = y1 - y0;

    if (dy<0) {dy=-dy; stepy=-1;}
    if (dx<0) {dx=-dx; stepx=-1;}
    dy <<= 1;
    dx <<= 1;

    points.push_back(Point(x0, y0));

    if (dx > dy) {
        int p = dy - (dx >> 1);
        while (x0 != x1) {
            x0 += stepx;
            if (p >= 0) {
                y0 += stepy;
                p -= dx;
            }
            p += dy;
            points.push_back(Point(x0, y0));
        }

    } else {
        int p = dx - (dy >> 1);
        while (y0 != y1) {
            if (p >= 0) {
                x0 += stepx;
                p -= dy;
            }
            y0 += stepy;
            p += dx;
            points.push_back(Point(x0, y0));
        }
    }
    for(size_t i = 0; i < points.size(); i++)
        points[i].setRGB(color.r, color.g, color.b);
}

void Line::bound(BoundingBox &box)
{
    box.setLeft(min(p0.getX(), p1.getX()));
    box.setRight(max(p0.getX(), p1.getX()));
    box.setTop(min(p0.getY(), p1.getY()));
    box.setBottom(max(p0.getY(), p1.getY()));
}

void Line::draw()
{
    if(!dash)
        for(auto p: points)
            p.draw();
    else
    {
        int cur = 0;
        bool mask[] = {false, false, true, true};
        for(auto p: points)
        {
            if(!mask[cur++])
                p.draw();
            if(cur >= 4)
                cur = 0;
        }
    }
}

void Line::drawControlPoints()
{
    p0.drawCircle();
    p1.drawCircle();
    drawCenter();
}

bool Line::spectialPoint(Point p)
{
    return p == p0 or p == p1;
}

Point *Line::boolEndPoint(Point p)
{
    if(p == p0)
        return &p0;
    else if(p == p1)
        return &p1;
    return nullptr;
}

void Line::update()
{
    calcPoints();
}

void Line::translate(int dx, int dy)
{
    p0.translate(dx, dy);
    p1.translate(dx, dy);
}

void Line::scale(double s)
{
    auto center = Point((p0.getX() + p1.getX())/2, (p0.getY()+p1.getY())/2);
    p0.scale(center, s);
    p1.scale(center, s);
}

void Line::rotate(double angle)
{
    auto center = getCenter();
    p0.rotate(center, angle);
    p1.rotate(center, angle);
}

Point Line::getCenter()
{
    return Point((p0.getX() + p1.getX())/2, (p0.getY()+p1.getY())/2);
}

void Line::clip(int xmin, int ymin, int xmax, int ymax)
{
    auto dx = p1.getX() - p0.getX();
    auto dy = p1.getY() - p0.getY();
    int p[] = {-dx, dx, -dy, dy};
    int q[] = {p0.getX() - xmin, xmax - p0.getX(), p0.getY() - ymin, ymax - p0.getY()};
    double u1 = 0;
    double u2 = 1;
    for(size_t i = 0; i < 4; i++)
    {
        if(p[i] == 0)
        {
            if(q[i] < 0)
                return;
        }
        else
        {
            double r = (static_cast<double>(q[i])) / p[i];
            if(p[i] < 0)
                u1 = max(u1, r);
            else
                u2 = min(u2, r);
        }
    }
    if(u1 > u2)
        return;
    auto x0 = static_cast<int>(p0.getX() + u1 * dx);
    auto y0 = static_cast<int>(p0.getY() + u1 * dy);
    auto x1 = static_cast<int>(p0.getX() + u2 * dx);
    auto y1 = static_cast<int>(p0.getY() + u2 * dy);
    p0.reset(x0, y0);
    p1.reset(x1, y1);
    update();
}

Point Line::intersectX(int x)
{
    double k = static_cast<double>(p1.getY()-p0.getY())/(p1.getX()-p0.getX());
    return Point(x, int(k*(x-p0.getX()) + p0.getY() + 0.5));
}

Point Line::intersectY(int y)
{
    double m = static_cast<double>(p1.getX()-p0.getX())/(p1.getY()-p0.getY());
    return Point(int(m*(y-p0.getY()) + p0.getX() + 0.5), y);
}
