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

void Point::setColor(Color color)
{
    this->r = color.r;
    this->g = color.g;
    this->b = color.b;
}

void Point::draw()
{
    glBegin(GL_POINTS);
    glColor3f(r, g, b);
    glVertex2i(x, y);
    glEnd();
}

void Point::drawCircle(int, int, int)
{

    glBegin(GL_POLYGON);
    glColor3f(this->r, this->g, this->b);
    int n = 100;
    GLfloat R = 3.0f;
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

ostream& operator<<(ostream&out, const Point& p)
{
    out << "(" << p.x << "," << p.y << ")";
}

void Point::translate(int dx, int dy)
{
    x += dx;
    y += dy;
}

void Point::scale(Point center, double s)
{
    auto x0 = x * s + center.getX()*(1 - s);
    auto y0 = y * s + center.getY()*(1 - s);
    reset(static_cast<int>(x0), static_cast<int>(y0));
}

void Point::rotate(Point r, double angle)
{
    auto x0 = r.getX() + (x - r.getX()) * cos(angle) - (y - r.getY()) * sin(angle);
    auto y0 = r.getY() + (x - r.getX()) * sin(angle) + (y - r.getY()) * cos(angle);
    reset(static_cast<int>(x0), static_cast<int>(y0));
}
