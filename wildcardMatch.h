#pragma once
class wildcardMatch
{
public:
	wildcardMatch();
	~wildcardMatch();
	void startSearch();
	bool strMatch(const char* pSrc, const char* pPattern);
	int checkNextWildcardPos(const char* pStr);
	int kmpMatch(const char* pSrc, const char* pPattern);
};

