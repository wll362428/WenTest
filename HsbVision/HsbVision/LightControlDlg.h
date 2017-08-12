#pragma once
#include <afxdialogex.h>
#include "afxcmn.h"
#include "afxwin.h"

// CLightControlDlg dialog
class CLightControlDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLightControlDlg)
public:
	CLightControlDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLightControlDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_LIGHTCONTROL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
private:
	void InitUILayers();

	int m_nSize;
	CComboBox m_comPort1,m_comPort2,m_comPort3;
	CComboBox m_comBaud1,m_comBaud2,m_comBaud3;

	CSliderCtrl m_SliderLight1;
	CSliderCtrl m_SliderLight2;
	CSliderCtrl m_SliderLight3;
	CSliderCtrl m_SliderLight4;
	CSliderCtrl m_SliderLight5;
	CSliderCtrl m_SliderLight6;
	CSliderCtrl m_SliderLight7;
	CSliderCtrl m_SliderLight8;
	CSliderCtrl m_SliderLight9;
	CSliderCtrl m_SliderLight10;
	CSliderCtrl m_SliderLight11;
	CSliderCtrl m_SliderLight12;

public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnOpenLight();
};
