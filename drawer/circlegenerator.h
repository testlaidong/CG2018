#ifndef CIRCLEGENERATOR_H
#define CIRCLEGENERATOR_H

#include "drawer.h"
#include "shapes/circle.h"

class CircleGenerator: public FigureGenerator
{
    Circle *circle = nullptr;
    std::vector<IShape*> *shapes;
public:
    CircleGenerator(std::vector<IShape *> *shapes);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent * event);
};

#endif // CIRCLEGENERATOR_H
