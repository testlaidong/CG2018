#include "circle.h"

Circle::Circle(Point center, int radius)
{
    this->center = center;
    this->radius = radius;
}

void Circle::setRadius(int radius)
{
    this->radius = radius;
}

void Circle::plot(int dx, int dy)
{
    int d1[] = {1, -1, 1, -1, 1, -1, 1, -1};
    int d2[] = {1, 1, -1, -1, 1, 1, -1, -1};
    int i = 0;
    for(i = 0; i < 4; i++)
    {
        auto p = Point(center.getX() + d1[i] * dx, center.getY() + d2[i] * dy);
        p.draw();
    }
    for(; i < 8; i++)
    {
        auto p = Point(center.getX() + d1[i] * dy, center.getY() + d2[i] * dx);
        p.draw();
    }
}

void Circle::draw()
{
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

Point Circle::getCenter()
{
    return this->center;
}
