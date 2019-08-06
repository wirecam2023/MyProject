#pragma once
#include "Point.h"
#include "Line.h"
#include "Polyline.h"
#include <vector>
#include "ModalEntity.h"
using namespace std;

class CInputAndOutput
{
public:
	CInputAndOutput(void);
	void InputData(	char *filename, CModalEntity& modelEntity);

	//读取txt文件中的每一行
	Point ReadPoint(string readline);
	BOOL HasInputData();

	~CInputAndOutput(void);

private:
	vector<Point> PolylinePointVector;
	vector<CLine> m_LineVector;
	BOOL DoesInputData;
	
};

