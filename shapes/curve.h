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
    void drawControlPoints()override;
    size_t nrControlPoints();
    Point lastControlPoints();
    void bound(BoundingBox& box)override;
    Point* boolControlPoint(Point p);
    void translate(int dx, int dy)override;
    void update()override;
private:
    void calcPoints()override;
};

#endif // CURVE_H
