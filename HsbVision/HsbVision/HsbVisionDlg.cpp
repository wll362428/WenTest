
// HsbVisionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HsbVision.h"
#include "HsbVisionDlg.h"
#include "ToolsDlg.h"
#include "CaptureImageDlg.h"
#include "WorkingProcDlg.h"
#include "afxdialogex.h"
#include "Config.h"

/*#include "halconlib.h"*/
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// #pragma comment(lib, "HsbLib.lib")
#define  ID_BTN_FILE              9996
#define  ID_BTN_SET               9997
#define  ID_BTN_DATA             9998
#define  ID_BTN_HELP             9999

#define  ID_BTN_FILE_NEW		10000
#define  ID_BTN_FILE_OPEN		10001
#define  ID_BTN_FILE_SAVE		10002
#define  ID_BTN_FILE_DELETE	10003
#define  ID_BTN_TOOLS            10004
#define  ID_BTN_PARA_SET       10005
#define  ID_BTN_RUN               10006
#define  ID_BTN_STOP_RUN      10007
#define  ID_BTN_EXIT               10008

#define  ID_BTN_SEL_REC1            10009
#define  ID_BTN_SEL_REC2            10010
#define  ID_BTN_SEL_CIR               10011
#define  ID_BTN_SEL_USER             10012
#define  ID_BTN_SEL_CANCEL             10013


// CAboutDlg dialog used for App About
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHsbVisionDlg dialog



CHsbVisionDlg::CHsbVisionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHsbVisionDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pToolsDlg =m_pCaptureDlg = m_pFixModelDlg = NULL;
}

void CHsbVisionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_IMAGE, m_grapWindow);
}

BEGIN_MESSAGE_MAP(CHsbVisionDlg, CDialogEx)
// 	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
// 	ON_WM_QUERYDRAGICON()
//	ON_WM_NCCALCSIZE()
	ON_BN_CLICKED(ID_BTN_TOOLS, OnTools)
	ON_BN_CLICKED(ID_BTN_FILE_NEW, OnFileNew)
	ON_BN_CLICKED(ID_BTN_FILE_OPEN, OnFileOpen)
	ON_BN_CLICKED(ID_BTN_FILE_SAVE, OnFileSave)
	ON_BN_CLICKED(ID_BTN_FILE_DELETE, OnFileDelete)
	ON_BN_CLICKED(ID_BTN_HELP, OnAbout)
	ON_BN_CLICKED(ID_BTN_EXIT, OnExit)
	ON_BN_CLICKED(ID_BTN_SEL_REC1, OnSelRec1)
	ON_BN_CLICKED(ID_BTN_SEL_REC2, OnSelRec2)
	ON_BN_CLICKED(ID_BTN_SEL_CIR, OnSelCir)
	ON_BN_CLICKED(ID_BTN_SEL_USER, OnSelUser)
	ON_BN_CLICKED(ID_BTN_SEL_CANCEL, OnSelCancel)

// 	ON_COMMAND(ID_F2, &CHsbVisionDlg::OnF2)

	ON_WM_NCLBUTTONDOWN()
	ON_WM_TIMER()
//	ON_WM_MOUSEWHEEL()
//	ON_WM_MBUTTONDOWN()
//	ON_WM_MBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_ROI_INTER_MODEL, &CHsbVisionDlg::OnBnClickedButtonRoiInterModel)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


CGraphWindow  *m_grah;
// CHsbVisionDlg message handlerss
BOOL CHsbVisionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	Config::LoadConfigFile();
	g_cFont[0] = NewMyFont(19,10);
	g_cFont[1] = NewMyFont(22,6);
	g_cFont[2] = NewMyFont(20,6);
	g_cFont[3] = NewMyFont(19,10);

