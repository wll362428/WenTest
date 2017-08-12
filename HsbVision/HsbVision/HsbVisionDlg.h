
// HsbVisionDlg.h : header file
//
#include "BtnST.h"
#include "WinXPButtonST.h"
#include "BCMenu.h"
#include "CKBaseDef.h"
#include "GraphWindow.h"
#include "..\\HVisionDll\\ShapeMatch.h"
#pragma once
using namespace CKVision;

// CHsbVisionDlg dialog
class CHsbVisionDlg : public CDialogEx
{
// Construction
public:
	CHsbVisionDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_HSBVISION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
// 	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
// 	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
// 	afx_msg void OnNewFile();
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileDelete();
	afx_msg void OnTools();
	afx_msg void OnAbout();
	afx_msg void OnExit();
	afx_msg void OnSelRec1();
	afx_msg void OnSelRec2();
	afx_msg void OnSelCir();
	afx_msg void OnSelUser();
	afx_msg void OnSelCancel();


public:
	 void OnF2();

public:
	static  CHsbVisionDlg *GetDlgInstance(){static  CHsbVisionDlg * pdlg = new  CHsbVisionDlg; return  pdlg;}

	CButtonST* NewMyButton(int nID,LPCTSTR lpCaption,CRect rect,int nStyle);
	CFont*  NewMyFont(int nHeight,int nWidth, LPCTSTR  lpszFaceName=_T("微软雅黑"));
	BOOL InitUiLayers();
	BOOL OnCreateDialog(UINT  nIDTemplate,CWnd* pParentWnd);

public:
	CDialog *m_pWorkProcDlg;

private:
	CButtonST  m_btnInterModel;//ROI集合方式
	CButtonST  m_btnSet;
	CButtonST  m_btnData;
	CButtonST  m_btnHelp;
	CDialog  *m_pToolsDlg;
	CDialog  *m_pFixModelDlg;
	CStatusBar   m_wndStatusBar; 

// 	CShapeMatch *pShape;

	CComboBox  m_comCamerbox;
	CFont  m_toolbarFont;
	IPNT ipntxy;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
//	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonRoiInterModel();
	afx_msg void OnClose();
	CGraphWindow m_grapWindow;
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
