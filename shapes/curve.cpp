#include "curve.h"
#include "line.h"
#include <iostream>
#include <math.h>

Curve::Curve(Point p0)
{
    control_points.push_back(p0);
}

void Curve::addControlPoint(Point pi)
{
    control_points.push_back(pi);
}

size_t Curve::nrControlPoints()
{
    return control_points.size();
}


void Curve::generate()
{
    auto n = control_points.size();
    vector<int>c(n, 1);
    for(unsigned k = 0; k <= n - 1; k++)
    {
        for(auto i = n - 1; i >= k+1; i--)
            c[k] *= i;
        for(auto i = n - 1- k; i >= 2; i--)
            c[k] /= i;
    }
    for(float u = 0.0; u <= 1; u += 0.001)
    {
        int x = 0;
        int y = 0;
        for(unsigned k = 0; k < n; k++)
        {
            auto blend = c[k] * powf(u, k) * powf(1 - u, n - 1 - k);
            x += control_points[k].getX() * blend;
            y += control_points[k].getY() * blend;
        }
        Point(x, y).draw();
    }
}

void Curve::draw()
{
    generate();
    for(unsigned i = 0; i < control_points.size() - 1; i++)
    {
        Line(control_points[i], control_points[i+1]).draw();
    }
}
