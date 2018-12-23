#ifndef POINT_H
#define POINT_H

struct Color;

#include <iostream>
using namespace std;

class Point
{
    int x;
    int y;
    int r, g, b;
public:
    Point(){}
    Point(int x, int y);
    void setRGB(int r, int g, int b);
    void setColor(Color color);
    void reset(int x, int y);
    void draw();
    void drawCircle(int r = 0, int g = 0, int b = 1);
    void translate(int dx, int dy);
    void scale(Point center, double s);
    void rotate(Point center, double angle);
    int getX(){return x;}
    int getY() {return y;}
    bool operator ==(const Point& d);
    int operator -(const Point& d);
    bool operator <= (const Point& d);
    friend ostream& operator<<(ostream&out, const Point& p);
};

struct Color
{
    float r;
    float g;
    float b;
    Color(){}
    Color(float red, float green, float blue): r(red), g(green), b(blue){}
    void set(float red, float green, float blue)
    {
        r = red;
        g = green;
        b = blue;
    }
    bool operator==(const Color&c)
    {
        return c.r == r and c.g == g and c.b == b;
    }
    bool operator != (const Color&c)
    {
        return c.r != r or c.g != g or c.b != b;
    }
};

#define BLACK Color(0, 0, 0)
#define BLUE Color(0, 0, 1)
#define YELLOW Color(255, 255, 0)

#endif // POINT_H
