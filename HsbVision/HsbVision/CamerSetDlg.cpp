// ToolsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HsbVision.h"
#include "CamerSetDlg.h"
#include "MainFrm.h"
#include "HsbVisionDoc.h"
#include "HsbVisionView.h"
// CCamerSetDlg dialog

IMPLEMENT_DYNAMIC(CCamerSetDlg, CDialogEx)

CCamerSetDlg::CCamerSetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCamerSetDlg::IDD, pParent)
{
}

CCamerSetDlg::~CCamerSetDlg()
{
}

void CCamerSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCamerSetDlg, CDialogEx)
	ON_WM_TIMER()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CCamerSetDlg message handlers


BOOL CCamerSetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetWindowText(_T("Ïà»úÉèÖÃ"));
	// TODO:  Add extra initialization here
	int cx = GetSystemMetrics(SM_CXFULLSCREEN);
	int cy = GetSystemMetrics(SM_CYFULLSCREEN);

	int   cx1   =   GetSystemMetrics(   SM_CXSCREEN   );
	int   cy2   =   GetSystemMetrics(   SM_CYSCREEN   );
	MoveWindow(cx-600, cy2-cy+30,300,300);
// 	GetDlgItem(IDC_EDIT_ZENGYI)->ShowWindow(SW_SHOW);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CCamerSetDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnTimer(nIDEvent);
}


void CCamerSetDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);  
	CHsbVisionView* pView = (CHsbVisionView*)pFrame->GetActiveView();
// 	pView->OnDeleteDialog(this);
	CDialogEx::OnClose();
}
