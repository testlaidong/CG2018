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

private:
    QAction                 *m_Line;
    QAction                 *m_Circle;
    QAction                 *m_Oval;
};

#endif
