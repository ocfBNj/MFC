#include "pch.h"
#include "Line.h"

void Points::addPoint(const CPoint& point)
{
	points.Add(point);
}

void Points::clear()
{
	points.RemoveAll();
}

const CArray<CPoint>& Points::getPoints()
{
	// TODO: insert return statement here
	return points;
}


void Points::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		this->points.Serialize(ar);
	}
	else
	{	// loading code
		this->points.Serialize(ar);
	}
}
