#include "point.h"
#include "GL/gl.h"
#include <cmath>

Point::Point(int x_loc, int y_loc):x(x_loc), y(y_loc), r(0), g(0), b(0)
{

}

void Point::setRGB(int r, int g, int b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

void Point::draw()
{
    glBegin(GL_POINTS);
    glColor3f(r, g, b);
    glVertex2i(x, y);
    glEnd();
}

void Point::drawCircle()
{

    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 1.0);
    int n = 100;
    GLfloat R = 5.0f;
    GLfloat pi = 3.1415926536f;
    for(int i=0;i<n;i++)
        glVertex2f(x+R*cos(2*pi/n*i), y+R*sin(2*pi/n*i));
    glEnd();
}

void Point::reset(int x, int y)
{
    this->x = x;
    this->y = y;
}

bool Point::operator==(const Point& d)
{
    int dx = d.x - x;
    int dy = d.y - y;
    int dd = dx * dx + dy * dy;
    return dd <= 25;
}

int Point::operator-(const Point& d)
{
    int dx = d.x - x;
    int dy = d.y - y;
    int dd = dx * dx + dy * dy;
    return static_cast<int>(sqrt(dd));
}

bool Point::operator <= (const Point& d)
{
    return x <= d.x and y <= d.y;
}

void Point::translate(int dx, int dy)
{
    x += dx;
    y += dy;
}
