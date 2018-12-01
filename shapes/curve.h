#ifndef CURVE_H
#define CURVE_H

#include "shapes/shape.h"
#include "shapes/point.h"

class Curve: public IShape
{
    vector<Point>control_points;
public:
    Curve(Point p0);
    void addControlPoint(Point p);
    void draw()override;
};

#endif // CURVE_H
