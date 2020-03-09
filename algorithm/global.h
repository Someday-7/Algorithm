#pragma once
#include <cstdio>
#include <cstring>
#include <cassert>
#include <windows.h>
#include <string>
#include <iostream>
class global
{
public:
	global();
	~global();
	//time count
	void funcTimeCountStart(std::string strUser = "");
	void funcTimeCountEnd(std::string strUser = "");
private:
	LARGE_INTEGER m_Freq;
	LARGE_INTEGER m_TimeStart;
	LARGE_INTEGER m_TimeEnd;
};