///////////////////////获取屏幕相关参数///////////////////////////////////////////////////
	g_nCXScreen   =   GetSystemMetrics(   SM_CXSCREEN   );
	g_nCYScreen   =   GetSystemMetrics(   SM_CYSCREEN   );
	g_nCYTitle = GetSystemMetrics(SM_CYCAPTION)+1;
	g_nCYMenu =GetSystemMetrics(SM_CYMENU)+1;

	CRect  rt,rtTastBar;
	::GetWindowRect(::FindWindow(_T("Shell_TrayWNd"),   NULL),   &rtTastBar);//任务栏
	rt.left = -1;
	rt.right = g_nCXScreen;
	rt.top = 0;
	rt.bottom = rtTastBar.top-1;

	MoveWindow(&rt);
// 	ShowWindow(SW_SHOWMAXIMIZED);

/////////////////////////////////添加菜单栏/////////////////////////////////////////////////////////////////////

	CMenu *pMenu=new CMenu() ; 
	pMenu->LoadMenu(IDR_MENU1);
	SetMenu(pMenu);

/////////////////////////////添加状态栏/////////////////////////////////////////////////////////////////////
	CRect rect;  
	GetClientRect(rect);
	static UINT indicators[]={IDS_STRING_CLIENT_CAPTION, IDS_STRING_VALUE, IDS_STRING_COORDINATA, IDS_STRING_GRAYVAL,IDS_STRING_VERSION};

	if( !m_wndStatusBar.Create(this)|| !m_wndStatusBar.SetIndicators(indicators,sizeof(indicators)/sizeof(UINT)) )  
	{
		TRACE0("Can't create status bar\n");
		return FALSE;
	}

	//添加状态栏信息  
	m_wndStatusBar.MoveWindow(1,rect.bottom-20,rect.right,20);// 调整状态栏的位置和大小  
	int index = m_wndStatusBar.CommandToIndex(IDS_STRING_CLIENT_CAPTION);
	m_wndStatusBar.SetPaneInfo(0,IDS_STRING_CLIENT_CAPTION,SBPS_NORMAL,100);
	m_wndStatusBar.SetPaneInfo(1,IDS_STRING_VALUE,SBPS_NORMAL,500);
	m_wndStatusBar.SetPaneInfo(2,IDS_STRING_COORDINATA,SBPS_NORMAL,200);
	m_wndStatusBar.SetPaneInfo(3,IDS_STRING_GRAYVAL,SBPS_NORMAL,200);
	m_wndStatusBar.SetPaneInfo(4,IDS_STRING_VERSION,SBPS_NORMAL,200);

 	SetTimer(1,1,NULL);
	InitUiLayers();
	((CListCtrl *)GetDlgItem(IDC_LIST_WORKING_PROCESS))->ShowWindow(SW_HIDE);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	m_wndStatusBar.GetClientRect(&rt);
	g_nCYClient =  g_nCYScreen -g_nCYTitle -  g_nCYMenu - g_nCYToolBar - rtTastBar.Height()- rt.Height()-5;

	m_grapWindow.MoveWindow(200,g_nCYToolBar+2, g_nCXScreen-430, g_nCYClient);
	

// 	pShape= new CShapeMatch();

	SetTimer(1001,50,NULL);
// //////////////////////////////////////////////////////////////////////////////
	return TRUE;  // return TRUE  unless you set the focus to a control
}

#define  BTN_MENU_HEIGHT 22
#define  BTN_MENU_WIDTH 80
#define  BTN_TOOL_HEIGHT 55
#define  BTN_TOOL_WIDTH  63
#define  IDC_COMBOX  11111

#define   ID_NEW_FILE1  32784

