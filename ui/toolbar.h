#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>
#include <QLabel>
#include <QPushButton>

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
    void onSelectClicked();
    void onEnlargeClicked();
    void onNarrowClicked();
    void onRotateRightClicked();
    void onRotateLeftClicked();
    void onCutClicked();
    void onDeleteClicked();
    void onFillClicked();
    void pickColor();
    void onSaveClicked();
    void on3dWidgetClicked();

private:
    QAction                 *m_Line;
    QAction                 *m_Circle;
    QAction                 *m_Oval;
    QAction                 *m_Curve;
    QAction                 *m_Rectangle;
    QAction                 *m_Polygon;
    QAction                 *m_Select;
    QAction                 *m_enlarge;
    QAction                 *m_narrow;
    QAction                 *m_rotateRight;
    QAction                 *m_rotateLeft;
    QAction                 *m_Cut;
    QAction                 *m_Fill;
    QAction                 *m_ColorPicker;
    QAction                 *m_Delete;
    QAction                 *m_Save;
    QAction                 *m_3dWidget;
};

#endif
