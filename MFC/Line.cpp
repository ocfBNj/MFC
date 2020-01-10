#include "pch.h"
#include "Line.h"

void Points::addPoint(const CPoint& point)
{
	points.Add(point);
}

const CArray<CPoint>& Points::getPoints()
{
	// TODO: insert return statement here
	return points;
}
