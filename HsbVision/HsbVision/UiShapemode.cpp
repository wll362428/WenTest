// UiShapemode.cpp : implementation file
//

#include "stdafx.h"
#include "UiShapemode.h"

#define  UiShapemode_Layer_ID   8000
#define  UiShapemode_Btn_ID  UiShapemode_Layer_ID+20

// CUiShapemode

IMPLEMENT_DYNAMIC(CUiShapemode, CWnd)

CUiShapemode::CUiShapemode( LPCTSTR  lpToolName,CWnd *Parent)
{
	int i =0;
	m_parent = Parent;
	m_pShape = new CShapeMatch();
}

CUiShapemode::~CUiShapemode()
{
	if (NULL!=m_pShape)
	{
		delete m_pShape;
		m_pShape = NULL;
	}

	for (int i =0; i <UI_LAYERS_COUNT; i ++)
	{
		if (NULL!=m_pLayers[i])
		{
			delete m_pLayers[i];
			m_pLayers[i] =NULL;
		}
	}
}


BEGIN_MESSAGE_MAP(CUiShapemode, CWnd)
//	ON_WM_CREATE()
	ON_COMMAND_RANGE(UiShapemode_Btn_ID,UiShapemode_Btn_ID+2 ,OnButtonFunc)

	ON_WM_HSCROLL()
//	ON_WM_COPYDATA()
//	ON_WM_ACTIVATE()
	ON_WM_TIMER()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CUiShapemode message handlers

void CUiShapemode::InitLayers()
{

	char *s[] = {"对比度(低)","对比度(高)","组件尺寸","匹配分数","结果设定"};
	CRect  rect1(3,30,75,55);
	CFont  *pfont= NewFont();
	int num = sizeof(s)/sizeof(s[0]);
	for (int i =0; i < num;i++  )
	{
		int nId= UiShapemode_Layer_ID+i*2;
		m_pLayers[i] = NewLayers( Static, s[i],0, rect1,this,nId );
		m_pLayers[i]->SetFont(pfont);
		rect1.OffsetRect(0,35);
	}

	Layers layers[] = {SliderCtrl,SliderCtrl, SliderCtrl, SliderCtrl, Combobox};
	CRect  rect2(78,27,218,52);

	for (int  i = num ; i < num*2; i++  )
	{
		int nstyle = 0;
		if (Combobox == layers[i-num]) 
		{
			rect2.bottom+=100;
			nstyle = CBS_DROPDOWNLIST;
		}
		int nID= UiShapemode_Layer_ID+(i-num)*2+1;
	
		m_pLayers[i] = NewLayers( layers[i-num], "", nstyle,rect2,this,  nID);
		m_pLayers[i]->SetFont(pfont);

// 		if (SliderCtrl == layers[i])
		{
// 			m_pSlider[i] =(CSliderCtrl  *)NewLayers(layers[i], "", 0,rect2,this,UiShapemode_Layer_ID+i);
// 			m_pSlider[i]->SetFont(pfont);
// 			m_pSlider[i] ->SetRange(0,100);
		}
// 		else if (Combobox == layers[i])
		{
// 			m_pCombobox[i-4]=(CComboBox  *)NewLayers(layers[i], "", CBS_DROPDOWN,rect2,this,UiShapemode_Layer_ID+i);
// 			m_pCombobox[i-4]->SetFont(pfont);
// 			m_pLayers[i-6] = NewLayers( layers[i], "",0,rect2,this, UiShapemode_Layer_ID+i);

		}

// 		else if (Edit == layers[i])
		{
// 			NewLayers( layers[i], "",0,rect2,this, UiShapemode_Layer_ID+i);
// 			SetDlgItemText(UiShapemode_Layer_ID+i,"0.35");
		}
		rect2.OffsetRect(0,35);
	}

	int nIndex = 0;
	((CSliderCtrl *)m_pLayers[UI_LAYERS_COUNT/2])->SetRange(0,99);
	((CSliderCtrl *)m_pLayers[UI_LAYERS_COUNT/2 + (nIndex++)])->SetPos(4);

	((CSliderCtrl *)m_pLayers[UI_LAYERS_COUNT/2+nIndex])->SetRange(1,100);
	((CSliderCtrl *)m_pLayers[UI_LAYERS_COUNT/2+(nIndex++)])->SetPos(19);

	((CSliderCtrl *)m_pLayers[UI_LAYERS_COUNT/2+nIndex])->SetRange(0,100);
	((CSliderCtrl *)m_pLayers[UI_LAYERS_COUNT/2+(nIndex++)])->SetPos(0);

	((CSliderCtrl *)m_pLayers[UI_LAYERS_COUNT/2+nIndex])->SetRange(0,100);
	((CSliderCtrl *)m_pLayers[UI_LAYERS_COUNT/2+(nIndex++)])->SetPos(35);



	((CComboBox *)m_pLayers[UI_LAYERS_COUNT/2+nIndex])->AddString("查找成功为OK");
	((CComboBox *)m_pLayers[UI_LAYERS_COUNT/2+(nIndex++)])->AddString("查找成功为NG");




// 	 NewButton("搜索区域", BS_PUSHBUTTON,CRect (20,250,100,280),this,UiShapemode_Btn_ID+2 )->SetFont(pfont);
// 	 NewButton("创建模板", BS_PUSHBUTTON,CRect (120,250,200,280),this,UiShapemode_Btn_ID+3)->SetFont(pfont);


// 	CToolTipCtrl *tooltip;
// 	CSliderCtrl   slider;
// 	slider.SetToolTips()
}

