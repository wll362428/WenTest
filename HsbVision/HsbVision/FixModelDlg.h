#pragma once
#include "afxcmn.h"

// #include "..\HVisionDll\ShapeMatch.h"
#include "afxpropertygridctrl.h"

// CFixModelDlg dialog

class CFixModelDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFixModelDlg)

public:
	CFixModelDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFixModelDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_MODEL_MATCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
// 	void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_SliderContrast;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

private:
// 	CShapeMatch *m_pShape;
public:
	afx_msg void OnBnClickedButtonSaveOpration();
	CMFCPropertyGridCtrl m_proPertyCtrl;
};
