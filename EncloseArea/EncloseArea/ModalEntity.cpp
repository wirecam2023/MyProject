#include "stdafx.h"
#include "ModalEntity.h"


CModalEntity::CModalEntity(void)
{
}


void CModalEntity::AddLine( CLine line )
{
	m_LineVector.push_back(line);
}

void CModalEntity::AddPolyline( CPolyline polyline )
{
	m_PolylineVector.push_back(polyline);
}

std::vector<CLine> CModalEntity::GetLine(vector<CLine> m_LineVector)
{
	vector<CLine> line;
	for (auto i = m_LineVector.begin(); i != m_LineVector.end(); ++i)
	{
		line.push_back(*i);
	}
	return line;
}

CLine CModalEntity::GetLine(int i)
{
	return m_LineVector[i];
}

std::vector<CLine> CModalEntity::GetLineVector()
{
	return m_LineVector;
}

std::vector<CPolyline> CModalEntity::GetPolylineVector()
{
	return m_PolylineVector;
}

int CModalEntity::getLineNum()
{
	return m_LineVector.size();
}

CModalEntity::~CModalEntity(void)
{
}
