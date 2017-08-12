#pragma once
 #include "CHVision.h"

// #define TEST_API __declspec(dllexport)
// #else
// #define TEST_API __declspec(dllimport)
// #endif

class  H_DLL_EXPORT CBlobIns :public CHVisionTool
{
public:
	CBlobIns(void);
	virtual ~CBlobIns(void);
public:
	void OnThreshold(HTuple MinGray, HTuple MaxGray,HTuple minArea=0);
};

