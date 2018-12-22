#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shapes/shape.h"
#include "shapes/point.h"

class Rect: public IShape
{
protected:
    Point start, end;
public:
    Rect(Point p0, Point p1);
    void setEndPoint(Point p);
    void draw()override;
    void drawControlPoints()override;
    Point getCenter()override;
    void bound(BoundingBox& box)override;

    Point& topleft();
    Point& bottomRight();

    bool isTopLeft(Point p);
    void moveTopLeft(Point p);

    bool isTopRight(Point p);
    void moveTopRight(Point p);

    bool isBottomLeft(Point p);
    void moveBottomLeft(Point p);

    bool isBottomRight(Point p);
    void moveBottomRight(Point p);

    void update()override;

    void translate(int dx, int dy)override;
    void scale(double s)override;
    void rotate(double angle)override;

    bool spectialPoint(Point p)override;
    void clip(int, int, int, int)override;

protected:
    void calcPoints()override;
};

#endif // RECTANGLE_H
