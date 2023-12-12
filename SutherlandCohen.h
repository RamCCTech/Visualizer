#pragma once

#include "shape.h"

class SutherlandCohen
{
public:
    SutherlandCohen(Shape region,Line l);
    ~SutherlandCohen();
    Line getClippedLine();

private:
    int computeCode(Point p);
    void setRegion();
    enum RegionCode {
        INSIDE = 0, // 0000
        LEFT = 1,   // 0001
        RIGHT = 2,  // 0010
        BOTTOM = 4, // 0100
        TOP = 8     // 1000
    };

private:
    double mXMin;
    double mXMax;
    double mYMin;
    double mYMax;
    Line mInputLine;
    Shape mRegion;
};

