#pragma once
#include "UiToolBase.h"

// CUiBlobIns




class CUiBlobIns : public CUiToolBase
{
	DECLARE_DYNAMIC(CUiBlobIns)

public:
// 	CUiBlobIns();
	CUiBlobIns(LPCTSTR  lpToolName="",CWnd *Parent =NULL);
	virtual ~CUiBlobIns();

protected:
	DECLARE_MESSAGE_MAP()
public:
//	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
//	virtual BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, LPVOID lpParam = NULL);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

public:
	virtual void InitLayers();
	virtual BOOL RunOnce();
	virtual CString  Save();
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT   lpDIS);

private:
	CWnd *m_parent;
	CSliderCtrl *m_pSliderMinGray;
	CSliderCtrl *m_pSliderMaxGray;

public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	afx_msg void OnButtonFunc(UINT nID);


	afx_msg void OnSize(UINT nType, int cx, int cy);
};


