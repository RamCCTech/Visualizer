#include "stdafx.h"
#include "Shape.h"

Shape::Shape(const std::vector<Line>& polyLines)
    : mPolyLines(polyLines)  // Use member initializer list
{
}

Shape::~Shape()
{
}

std::vector<Line>& Shape::getShape()
{
    return mPolyLines;
}

void Shape::setShape(std::vector<Line> vl)
{
    mPolyLines = vl;
}

size_t Shape::getSize() const
{
    return mPolyLines.size();
}