#pragma once

#include "shape.h"


class SutherlandHodgman
{
public:
	SutherlandHodgman(Shape region, Shape polygon);
	~SutherlandHodgman();
	Shape getClippedPolygon();

private:
	void clipAlongLine(Line l);
	double xIntersect(Line l1, Line l2);
	double yIntersect(Line l1, Line l2);

private:
	Shape mPolygon;
	Shape mRegion;
};