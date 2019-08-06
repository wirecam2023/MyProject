#include "stdafx.h"
#include "MinimumClosedArea.h"

/*-------------------程序思路------------------------*/
/*
	①：得到线段集合S（线段的集合为line和polyline）

	②：移除孤立的线段（两端的点都是孤立的）；

	③：拆分所有的线段（就是将所有的相交线线段拆分开,得到新的线段集合S）

	④：移除一个端点孤立的线段（一个端点孤立的线段是不构成多边形的）

	⑤：找出所有的大区域线段集合M,M是线段集合的集合,二维数组；
	（这里的大区域指的是：以任意一条线为起点找到和它相交的其他线段,再找到和这些线段相交的其他线段,
	  直到找不到相交线段,那么这些线段的集合就是一个大区域Mi.然后找完所有的大区域）

	⑥：分别对每一个大区域进行封闭区域的提取。
*/

CMinimumClosedArea::CMinimumClosedArea(void)
{
}


CMinimumClosedArea::~CMinimumClosedArea(void)
{
}

/*--------------------程序思路①：得线段我们的线段集合S（本次项目为line和polyline)-----------------*/
//输入line和polyline数组并转为线段
vector<CLine> CMinimumClosedArea::get_line(vector<CLine> LineVector,vector<CPolyline> PolylineVector)
{
	vector<CLine> AllLineSegment;
	for (unsigned int i = 0; i < LineVector.size();i++)
	{
		AllLineSegment.push_back(LineVector[i]);
	}

	//将polyline转换成line，然后添加到AllLineSegment
	for (unsigned int i = 0; i < PolylineVector.size();i++)
	{
		CPolyline polyline;
		polyline = PolylineVector[i];
		for(int i = 1; i<polyline.getPointNum(); i++) //遍历polyline的每一个点
		{
			CLine line;
			line.setPoints(polyline.getPoint(i-1),polyline.getPoint(i));
			AllLineSegment.push_back(line);
		}	
	}
	return AllLineSegment;
}


/*-----------------------程序思路②：移除孤立的线段（两端的点都是孤立的）----------------------------*/

//移除所有的孤立线段，与其他线段都不相交的线段。
vector<CLine> CMinimumClosedArea::remove_isolated_line(vector<CLine> input)
{
	vector<CLine> lines;
	lines = input;
	vector<CLine> output;

	for (unsigned int i = 0; i < lines.size(); i++)
	{
		vector<CLine> M;
		M = lines;

		for (unsigned int j = 0; j < M.size(); j++)
		{
			if (doselinecross(lines[i], M[j]))
			{
				output.push_back(lines[i]);
				break;
			}
		}
	}
	return output;
}

//判断线段是否相交
bool CMinimumClosedArea::doselinecross(CLine L1, CLine L2)
{
	double x1 = L1.getStartPoint().x;
	double y1 = L1.getStartPoint().y;
	double x2 = L1.getEndPoint().x;
	double y2 = L1.getEndPoint().y;

	double x3 = L2.getStartPoint().x;
	double y3 = L2.getStartPoint().y;
    double x4 = L2.getEndPoint().x;
	double y4 = L2.getEndPoint().y;
	//两条直线重合
	if ((Be_equal_to(L1.getStartPoint(), L2.getStartPoint()) && Be_equal_to(L1.getEndPoint(), L2.getEndPoint())) || (Be_equal_to(L1.getStartPoint(), L2.getEndPoint()) && Be_equal_to(L1.getEndPoint() ,L2.getStartPoint()))) //两条line的端点相同
	{
		return false;
	}
	if (Be_equal_to((x3 - x4) * (y1 - y2) - (x1 - x2) * (y3 - y4), 0.f) || Be_equal_to((y1 - y2) * (x3 - x4) - (x1 - x2) * (y3 - y4), 0.f))//斜率相等
	{
		if (Be_equal_to(L1.getStartPoint(), L2.getStartPoint()) || Be_equal_to(L1.getEndPoint(), L2.getEndPoint()) || Be_equal_to(L1.getEndPoint(), L2.getStartPoint()) || Be_equal_to(L1.getEndPoint(), L2.getEndPoint()))
		{
			return true;
		}
		else  //不相交
		{
			return false;
		}
	}
	double X = ((x1 - x2) * (x3 * y4 - x4 * y3) - (x3 - x4) * (x1 * y2 - x2 * y1)) / ((x3 - x4) * (y1 - y2) - (x1 - x2) * (y3 - y4));
	double Y = ((y1 - y2) * (x3 * y4 - x4 * y3) - (x1 * y2 - x2 * y1) * (y3 - y4)) / ((y1 - y2) * (x3 - x4) - (x1 - x2) * (y3 - y4));
	Point Q;
	Q.x = X;
	Q.y = Y;
	//判断交点是否同时在L1、L2上
	if (isonline(L1.getStartPoint(), L1.getEndPoint(), Q) && isonline(L2.getStartPoint(), L2.getEndPoint(), Q))
	{
		return true;
	}
	else//交点在延长线上
	{
		return false;
	}
}

