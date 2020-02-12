#include "wildcardMatch.h"
#include <cstring>
#include <cassert>
#include <cstdio>
wildcardMatch::wildcardMatch()
{
	startSearch();
}


wildcardMatch::~wildcardMatch()
{
}
void wildcardMatch::startSearch()
{
	const char pStrSrc[5][32] = { "x1.v(out)","x1.x2.x3","v(in)","v(out)","x1.x2.v(out)" };
	const char pattern[32] = { "*.v(?ut)" };
	for (int i = 0; i < 5; ++i)
	{
		bool bRet = strMatch(pStrSrc[i],pattern);
		printf("find %s result %d\n", pStrSrc[i], bRet);
	}
}
bool wildcardMatch::strMatch(const char* pSrc, const char* pPattern)
{
	if (*pSrc == '\0' && *pPattern == '\0')//匹配完成
	{
		return true;
	}
	if (*pSrc == '\0'|| *pPattern == '\0')//任一串先结束，匹配失败
	{
		return false;
	}

	if (*pSrc == *pPattern || *pPattern == '?')//匹配一个字符
	{
		return strMatch(pSrc + 1, pPattern + 1);
	}
	else if (*pPattern == '*')
	{
		if (*(pPattern + 1) == '\0')//原始串后面全部匹配（多个）
		{
			return true;
		}
		else
		{
			//匹配0个或者匹配一个
			if (strMatch(pSrc, pPattern + 1) || strMatch(pSrc + 1, pPattern + 1))
			{
				return true;
			}
			else//匹配多个
			{
				//*后串是否还包含*
				int iPos = checkNextWildcardPos(pPattern);
				if (iPos)
				{
					//继续当前通配符匹配(不考虑两个通配符挨着写)
					char* pStrModle = new char[iPos+1];
					memset(pStrModle,'\0', iPos);
					memcpy(pStrModle, pPattern + 1, iPos);

					pStrModle[iPos] = '\0';
					int iNextSrcPos = kmpMatch(pSrc, pStrModle);
					delete[]pStrModle;
					if (iNextSrcPos != -1)
					{
						pPattern = pPattern + iPos + 1;
						pSrc = pSrc + iNextSrcPos;
						return strMatch(pSrc, pPattern);
					}
					else
					{
						return false;
					}
				}
				else//0 未找到
				{
					//匹配末尾字符串
					int iLenTotal = strlen(pSrc);
					int iLenLast = strlen(++pPattern);
					return strMatch(pSrc + iLenTotal - iLenLast, pPattern);
				}
				
			}
		}
	}
	else
	{
		return false;
	}
}
int wildcardMatch::checkNextWildcardPos(const char* pStr)
{
	const char* pTemp = ++pStr;
	int iLen = strlen(pTemp);
	int iPos = 0;
	for (;iPos < iLen;++iPos)
	{
		if(pTemp[iPos] == '*' || pTemp[iPos] == '?')
		{		
			return iPos;
		}
	}
	return 0;
}
int wildcardMatch::kmpMatch(const char* pSrc, const char* pPattern)
{
	assert(pPattern);
	assert(pSrc);
	//init next array
	int iLen = strlen(pPattern);
	int* pNextArray = new int[iLen];
	memset(pNextArray, -1, iLen*sizeof(int));
	int j = 0;
	int k = -1;
	while (j < iLen - 1)
	{
		if (pPattern[j] == pPattern[k] || k == -1)
		{
			++j;
			++k;
			if (pPattern[j] != pPattern[k])
			{
				pNextArray[j] = k;
			}
			else
			{
				pNextArray[j] = pNextArray[k];
			}
		}
		else
		{
			k = pNextArray[k];
		}
	}
	//match process
	int i = 0;
	j = -1;
	int iDestLen = strlen(pSrc);
	int iModelLen = iLen;
	for (; i < iDestLen && j < iModelLen;)
	{
		if (j == -1)
		{
			//匹配第一个
			++j;
			if (pSrc[i] == pPattern[j])
			{
				++i;
				++j;
			}
			else
			{
				++i;
				j = -1;
			}
		}
		else if (j != -1 && pSrc[i] == pPattern[j])
		{
			++i;
			++j;
		}
		else
		{
			j = pNextArray[j];
		}
	}
	if (j != iModelLen)
	{
		i = -1;
	}
	//free memory
	delete[]pNextArray;

	return i;
}