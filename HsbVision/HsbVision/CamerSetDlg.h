#pragma once
#include <afxdialogex.h>
#include "afxcmn.h"



// CCamerSetDlg dialog
class CCamerSetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCamerSetDlg)
public:
	CCamerSetDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCamerSetDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_CAMER_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
};
