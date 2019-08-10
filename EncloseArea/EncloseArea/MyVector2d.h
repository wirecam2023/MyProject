#pragma once
#include "base.h"
class CMyVector2d :
	public CBase
{
public:
		CMyVector2d();
	~CMyVector2d(void);

	CMyVector2d(double x1, double y1);
	CMyVector2d(const CMyVector2d &v);
	CMyVector2d& operator=(const CMyVector2d &v);
	double DotProduct(CMyVector2d v);
	double GetAngleTo(CMyVector2d v);

	CMyVector2d operator+(CMyVector2d v); // ADD 2 Vectors 
	CMyVector2d operator-(CMyVector2d v); // Subtraction 
	double operator^(CMyVector2d v); // Dot Product 
	CMyVector2d operator*(CMyVector2d v); // Cross Product 
	double magnitude();

private: 
	double x, y; 
};

