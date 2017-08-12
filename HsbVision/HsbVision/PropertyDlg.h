#pragma once

#include "UiShapemode.h"
#include "UiBlobIns.h"
#include "UiImagePreProcessing.h"
#include "afxwin.h"
// CPropertyDlg dialog

class CPropertyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPropertyDlg)

public:
	CPropertyDlg(CWnd* pParent = NULL);   // standard constructor
	CPropertyDlg(LPCTSTR  lpItemText);

	virtual ~CPropertyDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_PROPERTY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnTimer(UINT_PTR nIDEvent);

public:
	void SetToolAttr(LPCTSTR  lpItemName);

public:
// 	CUiShapemode  m_uiShape;
// 	CUiBlobIns m_uiBlob;
// 	CUiImagePreProcessing m_uiPreImage;

	CUiToolBase  *m_pUiTool;
	DECLARE_MESSAGE_MAP()
private:
	CString  m_strToolName;

public:
	afx_msg void OnBnClickedButtonRun();
	afx_msg void OnBnClickedButtonSave();
};