BOOL CHsbVisionDlg::InitUiLayers()
{
	//**************************初始化菜单栏*************************************//
// 	BeginTime();
// 	const  TCHAR  *szCaptionMenu[] = {_T("文件(F)"),_T("设置(S)"),_T("数据(F)"),_T("帮助(H)")};
// 	int nlen = sizeof(szCaptionMenu)/sizeof(szCaptionMenu[0]);
// 
// 	CButtonST **p_btMenu;
// 	p_btMenu = new CButtonST *();
	CRect rt;
// 	rt.top = 0;
// 	rt.bottom = rt.top+g_nCYTitle;
// 	for (int i =0; i < sizeof(szCaptionMenu)/sizeof(szCaptionMenu[0]); i++)
// 	{
// 		rt.left = BTN_MENU_WIDTH*i+1;
// 		rt.right = rt.left+ BTN_MENU_WIDTH;
// 		p_btMenu[i] =NewMyButton(ID_BTN_FILE+i, szCaptionMenu[i], rt,BS_DEFPUSHBUTTON);
// 		p_btMenu[i]->DrawTransparent();
// 	}
// 	p_btMenu[0]->SetMenu(IDR_MENU_FILE, m_hWnd);
// 	p_btMenu[1]->SetMenu(IDR_MENU_SET, m_hWnd);
	//***************************初始化工具栏*************************************************//
	CWinXPButtonST *p_btTools[10];
// 	p_btTools = new CButtonST*();
// 	WCHAR  *szCaptionTools[] = {L"新建",L"打开",L"保存",L"删除",L"工具",L"参数设置", L"运行",L"停止",L"系统退出"};
// 	WCHAR *sz[] = {L"新建",L"打开"};
	CHAR  *szCaptionTools[] = {"新建","打开","保存","删除","工具","参数设置", "运行","停止","系统退出"};
	rt.top = /*g_nCYTitle +*/ 1;
	rt.bottom = rt.top+g_nCYToolBar-2;
	for (int i =0; i < sizeof(szCaptionTools)/sizeof(szCaptionTools[0]); i++)
	{
		rt.left =(BTN_TOOL_WIDTH+1)*i+1;
		rt.right = rt.left+  BTN_TOOL_WIDTH;
		p_btTools[i] =(CWinXPButtonST *)NewMyButton(ID_BTN_FILE_NEW+i, (LPCTSTR)szCaptionTools[i], rt,BS_DEFPUSHBUTTON);
		p_btTools[i]->SetIcon(IDI_ICON_NEW+i);
		p_btTools[i]->SetAlign(CButtonST::ST_ALIGN_VERT);
		p_btTools[i]->DrawTransparent();
// 		p_btTools[i]->DrawFlatFocus(TRUE);
// 		p_btTools[i]->SetRounded(TRUE);
	}

	//*******************************初始化ROI选择栏*********************************************//
	CWinXPButtonST *p_btSelRoi[5];
	const  TCHAR  *szToolsTip[] = {_T("矩形1"),_T("矩形2"),_T("圆"),_T("自定义"),_T("取消选择")};
	rt.top = /*g_nCYTitle + */1;
	rt.bottom = rt.top+g_nCYToolBar-2;
	int nW = rt.right;
	for (int i =0; i <sizeof(szToolsTip)/sizeof(szToolsTip[0]); i++)//
	{
		rt.left = nW + 400+ (BTN_TOOL_WIDTH+1)*i+1;
		rt.right = rt.left+  BTN_TOOL_WIDTH;
		p_btSelRoi[i] =(CWinXPButtonST *)NewMyButton(ID_BTN_SEL_REC1+i, _T(""), rt,BS_DEFPUSHBUTTON);
		p_btSelRoi[i]->SetFontEx(g_cFont[1]);
		p_btSelRoi[i]->SetIcon(IDI_ICON_REC1+i);
// 		p_btSelRoi[i]->SetAlign(CButtonST::ST_ALIGN_VERT);
		p_btSelRoi[i]->SetTooltipText(szToolsTip[i]);
		p_btSelRoi[i]->DrawTransparent();
		p_btSelRoi[i]->DrawFlatFocus(TRUE);
	}

	//****************************************************************************//
	m_btnInterModel.SubclassDlgItem(IDC_BUTTON_ROI_INTER_MODEL,this);
	m_btnInterModel.MoveWindow(nW + 300, rt.top, BTN_TOOL_WIDTH,g_nCYToolBar);

// 	m_btnInterModel.SetFontEx(g_cFont[1]);
	m_btnInterModel.SetIcon(IDI_ICON10);
// 	m_btnInterModel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnInterModel.DrawTransparent();
	double  dtime;
	dtime = EndTime();
	CString strTime;
	strTime.Format(_T("消耗时间：%0.3f ms"), dtime*1000.0 );

	return TRUE;
}

