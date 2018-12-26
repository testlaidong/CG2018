#ifndef SHAPE_H
#define SHAPE_H

#include "point.h"
#include "common/box.h"
#include "common/mode.h"

#include <vector>
#include <iostream>
using namespace std;

extern Color fillColor;

class IShape
{
protected:
    Mode _type;
    vector<Point>points;
    vector<Point>fillPoints;
    Color fColor;
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
    virtual Point getCenter(){return Point(0, 0);}
    virtual void clip(int, int, int, int){}
    virtual void fill(Color){}
    void refill()
    {
        if(!fillPoints.empty())
        {
            fillPoints.clear();
            fill(fColor);
        }
        this->update();
    }
    Mode type(){return _type;}

    void drawCenter()
    {
        auto center = getCenter();
        center.setColor(YELLOW);
        getCenter().drawCircle();
    }

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
    vector<Point>getFillPoints()
    {
        return fillPoints;
    }
};

#endif // SHAPE_H
