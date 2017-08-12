// UiShapemode.cpp : implementation file
//

#include "stdafx.h"
#include "UiBlobIns.h"


// CUiBlobIns

IMPLEMENT_DYNAMIC(CUiBlobIns, CWnd)

CUiBlobIns::CUiBlobIns( LPCTSTR  lpToolName,CWnd *Parent)
{
	int i =0;
	m_parent = Parent;
	strcpy(m_toolName, lpToolName);

}

CUiBlobIns::~CUiBlobIns()
{
}


BEGIN_MESSAGE_MAP(CUiBlobIns, CWnd)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(BTN_SHAPE_RUN,BTN_SHAPE_RUN+2 ,OnButtonFunc)

	ON_WM_HSCROLL()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CUiBlobIns message handlers
void CUiBlobIns::InitLayers()
{
	NewStatic("低阈值",0, CRect(0,5,80,30),this,111);
	NewStatic("高阈值",0, CRect(0,35,80,65),this,1112);
//   	NewStatic("最小组件尺寸",0, CRect(0,60,90,85),this);

	NewButton("执行一次", 0,CRect (20,100,100,130),this,BTN_BLOB_RUN);

	m_pSliderMinGray= NewSliderCtrl(0,CRect(80,0,220,30), this,SLIDER_THRES_MIN);
	m_pSliderMaxGray= NewSliderCtrl(0,CRect(80,30,220,55), this,SLIDER_THRES_MAX);


	m_pSliderMinGray->SetRange(0,254);
	m_pSliderMinGray->SetPos(0);
	m_pSliderMaxGray->SetRange(1,255);
	m_pSliderMaxGray->SetPos(10);

}

void CUiBlobIns::OnButtonFunc(UINT nID)
{
	switch(nID)
	{
	case BTN_SHAPE_RUN:
		RunOnce();
		break;
	}	
}

BOOL CUiBlobIns::RunOnce()
{
	AfxMessageBox("CUiBlobIns");
	return TRUE;
}

CString  CUiBlobIns::Save()
{
	CString  strData;
	return strData;
}

int CUiBlobIns::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void CUiBlobIns::DrawItem(LPDRAWITEMSTRUCT   lpDIS)
{
// 	CDC*	pDC = CDC::FromHandle(lpDIS->hDC);
// 	pDC->SetBkMode(TRANSPARENT);
// 
// 	CRect itemRect = lpDIS->rcItem;

	CUiToolBase::DrawItem(lpDIS);
}

void CUiBlobIns::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	DWORD dwStyle = GetStyle();
	SetWindowLong(GetSafeHwnd(),GWL_STYLE,dwStyle | SS_OWNERDRAW  |SS_NOTIFY);  
//   	InitLayers();

// 	CStatic *pStatic = new CStatic();
// 	pStatic->Create("对比", WS_CHILD | WS_VISIBLE, CRect(5,5,50,20),this,9110);

	CStatic::PreSubclassWindow();
}


void CUiBlobIns::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	if (  8100 == pScrollBar->GetDlgCtrlID()  )
	{
// 		m_pShape->OnSetMincontrast(pSlider->GetPos());
// 
// 		TRACE("%d\r\n", pSlider->GetPos());
	}

	CUiToolBase::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CUiBlobIns::OnSize(UINT nType, int cx, int cy)
{
	CUiToolBase::OnSize(nType, cx, cy);
	InitLayers();
	// TODO: Add your message handler code here
}
