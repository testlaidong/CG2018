#ifndef CUTBOX_H
#define CUTBOX_H

#include "shapes/rectangle.h"
#include <QMouseEvent>

class CutBox: public Rect
{
    int xmin, xmax, ymin, ymax;
    enum class _Mode
    {
        NONE,
        DRAW_BOX,
        TOP_LEFT,
        TOP_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_RIGHT,
        MOVE
    }_mode;

public:
    CutBox(Point p0, Point p1);
    void setEndPoint(Point p);
    void draw()override;
    void drawControlPoints()override;
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent * );
    int left();
    int right();
    int top();
    int bottom();
    bool in(Point p);
private:
    void setBoundary();
    Point *selectedPoint;
};

#endif // CUTBOX_H
