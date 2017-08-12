// GraphWindow.cpp : implementation file
//

#include "stdafx.h"
#include "GraphWindow.h"
#include "Resource.h"

// HalconCpp::HWindow  m_Window;

// CGraphWindow

IMPLEMENT_DYNAMIC(CGraphWindow, CStatic)

CGraphWindow::CGraphWindow()
{
	m_bDrawRegion = m_bLeftBtnDown = false;
}

CGraphWindow::~CGraphWindow()
{
// 	if (NULL != CHVisionWindow::GetInstance())
// 	{
// 		delete CHVisionWindow::GetInstance();
// 		CHVisionWindow::GetInstance() = NULL;
// 	}
}


BEGIN_MESSAGE_MAP(CGraphWindow, CStatic)
	ON_WM_CREATE()
// 	ON_BN_CLICKED(IDS_STRING102, OnButtonFunc)
	ON_COMMAND_RANGE(BTN_GRAPHWINDOW,BTN_GRAPHWINDOW+5 ,OnButtonFunc)
	ON_COMMAND_RANGE(ID_GRAB_ONE,ID_SAVE_IMAGE ,OnRightClickMenu)

	ON_WM_LBUTTONDOWN()
	ON_WM_CLOSE()
	ON_WM_CONTEXTMENU()
//	ON_WM_SETCURSOR()
ON_WM_SETCURSOR()
ON_WM_LBUTTONUP()
//ON_WM_LBUTTONDBLCLK()
ON_WM_MOUSEWHEEL()
ON_WM_MOUSEMOVE()
//ON_WM_MOUSEHOVER()
//ON_WM_MOUSEHWHEEL()
//ON_WM_MBUTTONDOWN()
//ON_WM_MBUTTONUP()
ON_WM_TIMER()
ON_WM_SIZE()
END_MESSAGE_MAP()

BOOL CGraphWindow::OnInitDialog()
{
	return 0;
}

// void  CGraphWindow::SetImage(HObject hImage)
// {
// }

void CGraphWindow::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类  
	DWORD dwStyle = GetStyle();
	SetWindowLong(GetSafeHwnd(),GWL_STYLE,dwStyle | SS_OWNERDRAW  |SS_NOTIFY);  
// 

// 	CStatic *pStatic = new CStatic();
// 	pStatic->Create("对比", WS_CHILD | WS_VISIBLE, CRect(5,5,50,20),this,9110);

	CButtonST *p_MyBut[5] ;
 
	p_MyBut[0] = NewMyButton( _T("适应"), BTN_GRAPHWINDOW, CRect(0,0,50,30),  0);
	p_MyBut[1] = NewMyButton( "rect1", BTN_GRAPHWINDOW+1, CRect(50,0,100,30),  0);
	p_MyBut[2] = NewMyButton( "rect2", BTN_GRAPHWINDOW+2, CRect(100,0,150,30),  0);
	p_MyBut[3] = NewMyButton( "circle", BTN_GRAPHWINDOW+3, CRect(150,0,200,30),  0);
	p_MyBut[4] = NewMyButton( "User", BTN_GRAPHWINDOW+4, CRect(200,0,250,30),  0);


	CStatic::PreSubclassWindow();
}

void CGraphWindow::OnButtonFunc(UINT nID)
{
	m_bDrawRegion = true;
	switch(nID)
	{
	case BTN_GRAPHWINDOW:
		{
			CHVisionWindow::GetInstance()->ReSet();
		}
		break;
	case BTN_GRAPHWINDOW+1:
		{
			CHVisionWindow::GetInstance()->OnDrawRegion(CHVisionWindow::RECTANGLE1, CHVisionWindow::UNION,NULL);
		}
		break;
	case BTN_GRAPHWINDOW+2://
		{
			CHVisionWindow::GetInstance()->OnDrawRegion(CHVisionWindow::RECTANGLE2, CHVisionWindow::UNION,NULL);
		}

		break;
	case BTN_GRAPHWINDOW+3://缩小
		{
			CHVisionWindow::GetInstance()->OnDrawRegion(CHVisionWindow::ELLIPSE, CHVisionWindow::UNION,NULL);
		}
		break;
	case BTN_GRAPHWINDOW+4:
		{
			CHVisionWindow::GetInstance()->OnDrawRegion(CHVisionWindow::USER_DEFINE, CHVisionWindow::UNION,NULL);
		}
		break;
	}
	m_bDrawRegion = false;

}

