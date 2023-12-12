#include "stdafx.h"
#include "Line.h"

Line::Line(Point p1, Point p2)
    : mP1(p1),
    mP2(p2)
{
}
Line::Line(const Line& other)
    : mP1(other.mP1),
    mP2(other.mP2)
{
    // You may need to copy other necessary data members if any
}

Line::~Line()
{
}

Point& Line::p1()
{
    return mP1;
}

Point& Line::p2()
{
    return mP2;
}

Line& Line::operator=(const Line& other)
{
    if (this != &other)  // Check for self-assignment
    {
        // Copy data members from 'other' to 'this'
        mP1 = other.mP1;
        mP2 = other.mP2;
    }
    return *this;
}