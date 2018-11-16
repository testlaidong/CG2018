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
}

void Line::setEnd(int x, int y)
{
    this->p1.reset(x, y);
}

void Line::draw()
{

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

    auto p = Point(x0, y0);
    p.draw();

    if (dx > dy) {
        int fraction = dy - (dx >> 1);
        while (x0 != x1) {
            x0 += stepx;
            if (fraction >= 0) {
                y0 += stepy;
                fraction -= dx;
            }
            fraction += dy;
            auto p = Point(x0, y0);
            p.draw();

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
            auto p = Point(x0, y0);
            p.draw();
        }
    }
}
