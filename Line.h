#pragma once
#include "Point.h"

class Line
{
public:
    Line(Point p1, Point p2);  // Use copies instead of references
    Line(const Line& other);
    ~Line();
    Line& operator=(const Line&);

    Point& p1();  // Return Point reference
    Point& p2();

private:
    Point mP1;  // Use copies instead of references
    Point mP2;
};
