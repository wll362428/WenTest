#pragma once
#include "UiToolBase.h"

#define  UI_LAYERS_COUNT  10 
// CUiShapemode
class CUiShapemode : public CUiToolBase
{
	DECLARE_DYNAMIC(CUiShapemode)

public:
	CUiShapemode(LPCTSTR  lpToolName="",CWnd *Parent =NULL);
	virtual ~CUiShapemode();

protected:
	DECLARE_MESSAGE_MAP()
public:
//	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
//	virtual BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, LPVOID lpParam = NULL);
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

public:
	virtual void InitLayers();
	virtual BOOL RunOnce();
	virtual CString  Save();
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT   lpDIS);

private:
	CWnd *m_parent;
// 	CSliderCtrl  *m_pSlider[4];
// 	CComboBox *m_pCombobox[2];
	CWnd *m_pLayers[UI_LAYERS_COUNT];
public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	afx_msg void OnButtonFunc(UINT nID);

//	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
//	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);

private:
	CShapeMatch *m_pShape;//

};


