#ifndef SHAPE_H
#define SHAPE_H

#include "point.h"
#include "common/box.h"

#include <vector>
using namespace std;

class IShape
{
protected:
    vector<Point>points;
    virtual void calcPoints(){}
public:
    virtual void bound(BoundingBox &box){};
    virtual void draw(){}
    bool selected(Point p)
    {
        for(auto p0: points)
            if(p == p0)
                return true;
        return false;
    }
    vector<Point> getPoints()
    {
        return points;
    }
};

#endif // SHAPE_H
