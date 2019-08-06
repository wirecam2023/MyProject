#pragma once
class Point
{
public:
	//默认构造函数
	Point();

	~Point(void);

	double Distance(const Point &p) const; 
	Point(double new_x, double new_y);
	Point(const Point& src);//定义拷贝构造函数;
	Point& operator=(const Point& src);



public:
	double x;
	double y;
};

