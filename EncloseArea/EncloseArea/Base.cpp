#include "stdafx.h"
#include "Base.h"
#include <string>
using namespace std;

CBase::CBase(void)
{

}


CBase::~CBase(void)
{
}

Point CBase::ReadPoint( string readline )
{
	double x1;
	double y1;
	Point point;
	string comma = ",";
	string newline_1=readline.substr(0,readline.find_first_of(comma));
	x1=stod(newline_1);
	string newline_2=readline.substr(readline.find_first_of(comma)+1,readline.size());
	y1=stod(newline_2);

	//获取一个点
	point.x = x1;  
	point.y = y1;
	return point;
}