CFont*  CHsbVisionDlg::NewMyFont(int nHeight,int nWidth, LPCTSTR  lpszFaceName)
{
	CFont *p_Font = new CFont();
	p_Font->CreateFont(nHeight,nWidth,0,0,FW_THIN,false,false,false,
		CHINESEBIG5_CHARSET,OUT_CHARACTER_PRECIS,
		CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
		FF_MODERN, lpszFaceName);

	return p_Font;
}

CButtonST* CHsbVisionDlg::NewMyButton(int nID,LPCTSTR lpCaption,CRect rect,int nStyle)
{
// 	CString m_Caption = L"新建";
// 	m_Caption.LoadString( nID ); //取按钮标题
	CButtonST *p_Button = new CButtonST();
	ASSERT_VALID(p_Button);

// 	LPCTSTR  wtbuf = "新建";
// 	WCHAR buf[20]={0,};
// 	CHAR bufc[20] = {0};
// 	int len = MultiByteToWideChar(CP_ACP, 0, wtbuf, -1,  NULL, 0);
// 	MultiByteToWideChar(CP_ACP, 0, wtbuf, -1, buf, len);
// 	memcpy(bufc, buf,20);

// 	int wLen = (CP_ACP,0,wtbuf,-1,NULL,0,NULL,NULL);//
// 	WideCharToMultiByte(CP_ACP,0,wtbuf,-1,buf,wLen,NULL,NULL);

	p_Button->Create(lpCaption, WS_CHILD | WS_VISIBLE | BS_FLAT| BS_PUSHBUTTON | nStyle, rect, this, nID ); //创建按钮
	return p_Button;
}

void CHsbVisionDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CRect rtWnd, rtTitle;
		GetWindowRect(&rtWnd);
		GetClientRect(&rtTitle);


		
////////////////////////////////draw  工具栏//////////////////////////////////////////////////////////////////////////////////////////////
		CBrush bsh;
		CPen pen;
		bsh.CreateSolidBrush(RGB(211,218,237));
		pen.CreatePen(0,1,RGB(105,105,105));
		CPen *pOldPen = dc.SelectObject(&pen);
		CBrush *pOldBsh = dc.SelectObject(&bsh);
		dc.Rectangle(0,0,g_nCXScreen, g_nCYToolBar);
		dc.SelectObject(pOldPen);
		dc.SelectObject(pOldBsh);
//////////////////////////////draw  客户区//////////////////////////////////////////////////////////////////////////////////////////////
		bsh.DeleteObject();
		bsh.CreateSolidBrush(RGB(207,232,204));
		dc.SelectObject(&bsh);
		dc.Rectangle(0, g_nCYToolBar+1,  g_nCXScreen,  g_nCYToolBar + 1+ g_nCYClient);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 		bsh.DeleteObject();
// 		pen.DeleteObject();
// 		bsh.CreateSolidBrush(RGB(217,223,240));
// 		pen.CreatePen(0,1,RGB(160,160,160));
// 		pOldPen = dc.SelectObject(&pen);
// 		pOldBsh = dc.SelectObject(&bsh);
// 		dc.Rectangle(0,g_nCYScreen-40,g_nCXScreen,g_nCYScreen);
// 		dc.SelectObject(pOldPen);
// 		dc.SelectObject(pOldBsh);

		CDialogEx::OnPaint();
	}
}

