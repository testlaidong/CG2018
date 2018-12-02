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
};

#endif // POLYGON_H
