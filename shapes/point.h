#ifndef POINT_H
#define POINT_H

class Point
{
    int x;
    int y;
public:
    Point(){}
    Point(int x, int y);
    void reset(int x, int y);
    void draw();
    int getX(){return x;}
    int getY() {return y;}
    bool operator ==(const Point& d);
    int operator -(const Point& d);
};

#endif // POINT_H
