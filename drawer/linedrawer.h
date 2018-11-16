#ifndef LINEDRAWER_H
#define LINEDRAWER_H

#include "drawer/drawer.h"
#include "shapes/point.h"
#include "shapes/line.h"

#include <vector>
using namespace std;

class LineDrawer: public IDrawer
{
    Line *line = nullptr;
    vector<IShape*> *shapes;
public:
    LineDrawer(vector<IShape *> *shapes);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent * event);
};

#endif // LINEDRAWER_H
