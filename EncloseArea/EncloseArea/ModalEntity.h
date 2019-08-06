#pragma once
#include "Line.h"
#include "Polyline.h"
#include <vector>
class CModalEntity
{
public:
	CModalEntity(void);
	void AddLine(CLine line);
	void AddPolyline(CPolyline polyline);

	vector<CLine> GetLine(vector<CLine> m_LineVector);

	vector<CLine> GetLineVector();
	vector<CPolyline> GetPolylineVector();

	int getLineNum();
	CLine GetLine(int i);
	~CModalEntity(void);

private:
	vector<CLine> m_LineVector;
	vector<CPolyline> m_PolylineVector;
};

