#ifndef CURVEGENERATOR_H
#define CURVEGENERATOR_H

#include "drawer.h"
#include "shapes/curve.h"

class CurveGenerator: public FigureGenerator
{
    Curve *curve = nullptr;
    std::vector<IShape*> *shapes;
public:
    CurveGenerator(std::vector<IShape *> *shapes);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent * event);
    void reset();
};

#endif // CURVEGENERATOR_H
