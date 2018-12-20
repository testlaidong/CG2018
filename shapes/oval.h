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

    bool isTopCenter(Point p);
    void moveTopCenter(Point p);

    bool isLeftCenter(Point p);
    void moveLeftCenter(Point p);

    bool isRightCenter(Point p);
    void moveRightCenter(Point p);

    bool isBottomCenter(Point p);
    void moveBottomCenter(Point p);

    void update()override;

    void translate(int dx, int dy)override;
private:
    void plot(int xc, int yc, int x, int y);
    void calcPoints()override;
};

#endif // OVAL_H
