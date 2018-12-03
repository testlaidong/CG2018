#ifndef COMMON_H
#define COMMON_H

enum class Mode
{
    MODE_NONE,
    MODE_DRAW_LINE,
    MODE_DRAW_CIRCLE,
    MODE_DRAW_OVAL,
    MODE_DRAW_CURVE,
    MODE_DRAW_RECTANGLE,
    MODE_DRAW_POLYGON,
    MODE_SELECT
};

#include <map>
#include "drawer/drawer.h"
extern Mode mode;
extern std::map<Mode, FigureGenerator *> *drawers_ref;

class PaintWidget;
extern PaintWidget *pWidget;

#endif // COMMON_H