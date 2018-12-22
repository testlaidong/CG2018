#ifndef POLYGON_H
#define POLYGON_H

#include "shape.h"
#include "point.h"
#include "line.h"

class Poly: public IShape
{
    vector<Point>vertexs;
public:
    Poly(Point start, Point next);
    void addVertex(Point p);
    void setLastVertex(Point p);
    bool close();
    void draw()override;
    void drawControlPoints()override;
    Point getCenter()override;
    void bound(BoundingBox& box)override;
    Point* boolVertex(Point p);
    void update()override;
    void translate(int dx, int dy)override;
    void scale(double s)override;
    void rotate(double angle)override;
    bool spectialPoint(Point p)override;
    void clip(int, int, int, int)override;
    bool firstVertex(Point v);
private:
    void calcPoints()override;
};

#endif // POLYGON_H
