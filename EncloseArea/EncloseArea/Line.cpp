#include "stdafx.h"
#include "Line.h"
#include "Point.h"
#include "Base.h"
#include "InputAndOutput.h"

#include <iostream>
#include <string>
#include <iosfwd>
#include <fstream> 

//默认构造函数
CLine::CLine()
{

}

//构造函数
CLine::CLine(Point p1, Point p2)
{
	m_p1 = p1;
	m_p2 = p2;
}

//拷贝构造函数
CLine::CLine(const CLine& src)
{
	m_p1 = src.m_p1;
	m_p2 = src.m_p2;
}

//赋值构造函数
CLine& CLine::operator=(const CLine& src)
{
	if (this != &src)
	{
		this->m_p1 = src.m_p1;
		this->m_p2 = src.m_p2;
	}
	return *this;
}


CLine::~CLine()
{

}


Point CLine::getStartPoint()
{
	return m_p1;
}

Point CLine::getEndPoint()
{
	return m_p2;
}

void CLine::setStartPoint(const Point& pt)
{
	m_p1 = pt;
}

void CLine::setEndPoint(const Point& pt)
{
	m_p2 = pt;
}

void CLine::setPoints(const Point &p1, const Point &p2)
{
	setStartPoint(p1);
	setEndPoint(p2);
}

void CLine::draw(CDC* pDC)
{
	Point startPoint = getStartPoint();
	Point endPoint = getEndPoint();
	pDC->MoveTo((int)startPoint.x,(int)startPoint.y);
	pDC->LineTo((int)endPoint.x,(int)endPoint.y);
}


void CLine::read(ifstream* ReadFile)
{
	Point StartPoint;
	Point EndPoint;
	string readline;
	//移动到下一行
	getline(*ReadFile,readline,'\n');
	//获取第一个点
	StartPoint = ReadPoint(readline);
	//移动到下一行
	getline(*ReadFile,readline,'\n');
	//获取第二个点
	EndPoint = ReadPoint(readline);			

	setPoints(StartPoint,EndPoint);
}
