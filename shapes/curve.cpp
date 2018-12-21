#include "curve.h"
#include "line.h"
#include <iostream>
#include <math.h>

Curve::Curve(Point p0)
{
    control_points.push_back(p0);
    _type = Mode::MODE_DRAW_CURVE;
}

void Curve::addControlPoint(Point pi)
{
    control_points.push_back(pi);
    calcPoints();
}

size_t Curve::nrControlPoints()
{
    return control_points.size();
}

void Curve::drawControlPoints()
{
    for(unsigned i = 0; i < control_points.size() - 1; i++)
        Line(control_points[i], control_points[i+1], true, BLUE).draw();
    for(auto p: control_points)
    {
        p.setColor(BLUE);
        p.drawCircle();
    }
    drawCenter();
}

void Curve::calcPoints()
{
    points.clear();
    auto n = control_points.size();
    vector<int>c(n, 1);
    for(unsigned k = 0; k <= n - 1; k++)
    {
        for(auto i = n - 1; i >= k+1; i--)
            c[k] *= i;
        for(auto i = n - 1- k; i >= 2; i--)
            c[k] /= i;
    }
    for(float u = 0.0; u <= 1; u += 0.004)
    {
        int x = 0;
        int y = 0;
        for(unsigned k = 0; k < n; k++)
        {
            auto coefficient = c[k] * powf(u, k) * powf(1 - u, n - 1 - k);
            x += control_points[k].getX() * coefficient;
            y += control_points[k].getY() * coefficient;
        }
        points.push_back(Point(x, y));
    }
}

Point Curve::lastControlPoints()
{
    return control_points[control_points.size() - 1];
}

void Curve::draw()
{
    for(auto p: points)
        p.draw();
}

void Curve::bound(BoundingBox & box)
{
    auto minx = 10000;
    auto miny = 10000;
    auto maxx = 0;
    auto maxy = 0;
    for(auto p: control_points)
    {
        minx = min(minx, p.getX());
        maxx = max(maxx, p.getX());
        miny = min(miny, p.getY());
        maxy = max(maxy, p.getY());
    }
    box.setLeft(minx);
    box.setRight(maxx);
    box.setTop(miny);
    box.setBottom(maxy);
}

Point* Curve::boolControlPoint(Point p)
{
    for(size_t i = 0;i < control_points.size(); i++)
        if(p == control_points[i])
            return &control_points[i];
    return nullptr;
}

void Curve::translate(int dx, int dy)
{
    for(size_t i = 0; i < control_points.size(); i++)
        control_points[i].translate(dx, dy);
}

void Curve::update()
{
    calcPoints();
}

bool Curve::spectialPoint(Point p)
{
    return boolControlPoint(p);
}

void Curve::scale(double s)
{
    auto center = getCenter();
    for(size_t i = 0; i < control_points.size(); i++)
        control_points[i].scale(center, s);
}

void Curve::rotate(double angle)
{
    auto center = getCenter();
    for(size_t i = 0; i < control_points.size(); i++)
        control_points[i].rotate(center, angle);
}

Point Curve::getCenter()
{
    int cx = 0, cy = 0;
    for(auto p: control_points)
    {
        cx += p.getX();
        cy += p.getY();
    }
    return Point(cx / control_points.size(), cy / control_points.size());
}