BOOL CHsbVisionDlg::OnCreateDialog(UINT  nIDTemplate, CWnd* pParentWnd)
{
	CDialog* pOneDlgObj=NULL;
	switch(nIDTemplate)
	{
	case IDD_DIALOG_TOOLS:
		{
			if (NULL == m_pToolsDlg)
			{
				m_pToolsDlg = new CToolsDlg;
				if ( m_pToolsDlg)
				{
					BOOL ret = m_pToolsDlg->Create(IDD_DIALOG_TOOLS,pParentWnd);
				}
			}
			pOneDlgObj = m_pToolsDlg;
			break;
		}
	case IDD_DIALOG_CAPUTRUE:
		{
			if (NULL == m_pCaptureDlg)
			{
				m_pCaptureDlg = new CcaptureImageDlg;
				if ( m_pCaptureDlg)
				{
					BOOL ret = m_pCaptureDlg->Create(IDD_DIALOG_CAPUTRUE,pParentWnd);
				}
			}
			pOneDlgObj = m_pCaptureDlg;
			break;
		}
	case IDD_DIALOG_MODEL_MATCH:
		{
			if (NULL == m_pFixModelDlg)
			{
				m_pFixModelDlg = new CcaptureImageDlg;
				if ( m_pFixModelDlg)
				{
					BOOL ret = m_pFixModelDlg->Create(IDD_DIALOG_MODEL_MATCH,pParentWnd);
				}
			}
			pOneDlgObj = m_pFixModelDlg;
			break;
		}
	case IDD_DIALOG_WORKING_PROC:
		{
			if (NULL == m_pFixModelDlg)
			{
				m_pWorkProcDlg = new CWorkingProcDlg;
				if ( m_pWorkProcDlg)
				{
					BOOL ret = m_pWorkProcDlg->Create(nIDTemplate,pParentWnd);
				}
			}
			pOneDlgObj = m_pWorkProcDlg;
			break;
		}
		break;
	}

	if (NULL!=pOneDlgObj)
	{
		pOneDlgObj->ShowWindow(SW_SHOW);
	}

	return TRUE;
}

 BOOL CHsbVisionDlg::PreTranslateMessage(MSG* pMsg)
 {
	 // TODO: Add your specialized code here and/or call the base class
	 if ((WM_KEYDOWN == pMsg->message) && (pMsg->wParam ==VK_F2))
	 {
		 OnF2();
		 
	 }
	 else
	 {
	 }
	 return CDialogEx::PreTranslateMessage(pMsg);
 }

 void CHsbVisionDlg::OnAbout()
 {
	 CAboutDlg  dlg;
	 dlg.DoModal();
 }

 void CHsbVisionDlg::OnFileNew()
 {
	 MessageBox(_T("OnFileNew"));
 }

 void CHsbVisionDlg::OnFileOpen()
 {
	 CFileDialog dlg( true,_T(".xls"),_T("*.xls"),OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 0, this);
	 if (dlg.DoModal() == IDOK)
	 {}
 }

 void CHsbVisionDlg::OnFileSave()
 {
	 MessageBox(_T("OnFileSave"));
// 	 CMenu* pMenu=GetMenu();
// 	 //获取1级菜单
// 	 CMenu* pFileMenu=pMenu->GetSubMenu(0);
// 	 CMenu* pTestMenu=pMenu->GetSubMenu(1);
 }

 void CHsbVisionDlg::OnFileDelete()
 {
// 	 CWorkingProcDlg dlg;
// 	 dlg.DoModal();
// 	 MoveWindow(2,g_nCYScreen - g_nCYClient+20,400,200);

	 CListCtrl  *m_ListWorkingProc;
	 m_ListWorkingProc =  ((CListCtrl *)GetDlgItem(IDC_LIST_WORKING_PROCESS));
	 m_ListWorkingProc->MoveWindow(1,g_nCYScreen - g_nCYClient+25,397,199);
	 DWORD ExStyle1 = m_ListWorkingProc->GetExtendedStyle();
	m_ListWorkingProc->SetExtendedStyle( ExStyle1|LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES|LVS_EX_GRIDLINES );//LVS_EX_FULLROWSELECT|
	 const  TCHAR *ss[] = {_T("序号"), _T("算法"),_T("相机"), _T("参数")};
	 for (int i = 0; i<sizeof(ss)/sizeof(ss[0]);i++)
	 {
		 m_ListWorkingProc->InsertColumn(i, ss[i], 0, 80);
	 }
	 m_ListWorkingProc->ShowWindow(SW_SHOW);
 }

 void CHsbVisionDlg::OnTools()
 {
	OnCreateDialog(IDD_DIALOG_TOOLS,this);
 }

