#include "kmp.h"
#include <assert.h>
#include <string.h>
#include <QDebug>
KMP::KMP()
{
    const char* pDest = "ABCDABDCABCDABFHJKEKASABABCDABD";
    const int iDest = strlen(pDest);

    char* arrayDest = new char[iDest];
    assert(arrayDest);
    memcpy(arrayDest,pDest,iDest);
    char arrayModle[8] = {"ABCDABD"};
    int* pNextArray = ConstructNextArray(arrayModle);
    assert(pNextArray);
    for(int i=0;i<strlen(arrayModle);++i)
    {
        qDebug("%d:%d",i,pNextArray[i]);
    }
    int i=0,j=-1;
    int iDestLen = strlen(arrayDest);
    int iModelLen = strlen(arrayModle);
    qDebug("iDestLen:%d iModelLen:%d",iDestLen,iModelLen);
    for(;i<iDestLen&&j<iModelLen;)
    {
        if(j == -1 )
        {
            //匹配第一个
            ++j;
            if(arrayDest[i] == arrayModle[j])
            {
                ++i;
                ++j;
                qDebug("1-i:%d j:%d c:%c",i,j,arrayDest[i]);
            }
            else
            {
                ++i;
                j = -1;
            }
        }
        else if(j != -1 && arrayDest[i] == arrayModle[j])
        {
            ++i;
            ++j;
            qDebug("2-i:%d j:%d c:%c",i,j,arrayDest[i]);
        }
        else
        {
            j = pNextArray[j];
        }
    }
    if(j == iModelLen)
    {
        qDebug("find index %d %s",i-j,&arrayDest[i-j]);
    }
    else
    {
        qDebug("not find index");
    }

    delete pNextArray;
    pNextArray = nullptr;
    delete arrayDest;
    arrayDest = nullptr;
}

int *KMP::ConstructNextArray(char* pSrcStr)
{
    assert(pSrcStr);
    int iLen = strlen(pSrcStr);
    int* pNextArray = new int[iLen];
    memset(pNextArray,-1,iLen);
    int j = 0;
    int k = -1;
    while(j < iLen -1)
    {
        //#1、j代表当前字符位置，求当前字符之前的前缀后缀相同的个数
        //#2、k代表前缀的起始位置
        //#3、连续相等的情况下，下一个位置前缀后缀相同的个数等于上一个的+1
        if(pSrcStr[j] == pSrcStr[k] || k == -1)
        {
#if 0
            //此获取next数组的方法在ABCABCD的模式串是，若ABCABC匹配到第二个C时不匹配，则不需要再回溯到ABC
            ++j;
            ++k;
            pNextArray[j] = k;
#else
            ++j;
            ++k;
            if(pSrcStr[j] != pSrcStr[k])
            {
                pNextArray[j] = k;
            }
            else
            {
                pNextArray[j] = pNextArray[k];
            }
#endif
        }
        else
        {
            k = pNextArray[k];
        }
    }
    return pNextArray;
}
