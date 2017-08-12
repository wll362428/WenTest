// StartUpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HsbVision.h"
#include "StartUpDlg.h"
#include "afxdialogex.h"
#include "HsbVisionDlg.h"

// CStartUpDlg dialog

IMPLEMENT_DYNAMIC(CStartUpDlg, CDialogEx)

CStartUpDlg::CStartUpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStartUpDlg::IDD, pParent)
{

}

CStartUpDlg::~CStartUpDlg()
{
}

void CStartUpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CStartUpDlg, CDialogEx)
	ON_BN_CLICKED(ID_BUTTON_OK, &CStartUpDlg::OnBnClickedButtonOk)
END_MESSAGE_MAP()


// CStartUpDlg message handlers
void CStartUpDlg::OnBnClickedButtonOk()
{
	 	CHsbVisionDlg dlg;
// 	 	m_pMainWnd = &dlg;
		INT_PTR nResponse = dlg.DoModal();
// 		EndDialog(0);
}

void  CStartUpDlg::CloseDialog()
{
	EndDialog(0);
	
}


LRESULT CStartUpDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	if (WM_HSB_CLOSE_LOGIN == message)
	{
		EndDialog(0);
	}
	
	return CDialogEx::WindowProc(message, wParam, lParam);
}
