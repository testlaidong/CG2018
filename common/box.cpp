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

int BoundingBox::getLeft()
{
    return left;
}

int BoundingBox::getRight()
{
    return right;
}

int BoundingBox::getTop()
{
    return top;
}

int BoundingBox::getBottom()
{
    return bottom;
}

void BoundingBox::draw()
{
    Point ps[] = {Point(left, top), Point(right, top), Point(right, bottom), Point(left, bottom), Point(left, top)};
    for(int i = 0; i < 4; i++)
        Line(ps[i], ps[i+1], true, BLUE).draw();
}

bool BoundingBox::in(int x, int y)
{
    return x >= left and x <= right and y >= top and y <= bottom;
}
