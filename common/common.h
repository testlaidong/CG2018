#ifndef COMMON_H
#define COMMON_H

#include <map>
#include "drawer/drawer.h"
#include "mode.h"

extern Mode mode;
extern std::map<Mode, FigureGenerator *> *drawers_ref;

class PaintWidget;
extern PaintWidget *pWidget;

#endif // COMMON_H
