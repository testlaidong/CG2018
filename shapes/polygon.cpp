#include "polygon.h"

Poly::Poly(Point start, Point next)
{
    vertexs.push_back(start);
    vertexs.push_back(next);
}

void Poly::addVertex(Point p)
{
    vertexs.push_back(p);
    if(!close())
        vertexs.push_back(p);
}

void Poly::setLastVertex(Point p)
{
    vertexs[vertexs.size() - 1] = p;
}

bool Poly::close()
{
    if(vertexs[vertexs.size() - 1] == vertexs[0] and vertexs.size() >= 3)
    {
        vertexs[vertexs.size() - 1] = vertexs[0];
        return true;
    }
    return false;
}

void Poly::draw()
{
    for(size_t i = 0; i < vertexs.size() - 1; i++)
        Line(vertexs[i], vertexs[i+1]).draw();
}
