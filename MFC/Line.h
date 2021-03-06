#pragma once
#include <afx.h>
#include <afxtempl.h>

class Points :
	public CObject
{
	DECLARE_SERIAL(Points);
public:
	void addPoint(const CPoint& point);
	void clear();
	const CArray<CPoint>& getPoints();
private:
	CArray<CPoint> points;
public:
	virtual void Serialize(CArchive& ar);
};

