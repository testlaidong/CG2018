#ifndef OVAL_H
#define OVAL_H

#include "shapes/shape.h"
#include "shapes/point.h"

class Oval: public IShape
{
    Point start; //upper-left coner
    Point end;
public:
    Oval(Point start, Point end);
    void setEndPoint(Point p);
    void draw() override;
private:
    void plot(int xc, int yc, int x, int y);
};

#endif // OVAL_H
