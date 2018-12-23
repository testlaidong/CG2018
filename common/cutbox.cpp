#include "cutbox.h"
#include "line.h"

CutBox::CutBox(Point p0, Point p1):Rect(p0, p1)
{
    setBoundary();
    _mode = _Mode::DRAW_BOX;
    selectedPoint = nullptr;
}

void CutBox::setBoundary()
{
    xmin = min(start.getX(), end.getX());
    xmax = max(start.getX(), end.getX());
    ymin = min(start.getY(), end.getY());
    ymax = max(start.getY(), end.getY());
}

int CutBox::left()
{
    return xmin;
}

int CutBox::top()
{
    return ymin;
}

int CutBox::bottom()
{
    return ymax;
}

int CutBox::right()
{
    return xmax;
}

void CutBox::setEndPoint(Point p)
{
    Rect::setEndPoint(p);
    setBoundary();
}

void CutBox::draw()
{
    Point p1 = Point(left(), top());
    Point p2 = Point(right(), top());
    Line(p1, p2, true, YELLOW).draw();
    Point p3 = Point(right(), bottom());
    Line(p2, p3, true, YELLOW).draw();
    Point p4 = Point(left(), bottom());
    Line(p3, p4, true, YELLOW).draw();
    Line(p4, p1, true, YELLOW).draw();
}

void CutBox::drawControlPoints()
{
  //  cout << "here" << endl;
    start.setColor(YELLOW);
    end.setColor(YELLOW);
    start.drawCircle();
    end.drawCircle();
    auto p0 = Point(end.getX(), start.getY());
    auto p1 = Point(start.getX(), end.getY());
    p0.setColor(YELLOW);
    p1.setColor(YELLOW);
    p0.drawCircle();
    p1.drawCircle();
}

void CutBox::mousePressEvent(QMouseEvent *event)
{
    if(event->button() != Qt::LeftButton)
        return;
    if(_mode == _Mode::NONE)
    {
        auto p = Point(event->x(), event->y());
        if(isTopLeft(p))
            _mode = _Mode::TOP_LEFT;
        else if(isTopRight(p))
            _mode = _Mode::TOP_RIGHT;
        else if(isBottomLeft(p))
            _mode = _Mode::BOTTOM_LEFT;
        else if(isBottomRight(p))
            _mode = _Mode::BOTTOM_RIGHT;
        else
        {
            _mode = _Mode::MOVE;
            selectedPoint = new Point(p.getX(), p.getY());
        }
    }
}

bool CutBox::in(Point p)
{
    auto x = p.getX();
    auto y = p.getY();
    return x >= left() and x <= right() and y >= top() and y <= bottom();
}

void CutBox::mouseMoveEvent(QMouseEvent *event)
{
    auto p = Point(event->x(), event->y());
    if(_mode == _Mode::DRAW_BOX)
    {
        setEndPoint(p);
    }
    else if(_mode == _Mode::BOTTOM_LEFT)
        moveBottomLeft(p);
    else if(_mode == _Mode::BOTTOM_RIGHT)
        moveBottomRight(p);
    else if(_mode == _Mode::TOP_LEFT)
        moveTopLeft(p);
    else if(_mode == _Mode::TOP_RIGHT)
        moveTopRight(p);
    else if(_mode == _Mode::MOVE)
    {
        auto dx = event->x() - selectedPoint->getX();
        auto dy = event->y() - selectedPoint->getY();
        translate(dx, dy);
        delete selectedPoint;
        selectedPoint = new Point(event->x(), event->y());
    }
    setBoundary();
}

void CutBox::mouseReleaseEvent(QMouseEvent *)
{
    _mode = _Mode::NONE;
}
