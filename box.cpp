#include "box.h"
#include "point.h"
#include "line.h"

BoundingBox::BoundingBox()
{

}

BoundingBox::BoundingBox(int l, int r, int t, int b)
{
    left = l;
    right = r;
    top = t;
    bottom = b;
}

void BoundingBox::setLeft(int l)
{
    this->left = l;
}

void BoundingBox::setRight(int r)
{
    this->right = r;
}

void BoundingBox::setBottom(int b)
{
    this->bottom = b;
}

void BoundingBox::setTop(int t)
{
    this->top = t;
}

void BoundingBox::draw()
{
    bool mask[] = {false, false, true, true};
    Point ps[] = {Point(left, top), Point(right, top), Point(right, bottom), Point(left, bottom), Point(left, top)};
    for(int i = 0; i < 4; i++)
    {
        auto v = Line(ps[i], ps[i+1]).getPoints();
        int cur = 0;
        for(auto p: v)
        {
            if(!mask[cur++])
                p.draw();
            if(cur >= 4)
                cur = 0;
        }
    }
}
