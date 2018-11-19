#ifndef CIRCLE_H
#define CIRCLE_H

#include "shapes/shape.h"
#include "shapes/point.h"

class Circle: public IShape
{
    Point center;
    int radius;
public:
    Circle(Point center, int radius);
    void setRadius(int radius);
    Point getCenter();
    void plot(int dx, int dy);
    void draw() override;
};

#endif // CIRCLE_H
