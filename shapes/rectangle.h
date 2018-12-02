#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shapes/shape.h"
#include "shapes/point.h"

class Rect: public IShape
{
    Point pstart, pend;
public:
    Rect(Point p0, Point p1);
    void setEndPoint(Point p);
    void draw()override;
};

#endif // RECTANGLE_H
