#pragma once
#include <afxdialogex.h>
#include "afxcmn.h"
#include "BtnST.h"
#include "afxwin.h"
// CcaptureImageDlg dialog
class CcaptureImageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CcaptureImageDlg)
public:
	CcaptureImageDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CcaptureImageDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_CAPUTRUE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnPaint();

public:
	CButtonST	m_btnCapture[4];
	CComboBox m_comBoxCamerList;
};