void CHsbVisionDlg::OnExit()
{
	if (IDOK == MessageBox(_T("确定退出系统"), _T("提示"), MB_OKCANCEL))
	{
		EndDialog(0);
	}
	else
	{
		return  ;
	}
}

 void CHsbVisionDlg::OnF2()
 {
	 OnCreateDialog(IDD_DIALOG_CAPUTRUE,this);
 }

 void CHsbVisionDlg::OnSelRec1()
 {
// 	 g_boHalcon.OnSelModelRoi(ROI_RECTANGLE);
 }

 void CHsbVisionDlg::OnSelRec2()
 {
// 	 g_boHalcon.OnSelModelRoi(ROI_RECTANGLE2);
 }

 void CHsbVisionDlg::OnSelCir()
 {
// 	 g_boHalcon.OnSelModelRoi(ROI_CIRCLE);
 }

 void CHsbVisionDlg::OnSelUser()
 {
// 	 g_boHalcon.OnSelModelRoi(ROI_USER_DEFINE);

 }

 void CHsbVisionDlg::OnSelCancel()
 {
// 	  g_boHalcon.OnUnselmodelroi();
 }

 void CHsbVisionDlg::OnNcLButtonDown(UINT nHitTest, CPoint point)
 {
	 // TODO: Add your message handler code here and/or call default
	 if (HTCAPTION == nHitTest)
	 {
// 		  		return;//禁止移动窗口，保持窗口最大化
	 }
	 CDialogEx::OnNcLButtonDown(nHitTest, point);
 }


 void CHsbVisionDlg::OnTimer(UINT_PTR nIDEvent)
 {
	 // TODO: Add your message handler code here and/or call default
	 if (1 == nIDEvent)
	 {
		 KillTimer(1);
// 		 InitUiLayers();
		 ::PostMessage(HWND_BROADCAST,WM_HSB_CLOSE_LOGIN,0,0);
		 DWORD  dd = 	GetSysColor(COLOR_WINDOW );
		 CHAR sz[8] = { 0 };
		 sprintf(sz, "#%02X", dd);
// 		 HTuple  AttrValue;
// 		 m_grapWindow.SetFocus();
// 		 SetWindowAttr("background_color",(HTuple)sz);
// 		 g_boHalcon.SetHalconWindow(NULL, g_nCYScreen - g_nCYClient+2,0,g_nCXScreen-250,g_nCYClient, (Hlong)this->m_hWnd);
// 		 Invalidate();
	 }
	 else if (1001== nIDEvent)
	 {
		 KillTimer(nIDEvent);
		 OnCreateDialog(IDD_DIALOG_TOOLS,this);
		 OnCreateDialog(IDD_DIALOG_WORKING_PROC,this);
		 m_pWorkProcDlg->ShowWindow(SW_HIDE);
	 }
	 CDialogEx::OnTimer(nIDEvent);
 }


 void CHsbVisionDlg::OnBnClickedButtonRoiInterModel()
 {
 }

 void CHsbVisionDlg::OnClose()
 {
	 // TODO: Add your message handler code here and/or call default

	 OnExit();
// 	 CDialogEx::OnClose();
 }



 LRESULT CHsbVisionDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
 {
	 switch(message)
	 {
	 case WM_UPDATE_STATUSBAR_MSG:
		 {
			 CString  strCoord,strGrayVal;
			 int nx = LOWORD(wParam);
			 strCoord.Format(_T("%d, %d"), LOWORD(wParam), HIWORD(wParam));

			 BYTE bytes[4] = {0,};
			 bytes[0] = (byte) (0xff & lParam);
			 bytes[1] = (byte) ((0xff00 & lParam) >> 8);
			 bytes[2] = (byte) ((0xff0000 & lParam) >> 16);
			 bytes[3] = (byte) ((0xff000000 & lParam) >> 24);
			 if (1 == bytes[3])		 strGrayVal.Format(_T("%d"), bytes[0]);
			 else		strGrayVal.Format(_T("%d, %d, %d"), bytes[0],bytes[1],bytes[2]);
			 m_wndStatusBar.SetPaneText(2, strCoord,TRUE);
			 m_wndStatusBar.SetPaneText(3, strGrayVal,TRUE);
		 }
		 break;
	 }	 
	return CDialogEx::WindowProc(message, wParam, lParam);
 }
