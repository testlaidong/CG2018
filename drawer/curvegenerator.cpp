#include "curvegenerator.h"

CurveGenerator::CurveGenerator(std::vector<IShape *>* v): shapes(v)
{
}

void CurveGenerator::mousePressEvent(QMouseEvent *event)
{
    if(event->button() != Qt::LeftButton)
        return;
    if(curve == nullptr)
    {
        curve = new Curve(Point(event->x(), event->y()));
        shapes->push_back(curve);
    }
    else
    {
        auto p = Point(event->x(), event->y());
        if(p == curve->lastControlPoints())
            curve = nullptr;
        else
            curve->addControlPoint(Point(event->x(), event->y()));
    }
}

void CurveGenerator::mouseMoveEvent(QMouseEvent *event)
{

}

void CurveGenerator::mouseReleaseEvent(QMouseEvent * event)
{

}

void CurveGenerator::reset()
{
    this->curve = nullptr;
}
