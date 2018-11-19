#ifndef OVALGENERATOR_H
#define OVALGENERATOR_H

#include "drawer/drawer.h"
#include "shapes/oval.h"

class OvalGenerator: public FigureGenerator
{
    Oval *oval = nullptr;
    std::vector<IShape*> *shapes;
public:
    OvalGenerator(std::vector<IShape *> *shapes);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent * event);
};

#endif // OVALGENERATOR_H
