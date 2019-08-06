#pragma once

#include "Point.h"
#include "Base.h"
#include <vector>
using namespace std;
class CLine:CBase
{
public:
	CLine();
	~CLine();
	CLine(const CLine& src);
	CLine(Point P1, Point P2);
	CLine& operator=(const CLine& src);

	Point getStartPoint();
	Point getEndPoint();
	void setStartPoint(const Point& pt);
	void setEndPoint(const Point& pt);

	void setPoints(const Point &p1, const Point &p2);

	void draw(CDC* pDC);
	void read(ifstream* ReadFile);
	//void read(CFile* pFiler);
private:
	Point m_p1;
	Point m_p2;
};

