#pragma once
#include "base.h"
class CMyVector2d :
	public CBase
{
public:
	CMyVector2d(void);
	~CMyVector2d(void);

	CMyVector2d(double x, double y) 
	{ 
		// Constructor 
		this->x = x; 
		this->y = y; 
	} 
	CMyVector2d operator+(CMyVector2d v); // ADD 2 Vectors 
	CMyVector2d operator-(CMyVector2d v); // Subtraction 
	double operator^(CMyVector2d v); // Dot Product 
	CMyVector2d operator*(CMyVector2d v); // Cross Product 
	double magnitude() 
	{ 
		return sqrt(pow(x, 2) + pow(y, 2)); 
	} 

private: 
	double x, y; 
};