void CUiShapemode::OnButtonFunc(UINT nID)
{
	switch(nID)
	{
	case UiShapemode_Btn_ID:
		RunOnce();
		break;
	case UiShapemode_Btn_ID + 1:
		Save();
		break;
	}
}

BOOL CUiShapemode::RunOnce()
{
// 	m_pShape->Run( m_pShape->CreateShape( m_pSlider[0]->GetPos(),  m_pSlider[1]->GetPos(),m_pSlider[2]->GetPos() ));

	return TRUE;
}


CString  CUiShapemode::Save()
{
	CString str;
	for (int i = UiShapemode_Layer_ID; i < UiShapemode_Layer_ID+UI_LAYERS_COUNT; i++)
	{
		CString strtmp;
			if (0 == i%2)
			{
				GetDlgItemText(i,strtmp);
			}

			else if (1==i%2)
			{
				if (GetDlgItem(i)->GetSafeHwnd() == m_pLayers[9]->GetSafeHwnd())
				{
					GetDlgItemText(i,strtmp);
				}
				else
				{
// 					int npos = ((CSliderCtrl *)m_pLayers[i-UiShapemode_Layer_ID])->GetPos();
					int npos = ((CSliderCtrl *)GetDlgItem(i))->GetPos();
					strtmp = int2String(npos);
				}
			}

			str +=strtmp;
	}
	return str;
}


void CUiShapemode::DrawItem(LPDRAWITEMSTRUCT   lpDIS)
{
// 	CDC*	pDC = CDC::FromHandle(lpDIS->hDC);
// 	pDC->SetBkMode(TRANSPARENT);
// 
// 	CRect itemRect = lpDIS->rcItem;

	CUiToolBase::DrawItem(lpDIS);
}

void CUiShapemode::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	DWORD dwStyle = GetStyle();
	SetWindowLong(GetSafeHwnd(),GWL_STYLE,dwStyle | SS_OWNERDRAW  |SS_NOTIFY);  
//   	InitLayers();

	CStatic::PreSubclassWindow();
}


void CUiShapemode::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	if (  UiShapemode_Layer_ID  <= pScrollBar->GetDlgCtrlID()    &&  pScrollBar->GetDlgCtrlID() <= UiShapemode_Layer_ID +2 )
	{
//  		m_pShape->OnSetMincontrast(m_pSlider[0]->GetPos(),  m_pSlider[1]->GetPos(),m_pSlider[2]->GetPos());

	}

	CUiToolBase::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CUiShapemode::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	CUiToolBase::OnTimer(nIDEvent);
}


void CUiShapemode::OnSize(UINT nType, int cx, int cy)
{
	InitLayers();
	CUiToolBase::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
}