void CGraphWindow::OnRightClickMenu(UINT nID)
{
	switch(nID)
	{
	case ID_GRAB_ONE:
		break;
	case ID_OPENIMAGE://
		{
			CString hFilePath;
			CFileDialog dlg( TRUE,_T(".png;.bmp;.jpeg;.jpg;.TIF"),_T("*.png;*.bmp;*.jpeg;*.jpg;*.TIF"),OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 0, NULL);
			if (dlg.DoModal() == IDOK)  
			 	hFilePath = dlg.GetPathName();
			else return;

			CHVisionWindow::GetInstance()->LoadImage(hFilePath.GetBuffer());
		}
		break;
	}
}

// CGraphWindow message handlers
CButtonST* CGraphWindow::NewMyButton(char*  lpszCaption, int nID,CRect rect,int nStyle)
{
// 	CString m_Caption;
// 	m_Caption.LoadString( nID ); //取按钮标题
	CButtonST *p_Button = new CButtonST();
	ASSERT_VALID(p_Button);
	p_Button->Create(lpszCaption, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | nStyle, rect, this, nID ); //创建按钮
	return p_Button;
}


int CGraphWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

// 	p_MyBut->Create( "新建", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | nStyle, rect, this, nID ); //创建按钮
	return 0;
}



void CGraphWindow::OnLButtonDown(UINT nFlags, CPoint point)
{
	this->SetFocus();
	m_bLeftBtnDown = true;
	CHVisionWindow::GetInstance()->OnLButtonDown();
	CStatic::OnLButtonDown(nFlags, point);
}


void CGraphWindow::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bLeftBtnDown = false;
	CStatic::OnLButtonUp(nFlags, point);
}


BOOL CGraphWindow::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	CRect  rc = m_rtImage;
	ClientToScreen(&rc);
	if (rc.PtInRect(pt))
	{
		if (zDelta >0)
		{
			CHVisionWindow::GetInstance()->ZoomImage(CHVisionWindow::ZoomIn);
		}
		else
		{
			CHVisionWindow::GetInstance()->ZoomImage(CHVisionWindow::ZoomOut);
		}
	}

	return CStatic::OnMouseWheel(nFlags, zDelta, pt);
}


void CGraphWindow::OnMouseMove(UINT nFlags, CPoint point)
{
	DWORD dwParam=0, dlParam=0;
	CHVisionWindow::GetInstance()->OnGetImageVal(point, &dwParam,&dlParam);
	::PostMessage(GetParent()->m_hWnd,WM_UPDATE_STATUSBAR_MSG,dwParam,dlParam);

	if (m_bLeftBtnDown)
	{
// 		TRACE("OnMouseMove\r\n");
		if (m_bDrawRegion)		return  	CStatic::OnMouseMove(nFlags, point);
		CHVisionWindow::GetInstance()->OnMoveImage(point);
	}
	CStatic::OnMouseMove(nFlags, point);
}


void CGraphWindow::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	CStatic::OnClose();
}

void CGraphWindow::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: Add your message handler code here

	if (!m_bDrawRegion)
	{
		CMenu popMenu;

		popMenu.LoadMenu(IDR_MENU_RIGHT);         //载入菜单

		CMenu *pPopup;

		pPopup=popMenu.GetSubMenu(0);     //获得子菜单指针

		// 	pPopup->EnableMenuItem(ID_1,MF_BYCOMMAND|MF_ENABLED);  //允许菜单项使用
		// 	pPopup->EnableMenuItem(ID_2,MF_BYCOMMAND|MF_DISABLED|MF_GRAYED);       //不允许菜单项使用

		//ClientToScreen(&point);            //将客户区坐标转换成屏幕坐标

		pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);                //显示弹出菜单，参数依次为(鼠标在菜单左边|跟踪右键，x，y，this)

		pPopup->Detach();
		popMenu.DestroyMenu();
	}

}


// void CGraphWindow::OnShowImage()
// {
// 
// }



