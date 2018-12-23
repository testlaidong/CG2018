#ifndef COMMON_H
#define COMMON_H

#include <map>
#include "drawer/drawer.h"
#include "mode.h"
#include "cutbox.h"

extern Mode mode;
extern std::map<Mode, FigureGenerator *> *drawers_ref;
extern IShape* selected;
extern BoundingBox* boundingBox;
extern CutBox* cutBox;
extern vector<IShape *>*shapes_ref;
extern Color fillColor;

extern void resetCutBox();

class PaintWidget;
extern PaintWidget *pWidget;

#endif // COMMON_H
