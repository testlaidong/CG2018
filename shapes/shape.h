#ifndef SHAPE_H
#define SHAPE_H

#include <vector>

class IShape
{
    static std::tuple<float, float, float> color;
public:
    virtual void draw(){}
};

#endif // SHAPE_H
