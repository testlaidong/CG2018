#ifndef POLYGONGENERATOR_H
#define POLYGONGENERATOR_H

#include "drawer/drawer.h"
#include "shapes/polygon.h"

class PolygonGenerator: public FigureGenerator
{
    Poly *polygon = nullptr;
    std::vector<IShape*> *shapes;
public:
    PolygonGenerator(std::vector<IShape *> *shapes);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent * event);
};

#endif // POLYGONGENERATOR_H
