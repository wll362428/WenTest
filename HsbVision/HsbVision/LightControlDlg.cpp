// ToolsDlg.cpp : implementation file

#include "stdafx.h"
#include "HsbVision.h"
#include "LightControlDlg.h"
// CLightControlDlg dialog

IMPLEMENT_DYNAMIC(CLightControlDlg, CDialogEx)

CLightControlDlg::CLightControlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLightControlDlg::IDD, pParent)
{
}

CLightControlDlg::~CLightControlDlg()
{
}

void CLightControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COM_PORT1, m_comPort1);
	DDX_Control(pDX, IDC_COM_BAUD1, m_comBaud1);
	DDX_Control(pDX, IDC_COM_PORT2, m_comPort2);
	DDX_Control(pDX, IDC_COM_BAUD2, m_comBaud2);
	DDX_Control(pDX, IDC_COM_PORT3, m_comPort3);
	DDX_Control(pDX, IDC_COM_BAUD3, m_comBaud3);

	DDX_Control(pDX, IDC_SLIDER_L11, m_SliderLight1);
	DDX_Control(pDX, IDC_SLIDER_L12, m_SliderLight2);
	DDX_Control(pDX, IDC_SLIDER_L13, m_SliderLight3);
	DDX_Control(pDX, IDC_SLIDER_L14, m_SliderLight4);
	DDX_Control(pDX, IDC_SLIDER_L21, m_SliderLight5);
	DDX_Control(pDX, IDC_SLIDER_L22, m_SliderLight6);
	DDX_Control(pDX, IDC_SLIDER_L23, m_SliderLight7);
	DDX_Control(pDX, IDC_SLIDER_L24, m_SliderLight8);
	DDX_Control(pDX, IDC_SLIDER_L31, m_SliderLight9);
	DDX_Control(pDX, IDC_SLIDER_L32, m_SliderLight10);
	DDX_Control(pDX, IDC_SLIDER_L33, m_SliderLight11);
	DDX_Control(pDX, IDC_SLIDER_L34, m_SliderLight12);

}


BEGIN_MESSAGE_MAP(CLightControlDlg, CDialogEx)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_HSCROLL()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_OPEN_LIGHT, &CLightControlDlg::OnBnClickedBtnOpenLight)
END_MESSAGE_MAP()


// CLightControlDlg message handlers


BOOL CLightControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetWindowText(_T("光源控制"));
	// TODO:  Add extra initialization here
/////////////////////////光源配置  最多只支持3路共12条光源///////////////////////////////////
	m_nSize = g_LightInfo.size();
	if (m_nSize >3)		m_nSize=3;

	m_SliderLight1.SetRange(0,255);
	m_SliderLight2.SetRange(0,255);
	m_SliderLight3.SetRange(0,255);
	m_SliderLight4.SetRange(0,255);
	m_SliderLight5.SetRange(0,255);
	m_SliderLight6.SetRange(0,255);
	m_SliderLight7.SetRange(0,255);
	m_SliderLight8.SetRange(0,255);
	m_SliderLight9.SetRange(0,255);
	m_SliderLight10.SetRange(0,255);
	m_SliderLight11.SetRange(0,255);
	m_SliderLight12.SetRange(0,255);

	for (int i = 1; i<=8; i++)
	{
		CHAR   wszCom[11] = {0};
		sprintf(wszCom, _T("COM%d"),i);
		m_comPort1.AddString(wszCom);
		m_comPort2.AddString(wszCom);
		m_comPort3.AddString(wszCom);
	}

	const  TCHAR  *tbuf[] ={_T("9600"),_T("19200"),_T("38400") };
	for( int i =0; i< sizeof(tbuf)/sizeof(tbuf[0]);i++)
	{
		m_comBaud1.AddString(tbuf[i]);
		m_comBaud2.AddString(tbuf[i]);
		m_comBaud3.AddString(tbuf[i]);
	}

	InitUILayers();



	return TRUE;  // return TRUE unless you set the focus to a control
}

