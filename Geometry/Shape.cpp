#include "pch.h"
#include "Shape.h"

Shape::Shape(const std::vector<Line>& polyLines)
    : mPolyLines(polyLines)  // Use member initializer list
{
}
//Shape::Shape(const std::vector<Point3D>& points)
//    : mPoints(points)  // Use member initializer list
//{
//}

Shape::~Shape()
{
}

std::vector<Line>& Shape::getShape()
{
    return mPolyLines;
}
//std::vector<Point3D>& Shape::getShapePoints()
//{
//    return mPoints;
//}
void Shape::setShape(std::vector<Line> vl)
{
    mPolyLines = vl;
}
void Shape::setShape(std::vector<Point3D> vp)
{
    mPoints = vp;
}

size_t Shape::getSize() const
{
    return mPolyLines.size();
}