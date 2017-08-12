#pragma once

#include "..\HVisionDll\ShapeMatch.h"
#include "..\HVisionDll\ImagePreProcessing.h"

// CUiToolBase
#define  BTN_SHAPE_RUN   8000
#define  BTN_SHAPE_SAVE   8001

#define  BTN_BLOB_RUN   8002
#define  BTN_BLOB_SAVE   8003

#define BTN_CHECK_0  8200
#define BTN_CHECK_1  8201
#define BTN_CHECK_2  8202
#define BTN_CHECK_3  8203
#define BTN_CHECK_4  8204
#define BTN_CHECK_5  8205
#define BTN_CHECK_6  8206
#define  BTN_PREPROCESS_RUN 8207

#define  SLIDER_SHAPE_MIN      8100
#define  SLIDER_SHAPE_MAX     8101
#define  SLIDER_SHAPE_MOD     8102


#define  SLIDER_THRES_MIN     8103
#define  SLIDER_THRES_MAX    8104

static  UINT  WM_UPDATE_WORKLIST_MSG= RegisterWindowMessage(_T("WM_UPDATE_WORKLIST_MSG"));

enum Layers
{
	Static=0,
	Edit,
	Button,
	Combobox,
	SliderCtrl,

};

class CUiToolBase : public CStatic
{
	DECLARE_DYNAMIC(CUiToolBase)

public:
	CUiToolBase();
	virtual ~CUiToolBase();
	virtual void DrawItem(LPDRAWITEMSTRUCT  lpDIS);

// 	afx_msg void OnButtonFunc(UINT nID);

public:
// 	CStatic*		  NewStatic(LPCTSTR lpszText, DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID=0xffff);
// 	CEdit*		  NewEdit( DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID =0xffff );
// 	CButton*	  NewButton(LPCTSTR lpszText, DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID=0xffff);
// 	CSliderCtrl * NewSliderCtrl(DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID=0xffff);
// 	CComboBox * NewComboBox(DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID=0xffff);
	CWnd *NewLayers(Layers eLayers, LPCTSTR lpszText, DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID=0xffff);
// 	CFont *NewFont();

public:
	virtual void InitLayers();
	virtual BOOL RunOnce();
	virtual CString Save();
public:
	CHAR  m_toolName[MAX_PATH];

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
};

