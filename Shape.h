#pragma once
#include <vector>
#include "Line.h"

class Shape
{
public:
    Shape(const std::vector<Line>& polyLines);
    ~Shape();

    std::vector<Line>& getShape();
    size_t getSize() const;
    void setShape(std::vector<Line> vl);

private:
    std::vector<Line> mPolyLines;
};