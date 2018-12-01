#include "curve.h"
#include "line.h"

Curve::Curve(Point p0)
{
    control_points.push_back(p0);
}

void Curve::addControlPoint(Point pi)
{
    control_points.push_back(pi);
}

void Curve::draw()
{
    for(int i = 0; i < control_points.size() - 1; i++)
    {
        Line line = Line(control_points[i], control_points[i+1]);
        line.draw();
    }
}
