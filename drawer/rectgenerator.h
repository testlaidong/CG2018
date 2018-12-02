#ifndef RECTANGLEGENERATOR_H
#define RECTANGLEGENERATOR_H

#include "drawer.h"
#include "shapes/rectangle.h"

class RectangleGenerator: public FigureGenerator
{
    Rect *rectangle = nullptr;
    std::vector<IShape*> *shapes;
public:
    RectangleGenerator(std::vector<IShape *> *shapes);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent * event);
};


#endif // RECTANGLEGENERATOR_H
