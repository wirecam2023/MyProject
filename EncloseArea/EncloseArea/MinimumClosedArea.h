#pragma once
#include "Line.h"
#include "Polyline.h"
#include <vector>
using namespace std;
class CMinimumClosedArea
{
public:
	CMinimumClosedArea(void);
	~CMinimumClosedArea(void);
	//输入line和polyline数组并转为线段
	vector<CLine> get_line(vector<CLine> LineVector,vector<CPolyline> PolylineVector);
	vector<CLine> remove_isolated_line(vector<CLine> input);
	bool doselinecross(CLine L1, CLine L2);
	bool Be_equal_to(Point A, Point B);
	bool Be_equal_to(double A, double B);
	bool isonline(Point P1, Point P2, Point Q); //FVector表示点,判断Q是否在line(p1,p2)上;
	vector<CLine> breaklines(vector<CLine> input);
	Point getcrosspoint(CLine L1, CLine L2);
	vector<CLine> removenonefieldlines(vector<CLine> input);

	vector<vector<CLine>> get_all_big_field(vector<CLine> input);



private:
	vector<CLine> LineCollection;
};

