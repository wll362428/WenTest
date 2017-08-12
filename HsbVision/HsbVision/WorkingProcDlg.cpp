// WorkingProcDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HsbVision.h"
#include "WorkingProcDlg.h"
#include "afxdialogex.h"
#include "UiToolBase.h"

// CWorkingProcDlg dialog

const  TCHAR *ss[] = {_T("序号"), _T("名称"),_T("位置"), _T("相机"),_T("光源"), _T("算法"), _T("预处理"),_T("属性")};

// CWorkingDlg dialog


IMPLEMENT_DYNAMIC(CWorkingProcDlg, CDialogEx)

CWorkingProcDlg::CWorkingProcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWorkingProcDlg::IDD, pParent)
{

}

CWorkingProcDlg::~CWorkingProcDlg()
{
}

void CWorkingProcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
// 	DDX_Control(pDX, IDC_LIST_WORKING_PROC, m_ListWorkingProc);
}


BEGIN_MESSAGE_MAP(CWorkingProcDlg, CDialogEx)
// 	ON_MESSAGE()
	ON_REGISTERED_MESSAGE(WM_UPDATE_WORKLIST_MSG, OnAddData)
END_MESSAGE_MAP()


// CWorkingProcDlg message handlers
BOOL  CWorkingProcDlg::OnInitDialog()
{
	SetWindowText(_T("流程控制"));
	MoveWindow(g_nCXScreen -450,g_nCYMenu+g_nCYTitle+g_nCYToolBar,450, g_nCYClient-440);


	m_ListWorkingProc =  ((CListCtrl *)GetDlgItem(IDC_LIST_WORKING_PROC));
	m_ListWorkingProc->MoveWindow(1,0,440,g_nCYClient-470);
	DWORD ExStyle1 = m_ListWorkingProc->GetExtendedStyle();
	 ((CListCtrl *)GetDlgItem(IDC_LIST_WORKING_PROC))->SetExtendedStyle( ExStyle1|LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES|LVS_EX_GRIDLINES );//LVS_EX_FULLROWSELECT|
	const  TCHAR *ss[] = {_T("序号"), _T("名称"),_T("位置"), _T("相机"),_T("光源"), _T("算法"), _T("预处理"),_T("属性")};
	for (int i = 0; i<sizeof(ss)/sizeof(ss[0]);i++)
	{
		m_ListWorkingProc->InsertColumn(i, ss[i], 0, 80);
	}

// 	m_ListWorkingProc->InsertItem(0,"0");
// 	m_ListWorkingProc->InsertItem(0,"1");
// 
// 	m_ListWorkingProc->SetItemText(0,1,"111r");
// 	m_ListWorkingProc->SetItemText(0,2,"111ee");
// 	m_ListWorkingProc->SetItemText(0,3,"11ee1");
// 	m_ListWorkingProc->SetItemText(0,4,"11221");
// 	m_ListWorkingProc->SetItemText(0,5,"1111111111");

	return TRUE;
}

LRESULT  CWorkingProcDlg::OnAddData(WPARAM wParam, LPARAM lParam)
{
	this->ShowWindow(SW_SHOWNORMAL);


// 	newWorkFile.szName


	return 0;
}

LRESULT CWorkingProcDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	switch(message)
	{
	case WM_COPYDATA:
		{
			this->ShowWindow(SW_SHOWNORMAL);
			int nCount  = m_ListWorkingProc->GetItemCount();
			_HSB_WORK_FILE   newWorkFile;
			newWorkFile.szId = int2String(nCount);

// 			newWorkFile.szName = 

		}
		break;
	}
	return CDialogEx::WindowProc(message, wParam, lParam);
}
