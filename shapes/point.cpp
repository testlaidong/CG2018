#include "point.h"
#include "GL/gl.h"
#include <cmath>

Point::Point(int x_loc, int y_loc):x(x_loc), y(y_loc)
{
}

void Point::draw()
{
    glColor3f(0.0, 0.0, 0.0);
    glVertex2i(x, y);
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
