#pragma once
#include <afx.h>
#include <afxtempl.h>

class Points :
	public CObject
{
public:
	void addPoint(const CPoint& point);
	const CArray<CPoint>& getPoints();
private:
	CArray<CPoint> points;
};

