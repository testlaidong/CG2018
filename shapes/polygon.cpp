#include "polygon.h"
#include <algorithm>

Poly::Poly(Point start, Point next)
{
    vertexs.push_back(start);
    vertexs.push_back(next);
    calcPoints();
    _type = Mode::MODE_DRAW_POLYGON;
}

void Poly::addVertex(Point p)
{
    if(!close())
        vertexs.push_back(p);
    calcPoints();
}

void Poly::setLastVertex(Point p)
{
    vertexs[vertexs.size() - 1] = p;
    calcPoints();
}

bool Poly::close()
{
    if(vertexs[vertexs.size() - 1] == vertexs[0] and vertexs.size() >= 3)
    {
        //vertexs.pop_back();
        vertexs[vertexs.size() - 1] = vertexs[0];
        return true;
    }
    return false;
}

void Poly::calcPoints()
{
    points.clear();
    for(size_t i = 0; i < vertexs.size() - 1; i++)
    {
        auto v = Line(vertexs[i], vertexs[i+1]).getPoints();
        points.insert(points.end(), v.begin(), v.end());
    }
}

void Poly::draw()
{
    for(auto p: points)
        p.draw();
    for(auto p: fillPoints)
        p.draw();
}

void Poly::drawControlPoints()
{
    for(auto p: vertexs)
        p.drawCircle();
    drawCenter();
}

void Poly::bound(BoundingBox & box)
{
    auto minx = 10000;
    auto miny = 10000;
    auto maxx = 0;
    auto maxy = 0;
    for(auto p: vertexs)
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

Point* Poly::boolVertex(Point p)
{
    for(size_t i = 0; i < vertexs.size(); i++)
        if(vertexs[i] == p)
            return &vertexs[i];
    return nullptr;
}

void Poly::update()
{
    calcPoints();
}

void Poly::translate(int dx, int dy)
{
    for(size_t i = 0; i < vertexs.size(); i++)
        vertexs[i].translate(dx, dy);
    refill();
}

bool Poly::spectialPoint(Point p)
{
    return boolVertex(p);
}

void Poly::scale(double s)
{
    auto center = getCenter();
    for(size_t i = 0; i < vertexs.size(); i++)
        vertexs[i].scale(center, s);
    refill();
}

Point Poly::getCenter()
{
    int cx = 0, cy = 0;
    for(auto p: vertexs)
    {
        cx += p.getX();
        cy += p.getY();
    }
    return Point(cx / vertexs.size(), cy / vertexs.size());
}

void Poly::rotate(double angle)
{
    auto center = getCenter();
    for(size_t i = 0; i < vertexs.size(); i++)
        vertexs[i].rotate(center, angle);
    refill();
}

bool Poly::firstVertex(Point p)
{
    return p == vertexs[0];
}

bool outside(int xmin, int ymin, int xmax, int ymax, int no, Point p)
{
    switch (no)
    {
    case 0: return p.getY() < ymin;
    case 1: return p.getX() > xmax;
    case 2: return p.getY() > ymax;
    case 3: return p.getX() < xmin;
    }
    return false;
}

Point intersect(Line line, int x, int no)
{
    if(no == 0 || no == 2)
        return line.intersectY(x);
    return line.intersectX(x);
}

void Poly::clip(int xmin, int ymin, int xmax, int ymax)
{
    int x[] = {ymin, xmax, ymax, xmin};
    vector<Point>result;
    for(int i = 0; i < 4; i++)
    {
        for(size_t j = 0; j < vertexs.size() - 1; j++)
        {
            auto start = vertexs[j];
            auto end = vertexs[j+1];
            if(outside(xmin, ymin, xmax, ymax, i, start))
            {
                if(outside(xmin, ymin, xmax, ymax, i, end))
                    continue;
                auto line = Line(start, end);
                result.push_back(intersect(line, x[i], i));
                result.push_back(end);
            }
            else
            {
                if(outside(xmin, ymin, xmax, ymax, i, end))
                {
                    auto line = Line(start, end);
                    result.push_back(intersect(line, x[i], i));
                }
                else
                    result.push_back(end);
            }
        }
        vertexs = result;
        vertexs.push_back(vertexs[0]);
        result.clear();
    }
    update();
    refill();
}

struct Edge
{
    double x;
    double dx;
    int y_upper;
    Edge(){}
    Edge(double x0, double dx0, int y_upper0):x(x0), dx(dx0), y_upper(y_upper0){}
};

void Poly::fill(Color color)
{
    fillPoints.clear();
    fColor = color;
    auto comp = [](Point a, Point b)->bool{return a.getY() < b.getY(); };
    //求扫描线的y值范围
    size_t low = static_cast<size_t>((*min_element(vertexs.begin(), vertexs.end(), comp)).getY());
    size_t high = static_cast<size_t>((*max_element(vertexs.begin(), vertexs.end(), comp)).getY());
    vector<Point>vertex_temp(vertexs.begin(), vertexs.end() - 1);

    auto n = vertex_temp.size();

    //计算有序边表
    vector<vector<Edge>> edges(high - low + 1);
    for(size_t i = 0; i < vertex_temp.size(); i++)
    {
        //edge = (begin, end)
        auto begin = vertex_temp[i];
        auto end = vertex_temp[(i+1) % n];
        if(begin.getY() == end.getY())
            continue;
        auto begin_prev = vertex_temp[(i-1+n)%n];
        auto end_next = vertex_temp[(i+2) % n];
        double x, dx = static_cast<double>(end.getX() - begin.getX()) / (end.getY() - begin.getY());
        int ymax;
        if(begin.getY() < end.getY())
        {
            x = begin.getX();
            if(end.getY() <= end_next.getY())
                ymax = end.getY() - 1;
            else
                ymax = end.getY();
            edges[static_cast<unsigned>(begin.getY()) - low].push_back(Edge(x, dx, ymax));
        }
        else
        {
            x = end.getX();
            if(begin.getY() <= begin_prev.getY())
                ymax = begin.getY() - 1;
            else
                ymax = begin.getY();
            edges[static_cast<unsigned>(end.getY()) - low].push_back(Edge(x, dx, ymax));
        }
    }

    vector<vector<Edge>> aet(high - low + 1);
    for (unsigned i = low; i <= high; i++)
    {
        for (unsigned j = low; j <= i; j++)
            for (Edge e : edges[j - low])
                if (e.y_upper >= i)
                    aet[i - low].push_back(Edge(e.x + (i - j)*e.dx, e.dx, e.y_upper));
        sort(aet[i - low].begin(), aet[i - low].end(), [](Edge a, Edge b)->bool {return a.x < b.x; });
    }

    for (size_t i = 0; i < aet.size(); i++)
        for (auto e = aet[i].begin(); e != aet[i].end() && e + 1 != aet[i].end(); e+=2)
        {
            for(auto x0 = static_cast<int>(e->x) + 1; x0 < static_cast<int>((e+1)->x); x0++)
            {
                auto p = Point(x0, i + low);
                p.setColor(color);
                fillPoints.push_back(p);
            }
        }
}
