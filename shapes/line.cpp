#include "line.h"

#include <cmath>
#include <iostream>
using namespace std;

Line::Line(Point p0)
{
    this->p0 = p0;
    this->p1 = p0;
}

Line::Line(Point p0, Point p1)
{
    this->p0 = p0;
    this->p1 = p1;
    calcPoints();
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
    for(auto p: points)
        p.draw();
}
