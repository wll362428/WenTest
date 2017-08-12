#pragma once
#include <afxdialogex.h>
#include "afxcmn.h"
#include "PropertyDlg.h"

// CToolsDlg dialog
class CToolsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CToolsDlg)

public:
	CToolsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CToolsDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_TOOLS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_TreeList;
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnNMDblclkTree1(NMHDR *pNMHDR, LRESULT *pResult);

	void OnDoItemEvent(LPCTSTR  pItemText);
	void OnShowPropertyDlg(LPCTSTR  pItemText="", BOOL bShow=TRUE);


	afx_msg void OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);

private:
	CPropertyDlg *m_pPropertyDlg ;


};
