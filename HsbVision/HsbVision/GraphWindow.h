#pragma once
#include "BtnST.h"


#define  BTN_GRAPHWINDOW  11000
#define  WM_UPDATE_STATUSBAR_MSG   0x4009

class CGraphWindow : public CStatic
{
	DECLARE_DYNAMIC(CGraphWindow)

public:
	CGraphWindow();
	virtual ~CGraphWindow();

	virtual void PreSubclassWindow() ;
	virtual void DrawItem(LPDRAWITEMSTRUCT );
	virtual BOOL OnInitDialog();
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual int OnCreate(LPCREATESTRUCT lpCreateStruct);

private:
	CButtonST* NewMyButton(char*   lpszCaption,int nID,CRect rect,int nStyle);

	afx_msg void OnButtonFunc(UINT nID);
	afx_msg void OnRightClickMenu(UINT nID);

// 	void  SetImage(HObject hImage);

// 	void OnShowImage();

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);

private:
// 	CHVisionWindow  *CHVisionWindow::GetInstance();
	CRect  m_rtImage;
	bool m_bLeftBtnDown;
	bool m_bDrawRegion;

public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

