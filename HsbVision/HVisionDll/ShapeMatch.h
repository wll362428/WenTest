#pragma once
 #include "CHVision.h"

// #define TEST_API __declspec(dllexport)
// #else
// #define TEST_API __declspec(dllimport)
// #endif

class  H_DLL_EXPORT CShapeMatch :public CHVisionTool
{
public:
	CShapeMatch(void);
	virtual ~CShapeMatch(void);
public:
	void OnSetMincontrast(HTuple hLow, HTuple hHigh, HTuple hMod);

	HTuple CreateShape(HTuple hLow, HTuple hHigh, HTuple hMod);
	BOOL  Run(HTuple hModelId, HTuple hScore=0.35, HTuple hName=HTuple(""), bool bReverse=false);
	BOOL OnSave(HTuple hPath);
private:
static  HTuple  m_hvmodelID;

};

