// CUiToolBase.cpp : implementation file
//

#include "stdafx.h"
#include "HsbVision.h"
#include "UiToolBase.h"
#include "HsbVisionDlg.h"


// CUiToolBase

IMPLEMENT_DYNAMIC(CUiToolBase, CStatic)

CUiToolBase::CUiToolBase()
{
	memset(m_toolName,0,sizeof(m_toolName));
}

CUiToolBase::~CUiToolBase()
{
}


BEGIN_MESSAGE_MAP(CUiToolBase, CWnd)

// 	ON_COMMAND_RANGE(BTN_SHAPE_RUN,BTN_SHAPE_RUN+2 ,OnButtonFunc)

END_MESSAGE_MAP()


void CUiToolBase::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	DWORD dwStyle = GetStyle();
	SetWindowLong(GetSafeHwnd(),GWL_STYLE,dwStyle | SS_OWNERDRAW  |SS_NOTIFY);  

	CStatic::PreSubclassWindow();
}

CWnd *CUiToolBase::NewLayers(Layers eLayers, LPCTSTR lpszText, DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	CWnd *pLayers;
	switch(eLayers)
	{
	case Static:
		pLayers = NewStatic(lpszText, dwStyle, rect, pParentWnd,nID);
		break;
	case  Edit:
		pLayers = NewEdit(dwStyle, rect, pParentWnd,nID);
		break;
	case Button:
		pLayers = NewButton(lpszText, dwStyle, rect, pParentWnd,nID);
		break;
	case  Combobox:
		pLayers = NewComboBox(dwStyle, rect, pParentWnd,nID);
		break;
	case  SliderCtrl:
		pLayers = NewSliderCtrl(dwStyle, rect, pParentWnd,nID);
		break;
	default:
		pLayers = new CWnd();
	}

	return pLayers;
}
// 
// CStatic*		  CUiToolBase::NewStatic(LPCTSTR lpszText, DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID  )
// {
// 	CStatic *pStatic = new CStatic();
// 	pStatic->Create(lpszText, WS_CHILD | WS_VISIBLE|dwStyle, rect, pParentWnd, nID);
// 	return pStatic;
// }
// 
// CEdit*		  CUiToolBase::NewEdit(DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID  )
// {
// 	CEdit *pEdit = new CEdit();
// 	pEdit->Create(WS_CHILD | WS_VISIBLE|dwStyle, rect, pParentWnd, nID);
// 	return pEdit;
// }
// 
// 
// CButton*		  CUiToolBase::NewButton(LPCTSTR lpszText, DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID)
// {
// 	CButton* pButton = new CButton();
// 	pButton->Create(lpszText, WS_CHILD | WS_VISIBLE|dwStyle, rect, pParentWnd, nID);
// 	return pButton;
// }
// 
// CSliderCtrl * CUiToolBase::NewSliderCtrl(DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID)
// {
// 	CSliderCtrl* pSliderCtrl = new CSliderCtrl();
// 	pSliderCtrl->Create( WS_CHILD | WS_VISIBLE|TBS_NOTICKS |TBS_HORZ|dwStyle, rect, pParentWnd, nID);
// 	return pSliderCtrl;
// }
// 
// CComboBox * CUiToolBase::NewComboBox(DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID)
// {
// 	CComboBox* pComboBox= new CComboBox();
// 	pComboBox->Create( WS_CHILD | WS_VISIBLE|CBS_DROPDOWN|dwStyle, rect, pParentWnd, nID);
// 	return pComboBox;
// }
// 
// 
// 
// CFont *CUiToolBase::NewFont()
// {
// 	CFont *font = new CFont();
// 	font->CreateFontA(18,0,0,0,300,0,0,0,1,0,0,0,0,_T("Î¢ÈíÑÅºÚ"));
// 	return font;
// }

void CUiToolBase::DrawItem(LPDRAWITEMSTRUCT  lpDIS)
{
	CDC*	pDC = CDC::FromHandle(lpDIS->hDC);
	pDC->SetBkMode(TRANSPARENT);

	CRect itemRect = lpDIS->rcItem;
// 	pDC->MoveTo(3,3);
// 	pDC->LineTo(3,300);
}


void CUiToolBase::InitLayers()
{

}

BOOL CUiToolBase::RunOnce()
{
	return TRUE;
}


CString CUiToolBase::Save()
{
	CString  strData;
	return strData;
}




// CUiToolBase message handlers



