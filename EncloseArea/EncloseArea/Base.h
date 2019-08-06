#pragma once
#include "Point.h"

#include <string>
using namespace std;
class CBase
{
public:
	CBase(void);

	CString GetFileData();

	~CBase(void);


	Point ReadPoint( string readline );
};

