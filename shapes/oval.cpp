#include "oval.h"
#include <math.h>

#define ROUND(a) (static_cast<int>(a + 0.5))

Oval::Oval(Point start, Point end)
{
    this->start = start;
    this->end = end;
    calcPoints();
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
}

void Oval::bound(BoundingBox & box)
{
    box.setLeft(min(start.getX(), end.getX()));
    box.setRight(max(start.getX(), end.getX()));
    box.setTop(min(start.getY(), end.getY()));
    box.setBottom(max(start.getY(), end.getY()));
}
