#include "global.h"



global::global()
{
}


global::~global()
{
}
void global::funcTimeCountStart(std::string strUser)
{
	QueryPerformanceFrequency(&m_Freq);
	QueryPerformanceCounter(&m_TimeStart);
	std::cout << strUser << " Time Start" << std::endl;
}
void global::funcTimeCountEnd(std::string strUser)
{
	QueryPerformanceCounter(&m_TimeEnd);
	std::cout << strUser << " Time Consume(s): " << ((m_TimeEnd.QuadPart - m_TimeStart.QuadPart)*1.0 / m_Freq.QuadPart) << std::endl;
}