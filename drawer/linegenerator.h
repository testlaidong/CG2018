#ifndef LINEDRAWER_H
#define LINEDRAWER_H

#include "drawer/drawer.h"
#include "shapes/point.h"
#include "shapes/line.h"

class LineGenerator: public FigureGenerator
{
    Line *line = nullptr;
    std::vector<IShape*> *shapes;
public:
    LineGenerator(std::vector<IShape *> *shapes);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent * event);
};

#endif // LINEDRAWER_H
