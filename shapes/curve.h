#ifndef CURVE_H
#define CURVE_H

#include "shapes/shape.h"
#include "shapes/point.h"

class Curve: public IShape
{
    vector<Point>control_points;
public:
    Curve(Point p0);
    void generate();
    void addControlPoint(Point p);
    void draw()override;
    size_t nrControlPoints();
};

#endif // CURVE_H
