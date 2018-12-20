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
    void draw() override;
    void drawControlPoints()override;
    void bound(BoundingBox& box)override;
    Point* onCircle(Point p);
    void translate(int dx, int dy) override;
    void update()override;
private:
    void calcPoints() override;
    bool selected(Point p);
    void plot(int dx, int dy);
};

#endif // CIRCLE_H
