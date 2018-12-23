#include "common.h"

Mode mode = Mode::MODE_NONE;
std::map<Mode, FigureGenerator *> *drawers_ref;
PaintWidget *pWidget = nullptr;
IShape *selected = nullptr;
BoundingBox* boundingBox = nullptr;
CutBox* cutBox = nullptr;
vector<IShape *>*shapes_ref = nullptr;
Color fillColor = YELLOW;

void resetCutBox()
{
    delete cutBox;
    cutBox = nullptr;
}
