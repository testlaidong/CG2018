#ifndef SHAPE_H
#define SHAPE_H

#include "point.h"
#include "common/box.h"
#include "common/mode.h"

#include <vector>
#include <iostream>
using namespace std;

class IShape
{
protected:
    Mode _type;
    vector<Point>points;
    virtual void calcPoints(){}
public:
    virtual void bound(BoundingBox&){}
    virtual void draw(){}
    virtual void drawControlPoints(){}
    virtual bool spectialPoint(Point){return false;}
    virtual void update(){}
    virtual void translate(int , int ){}
    virtual void scale(double ){}
    virtual void rotate(double ){}
    virtual Point getCenter(){}
    void drawCenter()
    {
        auto center = getCenter();
        center.setColor(YELLOW);
        getCenter().drawCircle();
    }
    virtual bool clip(int, int, int, int){}
    Mode type(){return _type;}
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
