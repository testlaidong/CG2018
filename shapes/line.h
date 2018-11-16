#ifndef LINE_H
#define LINE_H

#include "shape.h"
#include "point.h"

class Line: public IShape
{
    Point p0;
    Point p1;
public:
    Line(Point p0);
    Line(Point p0, Point p1);
    void setEnd(int x, int y);
    void draw() override;
};

#endif // LINE_H