void CLightControlDlg::InitUILayers()
{
	int cx = GetSystemMetrics(SM_CXFULLSCREEN);
	int cy = GetSystemMetrics(SM_CYFULLSCREEN);

	int   cx1   =   GetSystemMetrics(   SM_CXSCREEN   );
	int   cy2   =   GetSystemMetrics(   SM_CYSCREEN   );
	int m_nSize = g_LightInfo.size();
	m_nSize =0;
	int nDlgW = 100;
	int nDlgH = 1000;
	if (0 == m_nSize)
	{
		MoveWindow(g_nCXScreen-600, 110,320,100);
		for (int i = IDC_STATIC_TXT1; i<=IDC_STATIC_TXT12;i++ )
		{
			GetDlgItem(i)->ShowWindow(SW_HIDE);
		}
		GetDlgItem(IDC_BTN_OPEN_LIGHT)->ShowWindow(SW_HIDE);
		SetTimer(1,5,NULL);
// 		CClientDC dc(this);
	}
	else if (1 == m_nSize)
	{
		MoveWindow(g_nCXScreen-720, 110,430,270);
		GetDlgItem(IDC_BTN_LIGHT_SAVE)->MoveWindow(100, 170,80,30);
		GetDlgItem(IDC_BTN_LIGHT_QUIT)->MoveWindow(250, 170,80,30);

		for (int i = IDC_STATIC_TXT1; i<=IDC_STATIC_TXT12;i++ )
		{
			if (i<IDC_STATIC_TXT1+16)
			{
				GetDlgItem(i)->ShowWindow(SW_SHOW);
			}
			else
			{
				GetDlgItem(i)->ShowWindow(SW_HIDE);
			}
		}

		m_comPort1.SetCurSel(g_LightInfo[0].ncom-1);
		m_comBaud1.SetCurSel(0);
	}
	else if (2 == m_nSize)
	{
		MoveWindow(g_nCXScreen-720, 110,450,400);
		GetDlgItem(IDC_BTN_LIGHT_SAVE)->MoveWindow(100, 300,80,30);
		GetDlgItem(IDC_BTN_LIGHT_QUIT)->MoveWindow(250, 300,80,30);

		for (int i = IDC_STATIC_TXT1; i<=IDC_STATIC_TXT12;i++ )
		{
			if (i<IDC_STATIC_TXT1+32)
			{
				GetDlgItem(i)->ShowWindow(SW_SHOW);
			}
			else
			{
				GetDlgItem(i)->ShowWindow(SW_HIDE);
			}
		}

		m_comPort1.SetCurSel(g_LightInfo[0].ncom-1);
		m_comBaud1.SetCurSel(0);
		m_comPort2.SetCurSel(g_LightInfo[1].ncom-1);
		m_comBaud2.SetCurSel(1);
	}

	else if (3 == m_nSize)
	{
		MoveWindow(g_nCXScreen-720,110,400,560);
		GetDlgItem(IDC_BTN_LIGHT_SAVE)->MoveWindow(100, 450,80,30);
		GetDlgItem(IDC_BTN_LIGHT_QUIT)->MoveWindow(250, 450,80,30);

		m_comPort1.SetCurSel(g_LightInfo[0].ncom-1);
		m_comBaud1.SetCurSel(0);
		m_comPort2.SetCurSel(g_LightInfo[1].ncom-1);
		m_comBaud2.SetCurSel(1);
		m_comPort3.SetCurSel(g_LightInfo[2].ncom-1);
		m_comBaud3.SetCurSel(1);

	}
}

void CLightControlDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (1 == nIDEvent)
	{
// 		KillTimer( 1);
		m_nSize =0;
		if (0 == m_nSize)
		{
			CDC *dc=GetDC();

			CFont font;
			font.CreateFont(20,10,0,0,FW_THIN,false,false,false,
				CHINESEBIG5_CHARSET,OUT_CHARACTER_PRECIS,
				CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
				FF_MODERN, _T("微软雅黑"));
			int nbk = dc->SetBkMode(TRANSPARENT);
			COLORREF  ncolor =  dc->SetTextColor(RGB(251,51,51));
			CFont *pfont =dc->SelectObject(&font);

			CString  str = _T("没有找到光源或线路连接有问题");
			CRect rt(10,20,400,100);
			dc->DrawText(str, str.GetLength(), &rt, DT_LEFT|DT_SINGLELINE);
			dc->SetBkMode(nbk);
			dc->SetTextColor(ncolor);
			dc->SelectObject(&pfont);
			ReleaseDC(dc);
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CLightControlDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
// 	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);  
// 	CHsbVisionView* pView = (CHsbVisionView*)pFrame->GetActiveView();
// 	pView->OnDeleteDialog(this);
	CDialogEx::OnClose();
}


void CLightControlDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	switch(pScrollBar->GetDlgCtrlID())
	{
	case IDC_SLIDER_L11:
		SetDlgItemInt(IDC_STATIC_TXT1,m_SliderLight1.GetPos());
		break;
	case IDC_SLIDER_L12:
		SetDlgItemInt(IDC_STATIC_TXT2,m_SliderLight2.GetPos());
		break;
	case IDC_SLIDER_L13:
		SetDlgItemInt(IDC_STATIC_TXT3,m_SliderLight3.GetPos());
		break;
	case IDC_SLIDER_L14:
		SetDlgItemInt(IDC_STATIC_TXT4,m_SliderLight4.GetPos());
		break;
	case IDC_SLIDER_L21:
		SetDlgItemInt(IDC_STATIC_TXT5,m_SliderLight5.GetPos());
		break;
	case IDC_SLIDER_L22:
		SetDlgItemInt(IDC_STATIC_TXT6,m_SliderLight6.GetPos());
		break;
	case IDC_SLIDER_L23:
		SetDlgItemInt(IDC_STATIC_TXT7,m_SliderLight7.GetPos());
		break;
	case IDC_SLIDER_L24:
		SetDlgItemInt(IDC_STATIC_TXT8,m_SliderLight8.GetPos());
		break;
	case IDC_SLIDER_L31:
		SetDlgItemInt(IDC_STATIC_TXT9,m_SliderLight9.GetPos());
		break;
	case IDC_SLIDER_L32:
		SetDlgItemInt(IDC_STATIC_TXT10,m_SliderLight10.GetPos());
		break;
	case IDC_SLIDER_L33:
		SetDlgItemInt(IDC_STATIC_TXT11,m_SliderLight11.GetPos());
		break;
	case IDC_SLIDER_L34:
		SetDlgItemInt(IDC_STATIC_TXT12,m_SliderLight12.GetPos());
		break;

	}
		CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


HBRUSH CLightControlDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
// 	if (CTLCOLOR_STATIC == nCtlColor)
// 	{
// 		if ( IDC_STATIC_TXT1 == pWnd->GetDlgCtrlID())
// 		{
// 
// 		}
// 	}

	return hbr;
}


void CLightControlDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CDialogEx::OnPaint();

}


void CLightControlDlg::OnBnClickedBtnOpenLight()
{
	
}
