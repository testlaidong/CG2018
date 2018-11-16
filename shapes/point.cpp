#include "point.h"
#include "GL/gl.h"

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
