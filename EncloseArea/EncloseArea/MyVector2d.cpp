#include "stdafx.h"
#include "MyVector2d.h"


CMyVector2d::CMyVector2d(void)
{
}


CMyVector2d::~CMyVector2d(void)
{
}

// Addition of vectors 
CMyVector2d CMyVector2d::operator+(CMyVector2d v) 
{ 
	double x1, y1; 
	x1 = x + v.x; 
	y1 = y + v.y; 
	return CMyVector2d(x1, y1); 
} 

// Subtraction of vectors 
CMyVector2d CMyVector2d::operator-(CMyVector2d v) 
{ 
	double x1, y1; 
	x1 = x - v.x; 
	y1 = y - v.y; 
	return CMyVector2d(x1, y1); 
} 

// Dot product of vectors 
double CMyVector2d::operator^(CMyVector2d v) 
{ 
	double x1, y1; 
	x1 = x * v.x; 
	y1 = y * v.y; 
	return (x1 + y1); 
} 

// Cross product of vectors 
CMyVector2d CMyVector2d::operator*(CMyVector2d v) 
{ 
	return CMyVector2d(x*v.x, y*v.y); 
} 