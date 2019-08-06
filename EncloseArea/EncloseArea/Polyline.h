#pragma once
#include "Point.h"
#include "Base.h"
#include <vector>
using namespace std; 
class CPolyline:CBase
{
public:
	CPolyline();
	~CPolyline();


	void addPoint(Point point);

	void ClearPolyPointVector();
	vector<Point> getPoints();
	Point getPoint(int nIdx);

	int getPointNum();
	void draw(CDC* pDC);
	void read(ifstream* ReadFile);
private:
	vector<Point> m_PolyPointVector;
};