BOOL CGraphWindow::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
// 	return CStatic::OnSetCursor(pWnd, nHitTest, message);
	HCURSOR hCur=LoadCursor( NULL , IDC_ARROW );
// 	if (	Cursor_zoomin ==		m_CursorType )
// 	{
// 		hCur = LoadCursor( NULL , IDC_SIZEWE );
// 	}
// 	else if (Cursor_zoomout ==		m_CursorType)
// 	{
// 		hCur = LoadCursor( NULL , IDC_SIZENS );
// 	}
// 	else if (Cursor_arrow == m_CursorType)
// 	{
// 		hCur = LoadCursor( NULL , IDC_ARROW );
// 	}
// 	else if (Cursor_hand == m_CursorType)
// 	{
// 		hCur = LoadCursor( NULL , IDC_HAND );
// 	}
	if (NULL != hCur)
	{
		::SetCursor(hCur);
	}
	return TRUE;
}


void CGraphWindow::DrawItem(LPDRAWITEMSTRUCT )
{
	return ;
	CRect rcWnd;  
	GetWindowRect(&rcWnd);  
	ScreenToClient(&rcWnd);
	CString strText;
	GetWindowText(strText);

	CBitmap bmp;
// 	bmp.LoadBitmap(IDB_BITMAP1);
	BITMAP bmpInfo;
	bmp.GetBitmap(&bmpInfo);
	CDC *pdc = GetWindowDC();
	CDC dcMem;
	dcMem.CreateCompatibleDC(pdc);
	CBitmap bmpBg;
	bmpBg.CreateCompatibleBitmap(pdc,rcWnd.Width(),rcWnd.Height());  
	dcMem.SelectObject(&bmpBg);  

	CDC dcDraw;  
	dcDraw.CreateCompatibleDC(pdc);  
	dcDraw.SelectObject(&bmp);  
	dcMem.StretchBlt(0,0,rcWnd.Width(),rcWnd.Height(),&dcDraw,0,0,bmpInfo.bmWidth,bmpInfo.bmHeight,SRCCOPY);  

	CFont font;  
	VERIFY(font.CreateFont(  
		12,                        // nHeight  
		0,                         // nWidth  
		0,                         // nEscapement  
		0,                         // nOrientation  
		FW_NORMAL,                 // nWeight  
		FALSE,                     // bItalic  
		FALSE,                     // bUnderline  
		0,                         // cStrikeOut  
		ANSI_CHARSET,              // nCharSet  
		OUT_DEFAULT_PRECIS,        // nOutPrecision  
		CLIP_DEFAULT_PRECIS,       // nClipPrecision  
		DEFAULT_QUALITY,           // nQuality  
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily  
		_T("宋体")));                 // lpszFacename  

	dcMem.SelectObject(&font);  
	dcMem.SetBkMode(TRANSPARENT);  
	dcMem.SetTextColor(RGB(255,0,0));  
	dcMem.DrawText(strText,&rcWnd,DT_CENTER);  
	//pdc->BitBlt(0,0,rcWnd.Width(),rcWnd.Height(),&dcMem,0,0,SRCCOPY);  
	//pdc->TransparentBlt(0,0,rcWnd.Width(),rcWnd.Height(),&dcMem,0,0,rcWnd.Width(),rcWnd.Height(),RGB(255,0,0));  
	BLENDFUNCTION bf = {0};
	bf.AlphaFormat = AC_SRC_OVER ;
	bf.BlendFlags = 0;
	bf.BlendOp = AC_SRC_OVER ;
	bf.SourceConstantAlpha = 135;
	pdc->AlphaBlend(0,0,rcWnd.Width(),rcWnd.Height(),&dcMem,0,0,rcWnd.Width(),rcWnd.Height(),bf);  
	bmp.DeleteObject();
	ReleaseDC(pdc);
}


void CGraphWindow::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	CStatic::OnTimer(nIDEvent);
}


void CGraphWindow::OnSize(UINT nType, int cx, int cy)
{
// 	CRect rt;
	this->GetClientRect(&m_rtImage);

	m_rtImage.top += 30;
	m_rtImage.bottom -=3;
 	CHVisionWindow::GetInstance()->InitWindow(m_rtImage, m_hWnd);

	CStatic::OnSize(nType, cx, cy);

}
