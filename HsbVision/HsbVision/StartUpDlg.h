#pragma once


// CStartUpDlg dialog

class CStartUpDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStartUpDlg)

public:
	CStartUpDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CStartUpDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();

public:
	  void  CloseDialog();
	  virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
