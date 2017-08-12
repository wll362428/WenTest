// PropertyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HsbVision.h"
#include "PropertyDlg.h"
#include "afxdialogex.h"
#include "UiShapemode.h"

#define  BTN_RUN_ONCE  0x8000
#define  BTN_SAVE_DATA  0x8001
// CPropertyDlg dialog

typedef    unsigned int  MYINT ;
IMPLEMENT_DYNAMIC(CPropertyDlg, CDialogEx)

CPropertyDlg::CPropertyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPropertyDlg::IDD, pParent)
{

}

CPropertyDlg::CPropertyDlg(LPCTSTR  lpItemText)
{
	m_strToolName = CString(lpItemText);
	m_pUiTool = NULL;
}

CPropertyDlg::~CPropertyDlg()
{
}

void CPropertyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
// 	DDX_Control(pDX, IDC_STATIC_SHAPEMODEL, m_uiShape);
// 	DDX_Control(pDX, IDC_STATIC_BLOB, m_uiBlob);
// 	DDX_Control(pDX, IDC_STATIC_IMAGE_PRE, m_uiPreImage);
}


BEGIN_MESSAGE_MAP(CPropertyDlg, CDialogEx)
	ON_WM_TIMER()

ON_COMMAND(BTN_RUN_ONCE,OnBnClickedButtonRun)
ON_COMMAND(BTN_SAVE_DATA,OnBnClickedButtonSave)

END_MESSAGE_MAP()


void CPropertyDlg::SetToolAttr(LPCTSTR  lpItemName)
{
	if (NULL != m_pUiTool)
	{
		delete m_pUiTool;
		m_pUiTool=NULL;
	}

	if (CString("图像定位") == CString(lpItemName))
	{
// 		m_uiShape.ShowWindow(SW_SHOW);
// 		m_uiBlob.ShowWindow(SW_HIDE);
// 		m_uiPreImage.ShowWindow(SW_HIDE);

 		m_pUiTool = new CUiShapemode();

// 		m_pUiTool = (CUiShapemode *)GetDlgItem(IDC_STATIC_SHAPEMODEL);
	}
	else if (  CString("斑点分析") == CString(lpItemName) )
	{
// 		m_uiShape.ShowWindow(SW_HIDE);
// 		m_uiBlob.ShowWindow(SW_SHOW);
// 		m_uiPreImage.ShowWindow(SW_HIDE);
		m_pUiTool = new CUiBlobIns();
	}
	else if (  CString("彩色转灰") == CString(lpItemName) )
	{
// 		m_uiShape.ShowWindow(SW_HIDE);
// 		m_uiBlob.ShowWindow(SW_HIDE);
// 		m_uiPreImage.ShowWindow(SW_SHOW);
		m_pUiTool = new  CUiImagePreProcessing();
	}

	CRect rect(0,0,225,270);
	m_pUiTool->Create("", WS_CHILD|WS_VISIBLE, rect, this);
	m_pUiTool->MoveWindow(&rect);
}

BOOL CPropertyDlg::OnInitDialog()
 {
	 CDialogEx::OnInitDialog();

	 SetWindowText("属性");
	 MoveWindow(g_nCXScreen - 225,g_nCYTitle + g_nCYMenu + g_nCYToolBar+320, 225,420);

	CFont  *pfont= NewFont();


	NewStatic("模板名称",0, CRect(20,270,80,300), this, 0)->SetFont(pfont);
	NewComboBox(CBS_DROPDOWN, CRect(85,265,215,395), this, 0)->SetFont(pfont);

	NewButton("处理一次", BS_PUSHBUTTON,CRect (20,300,100,330),this,BTN_RUN_ONCE )->SetFont(pfont);
	NewButton("保存", BS_PUSHBUTTON,CRect (120,300,200,330),this,BTN_SAVE_DATA)->SetFont(pfont);

	 return  TRUE;
 }

void CPropertyDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	if (1 == nIDEvent)
	{
		KillTimer(1);
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CPropertyDlg::OnBnClickedButtonRun()
{
	m_pUiTool->RunOnce();
}


void CPropertyDlg::OnBnClickedButtonSave()
{
	CString  strData = m_pUiTool->Save();

	COPYDATASTRUCT cds = {0};
	cds.lpData = strData.GetBuffer();
	cds.cbData = strData.GetLength();

	HWND receiveWindow = ::FindWindow(NULL, "流程控制");  
	if (NULL == receiveWindow  )  
		return; 

	::SendMessage(receiveWindow, WM_COPYDATA,(WPARAM)GetSafeHwnd(),(LPARAM)&cds);
	strData.ReleaseBuffer();
}
