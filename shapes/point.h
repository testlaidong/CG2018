#ifndef POINT_H
#define POINT_H

class Point
{
    int x;
    int y;
    int r, g, b;
public:
    Point(){}
    Point(int x, int y);
    void setRGB(int r, int g, int b);
    void reset(int x, int y);
    void draw();
    void drawCircle();
    void translate(int dx, int dy);
    int getX(){return x;}
    int getY() {return y;}
    bool operator ==(const Point& d);
    int operator -(const Point& d);
    bool operator <= (const Point& d);
};

#endif // POINT_H
