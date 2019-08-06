#include "stdafx.h"
#include "Point.h"
#include <math.h>


//默认构造函数
Point::Point():x(0), y(0)
{

}

//构造函数
Point::Point(double new_x, double new_y)
{
	x = new_x;
	y = new_y;
}
//拷贝构造函数
Point::Point(const Point& src)
{
	x = src.x;
	y = src.y;
}

Point& Point::operator=(const Point& src)
{
	if (this != &src)
	{
		this->x = src.x;
		this->y = src.y;
	}

	return *this;
}

Point::~Point()
{
}

double Point::Distance(const Point &p)  const
{  
	double disX = x - p.x;  
	double disY = y - p.y;  
	return sqrt(disX*disX+disY*disY);  
}  


