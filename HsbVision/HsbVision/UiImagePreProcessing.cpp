// ImagePreProcessing.cpp : implementation file
//

#include "stdafx.h"
#include "HsbVision.h"
#include "UiImagePreProcessing.h"


// CImagePreProcessing

IMPLEMENT_DYNAMIC(CUiImagePreProcessing, CWnd)

CUiImagePreProcessing::CUiImagePreProcessing()
{
	m_ImaePreProcess = new CImagePreProcessing();

	memset(m_bIsCheck, 0, sizeof(m_bIsCheck));
}

CUiImagePreProcessing::~CUiImagePreProcessing()
{
}


BEGIN_MESSAGE_MAP(CUiImagePreProcessing, CWnd)
	ON_COMMAND_RANGE(BTN_CHECK_0,BTN_CHECK_0+8,OnButtonFunc)

END_MESSAGE_MAP()

void CUiImagePreProcessing::InitLayers()
{
	char *s[] = {"GRAY", "R",  "G","B", "H",  "S","V"};

	CRect rect(15,10,130,40);
	for (int i =0; i < sizeof(s)/sizeof(s[0]); i++)
	{
		m_Btn[i] = NewButton(s[i], BS_CHECKBOX, rect,this, BTN_CHECK_0+i);
		rect.OffsetRect(0,30);
	}

// 	m_Btn[0] = NewButton("GRAY", BS_CHECKBOX, CRect(11,1,130,30),this, BTN_CHECK_0);
// 	m_Btn[1] = NewButton("R", BS_CHECKBOX, CRect(11,50,130,80),this, BTN_CHECK_1);


}

void CUiImagePreProcessing::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	DWORD dwStyle = GetStyle();
	SetWindowLong(GetSafeHwnd(),GWL_STYLE,dwStyle | SS_OWNERDRAW  |SS_NOTIFY);  
	InitLayers();

	CStatic::PreSubclassWindow();
}

void CUiImagePreProcessing::OnButtonFunc(UINT nID)
{
	switch(nID)
	{
	case BTN_CHECK_0:
	case BTN_CHECK_1:
	case BTN_CHECK_2:
	case BTN_CHECK_3:
	case BTN_CHECK_4:
	case BTN_CHECK_5:
	case BTN_CHECK_6:
		{
			for (int i =0; i<7; i++)
			{
				if (nID - BTN_CHECK_0 == i)
				{
					m_bIsCheck[i] = !m_bIsCheck[i];
					m_Btn[nID - BTN_CHECK_0]->SetCheck(m_bIsCheck[i]);
				}
				else
				{
					m_bIsCheck[i] = FALSE;
					m_Btn[i]->SetCheck(m_bIsCheck[i]);
				}
			}
			m_ImaePreProcess->RGB2SingleChannel(nID - BTN_CHECK_0);
		}

		break;

	case  BTN_PREPROCESS_RUN:
		break;
	}
}

// BOOL CUiImagePreProcessing::Save()
//  {
// 	 return TRUE;
//  }
