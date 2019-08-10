#include "stdafx.h"
#include "MyVector2d.h"
#include <math.h>       /* acos */
#define PI 3.14159265


CMyVector2d::CMyVector2d():x(0),y(0)
{
}

CMyVector2d::CMyVector2d(double x1, double y1):x(x1),y(y1)
{

}

CMyVector2d::CMyVector2d(const CMyVector2d &v)
{
	x = v.x;
	y = v.y;
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

CMyVector2d& CMyVector2d::operator=(const CMyVector2d &v)
{
	if (this != &v)
	{
		this->x = v.x;
		this->y = v.y;
	}
	return *this;
}

double CMyVector2d::magnitude() 
{ 
	return sqrt(pow(x, 2) + pow(y, 2)); 
} 

double CMyVector2d::DotProduct(CMyVector2d v)
{
	double x1, y1; 
	x1 = x * v.x; 
	y1 = y * v.y; 
	return (x1 + y1); 
}

double CMyVector2d::GetAngleTo(CMyVector2d v)
{
	double angle = 0.0;
	double productValue = this->DotProduct(v);//向量的乘积
	double valA = this->magnitude();//向量a的模
	double valB = v.magnitude();//向量b的模
	double cosValue = productValue / (valA * valB); //余弦公式

	//acos的输入参数必须在[-1,1]之间,否则会"domain error"
	if(cosValue < -1 && cosValue > -2)
	{
		cosValue  = -1;
	}	
	else if (cosValue > 1 && cosValue < 2)
	{
		cosValue = 1;
	}

	//acos返回的是弧度值，转换为角度值
	angle = acos(cosValue) * 180 / PI;
	return angle;
	
}
