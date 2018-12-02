#include "circle.h"
#include <cmath>

Circle::Circle(Point center, int radius)
{
    this->center = center;
    this->radius = radius;
    calcPoints();
}

void Circle::setRadius(int radius)
{
    this->radius = radius;
    calcPoints();
}

void Circle::plot(int dx, int dy)
{
    int d1[] = {1, -1, 1, -1, 1, -1, 1, -1};
    int d2[] = {1, 1, -1, -1, 1, 1, -1, -1};
    int i = 0;
    for(i = 0; i < 4; i++)
        points.push_back(Point(center.getX() + d1[i] * dx, center.getY() + d2[i] * dy));
    for(; i < 8; i++)
        points.push_back(Point(center.getX() + d1[i] * dy, center.getY() + d2[i] * dx));
}

void Circle::draw()
{
    for(auto p: points)
        p.draw();
}

void Circle::calcPoints()
{
    points.clear();
    auto x = 0;
    auto y = radius;
    auto p = 1 - radius;
    plot(x, y);
    while (x < y) {
        x++;
        if(p < 0)
            p += 2 * x + 1;
        else
        {
            y--;

            p += 2 * (x - y) + 1;
        }
        plot(x, y);
    }
}

bool Circle::selected(Point p)
{
    return abs(p - center - radius) <= 5;
}

void Circle::bound(BoundingBox & box)
{
    box.setLeft(center.getX() - radius);
    box.setRight(center.getX() + radius);
    box.setTop(center.getY() - radius);
    box.setBottom(center.getY() + radius);
}

Point Circle::getCenter()
{
    return this->center;
}