//判断两个浮点数是否相等
bool CMinimumClosedArea::Be_equal_to(double A, double B)
{
	if (((A - B) < 0.1) && ((A - B) > -0.1))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//判断点A和点B是否相等
bool CMinimumClosedArea::Be_equal_to(Point A, Point B)
{
	if (Be_equal_to(A.x, B.x) && Be_equal_to(A.y, B.y))
	{
		return true;
	}
	else
	{
		return false;
	}
}


//判断点是否在线上
bool CMinimumClosedArea::isonline(Point P1, Point P2, Point Q) //FVector表示点,判断Q是否在line(p1,p2)上
{
	if (Be_equal_to(Q, P1) || Be_equal_to(Q, P2)) //点Q是线段的端点
	{
		return true;
	}
	if (Be_equal_to(Q.Distance(P1) + Q.Distance(P2), P1.Distance(P2)))//点Q在line的两端点之间
	{
		return true;
	}
	return false;
}


/*-------------程序思路③：拆分所有的线段（就是将所有的相交线线段拆分开，得到新的线段集合S）--------------*/

//分割所有的线段，得到新的线段数组
vector<CLine> CMinimumClosedArea::breaklines(vector<CLine> input)
{
	vector<CLine> lines;
	lines.clear();
	lines = input;
	vector<CLine> output;
	output.clear();
	for (unsigned int i = 0; i < lines.size(); i++)
	{
		vector<Point> crosspointVec;
		for (unsigned int j = 0; j < lines.size(); j++)
		{
			if (doselinecross(lines[i], lines[j])) //两条line相交
			{ 
				//交点不是lines[i]的起点和终点
				Point crosspoint;
				crosspoint = getcrosspoint(lines[i], lines[j]);
				if ((!Be_equal_to(crosspoint, lines[i].getStartPoint()))  
					&& (!Be_equal_to(crosspoint, lines[i].getEndPoint())))
				{
					crosspointVec.push_back(crosspoint);
				}
			}
		}

		crosspointVec.insert(crosspointVec.begin(),lines[i].getStartPoint());
		crosspointVec.push_back(lines[i].getEndPoint());
		//计算每一个交点与line的起点距离，并增序排序
	    for (unsigned int m = 0;m < crosspointVec.size() - 1; m++)
	    {
			for (unsigned int n = 0; n < crosspointVec.size()-m-1; n++ )
			{
				double Distm = lines[i].getStartPoint().Distance(crosspointVec[n]);
				double Distn = lines[i].getStartPoint().Distance(crosspointVec[n+1]);
				if (Distm > Distn)
				{
					swap(crosspointVec[n],crosspointVec[n+1]);
				}
			}
		
	    }


		//将line[i]所截断的线段放入output中

		for (unsigned int k = 0;k < crosspointVec.size()-1; k++)
		{
			CLine lineSegment;
			lineSegment.setPoints(crosspointVec[k],crosspointVec[k + 1]);
			output.push_back(lineSegment);
		}

	}
	return output;
}

//获取交点
Point CMinimumClosedArea::getcrosspoint(CLine L1, CLine L2)
{

	double x1 = L1.getStartPoint().x;
	double y1 = L1.getStartPoint().y;
	double x2 = L1.getEndPoint().x;
	double y2 = L1.getEndPoint().y;
	double x3 = L2.getStartPoint().x;
	double y3 = L2.getStartPoint().y;
	double x4 = L2.getEndPoint().x;
	double y4 = L2.getEndPoint().y;
	Point Q;
	Q.x = 0;
	Q.y = 0;

	if (!doselinecross(L1, L2)) //判断两条lime是否相交
	{
		return Q;
	}
	//L1的起点与L2的起点或端点相交
	if (Be_equal_to(L1.getStartPoint(), L2.getStartPoint()) || Be_equal_to(L1.getStartPoint(), L2.getEndPoint()))
	{
		return L1.getStartPoint(); 
	}
	//L1的终点与L2的起点或终点相交
	if (Be_equal_to(L1.getEndPoint(), L2.getStartPoint()) || Be_equal_to(L1.getEndPoint(), L2.getEndPoint()))
	{
		return L1.getEndPoint();
	}
	//计算交点
	double X = ((x1 - x2) * (x3 * y4 - x4 * y3) - (x3 - x4) * (x1 * y2 - x2 * y1)) / ((x3 - x4) * (y1 - y2) - (x1 - x2) * (y3 - y4));
	double Y = ((y1 - y2) * (x3 * y4 - x4 * y3) - (x1 * y2 - x2 * y1) * (y3 - y4)) / ((y1 - y2) * (x3 - x4) - (x1 - x2) * (y3 - y4));
	Q.x = X;
	Q.y = Y;

	//Q点同时在L1和L2上
	if (isonline(L1.getStartPoint(), L1.getEndPoint(), Q) && isonline(L2.getStartPoint(), L2.getEndPoint(), Q))
	{
		return Q;
	}
	else
	{
		Q.x = 0;
		Q.y = 0;

		return Q;
	}
}


/*----------------------程序思路④：移除一个端点孤立的线段（一个端点孤立的线段是不构成多边形的）------------------------*/

//移除端点孤立的线段
vector<CLine> CMinimumClosedArea::removenonefieldlines(vector<CLine> input)
{
	vector<CLine> resultLines;
	int nSize = input.size();
	for (int i = 0;i < nSize; i++)
	{
		vector<Point> crossPoint;
		for (int j = 0;j < nSize; j++)
		{
			if (doselinecross(input[i],input[j]))
			{
				crossPoint.push_back(getcrosspoint(input[i],input[j]));
			}
		}

		bool bEqual = false;
		for (unsigned int m = 0;m < crossPoint.size() ;m++)
		{
			if (Be_equal_to(input[i].getStartPoint(),crossPoint[m]))
			{
				bEqual = true;
			}
		}

		if (bEqual)
		{
			for (unsigned int n = 0;n < crossPoint.size() ;n++)
			{
				if (Be_equal_to(input[i].getEndPoint(),crossPoint[n]))
				{
					resultLines.push_back(input[i]);
				}
			}
		}

	}

	
	return resultLines;
}

/*-------------------程序思路⑤：找出所有的大区域线段集合M,M是线段集合的集合-----------------*/


vector<vector<CLine>> CMinimumClosedArea::get_all_big_field(vector<CLine> input)
{
	vector<CLine> alllines;
	alllines.clear();
	alllines = input;
	vector<CLine> M;
	M.clear();
	vector<vector<CLine>> output;
	output.clear();
	vector<CLine> field;
	field.clear();
	while (alllines.size() != 0)
	{
		M.clear();
		M.push_back(alllines[0]);
		for (unsigned int i = 0; i < M.size(); i++)
		{
			for (unsigned int j = 0; j < alllines.size();)
			{
				if (doselinecross(M[i], alllines[j]))
				{
					M.push_back(alllines[j]);
					alllines.erase(alllines.begin() + j);
					i = 0;
					j = 0;
					break;
				}
				else
				{
					j = j + 1;
				}
			}
		}
		M.erase(M.begin());//可能去除有点问题。
		output.push_back(M);
		M.clear();
	}
	return output;
}





