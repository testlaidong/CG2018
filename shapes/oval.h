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
    void drawControlPoints()override;    
    Point getCenter()override;
    void drawCenter()override;

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
    void rotate(double s)override;

    bool spectialPoint(Point p)override;
private:
    void plot(int xc, int yc, int x, int y);
    void calcPoints()override;
};

#endif // OVAL_H
