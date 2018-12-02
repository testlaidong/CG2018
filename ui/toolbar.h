#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>

class ToolBar : public QToolBar
{
    Q_OBJECT
public:
    ToolBar(QWidget *parent = nullptr);
    ~ToolBar(void){}

private:
    void CreateToolBar(void);

public slots:
    void onLineClicked();
    void onCircleClicked();
    void onOvalClicked();
    void onCurveClicked();
    void onRectangleClicked();
    void onPolygonClicked();

private:
    QAction                 *m_Line;
    QAction                 *m_Circle;
    QAction                 *m_Oval;
    QAction                 *m_Curve;
    QAction                 *m_Rectangle;
    QAction                 *m_Polygon;
};

#endif
