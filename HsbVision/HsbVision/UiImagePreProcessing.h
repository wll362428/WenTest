#pragma once
#include "UiToolBase.h"

// CImagePreProcessing

class CUiImagePreProcessing : public CUiToolBase
{
	DECLARE_DYNAMIC(CUiImagePreProcessing)

public:
	CUiImagePreProcessing();
	virtual ~CUiImagePreProcessing();

public:
	virtual void InitLayers();
// 	virtual BOOL RunOnce();
// 	virtual CString  Save();
	virtual void PreSubclassWindow();
	afx_msg void OnButtonFunc(UINT nID);

protected:
	DECLARE_MESSAGE_MAP()


private:
	CImagePreProcessing *m_ImaePreProcess;

	CButton  *m_Btn[7];
	BOOL  m_bIsCheck[7];
};


