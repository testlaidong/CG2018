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

Line::Line(Point p0, Point p1, bool dash)
{
    this->p0 = p0;
    this->p1 = p1;
    this->dash = dash;
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
    int stepx, stepy;

    dx = x1 - x0;
    dy = y1 - y0;

    if (dy<0) {dy=-dy; stepy=-1;} else {stepy=1;}
    if (dx<0) {dx=-dx; stepx=-1;} else {stepx=1;}
    dy <<= 1; /* dy is now 2*dy */
    dx <<= 1; /* dx is now 2*dx */

    points.push_back(Point(x0, y0));

    if (dx > dy) {
        int fraction = dy - (dx >> 1);
        while (x0 != x1) {
            x0 += stepx;
            if (fraction >= 0) {
                y0 += stepy;
                fraction -= dx;
            }
            fraction += dy;
            points.push_back(Point(x0, y0));
        }

    } else {
        int fraction = dx - (dy >> 1);
        while (y0 != y1) {
            if (fraction >= 0) {
                x0 += stepx;
                fraction -= dy;
            }
            y0 += stepy;
            fraction += dx;
            points.push_back(Point(x0, y0));

        }
    }
    if(dash)
    {
        for(size_t i = 0; i < points.size(); i++)
            points[i].setRGB(0, 0, 1);
    }
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

void Line::drawCenter()
{
    auto center = getCenter();
    center.drawCircle(255, 215, 0);
}
