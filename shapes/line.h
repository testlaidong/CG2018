#ifndef LINE_H
#define LINE_H

#include "shape.h"
#include "point.h"

class Line: public IShape
{
    Point p0;
    Point p1;
    bool dash;
public:
    Line(Point p0);
    Line(Point p0, Point p1, bool dash = false);
    void setEnd(int x, int y);
    void draw()override;
    void drawControlPoints()override;
    bool spectialPoint(Point p)override;
    Point *boolEndPoint(Point p);   //判断点p是否是线段端点
    void update()override;
    void bound(BoundingBox &box) override;
    void translate(int dx, int dy) override;
private:
    void calcPoints() override;
};

#endif // LINE_H
