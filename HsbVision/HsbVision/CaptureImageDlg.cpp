// ToolsDlg.cpp : implementation file

#include "stdafx.h"
#include "HsbVision.h"
#include "CaptureImageDlg.h"
#include "HsbVisionDlg.h"
// CcaptureImageDlg dialog

IMPLEMENT_DYNAMIC(CcaptureImageDlg, CDialogEx)

CcaptureImageDlg::CcaptureImageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CcaptureImageDlg::IDD, pParent)
{
}

CcaptureImageDlg::~CcaptureImageDlg()
{
}

void CcaptureImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CAMER_LIST, m_comBoxCamerList);
}


BEGIN_MESSAGE_MAP(CcaptureImageDlg, CDialogEx)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CcaptureImageDlg message handlers
#define  ID_BTN_CAMERA_SET   11011
#define  ID_BTN_CAPTURE_ALLTIME   11012
#define  ID_BTN_CAPTURE_ONE   11013
#define  ID_BTN_CAPTURE_USEMODEL   11014

BOOL CcaptureImageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetWindowText(_T("相机工具"));
	// TODO:  Add extra initialization here
	int cx = GetSystemMetrics(SM_CXFULLSCREEN);
	int cy = GetSystemMetrics(SM_CYFULLSCREEN);

	int   cx1   =   GetSystemMetrics(   SM_CXSCREEN   );
	int   cy2   =   GetSystemMetrics(   SM_CYSCREEN   );
	MoveWindow(cx-900, cy2-cy+30,288,102);

	CRect  rt;
	rt.top = 22;
	rt.bottom = rt.top + 55;
	for (int i = 0; i<4; i++)
	{
		rt.left = 70*i+1;
		rt.right = rt.left+ 70;

		m_btnCapture[i].SubclassDlgItem(IDC_BUTTON_CAPTRUE_SET+i,this);
		m_btnCapture[i].MoveWindow(&rt);
		m_btnCapture[i].SetIcon(IDI_ICON_CAMER_SET+i);
		m_btnCapture[i].SetFontEx(g_cFont[1]);
		m_btnCapture[i].SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnCapture[i].DrawTransparent();
		m_btnCapture[i].DrawFlatFocus(TRUE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CcaptureImageDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CDialogEx::OnTimer(nIDEvent);
}

void CcaptureImageDlg::OnClose()
{
	CDialogEx::OnClose();
}

void CcaptureImageDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
}
