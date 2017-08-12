#pragma once
#include "afxcmn.h"


// CWorkingProcDlg dialog
typedef struct _HSB_WORK_FILE
{
	CString  szId;//ÐòºÅ
	CString  szName;//
	CString  szPosition;
	CString  szCamera;
	CString  szLight;
	CString  szAlg;//
	CString szPreProcess;//
	CString szProperty;//
	CString szFilePath;//
	CString   szReserve1;
	CString   szReserve2;

public:
	_HSB_WORK_FILE()
	{
	}

public:
	void getStringArray(	CStringArray  &strarry)
	{
		strarry.Add(szId);
		strarry.Add(szName);
		strarry.Add(szPosition);
		strarry.Add(szCamera);
		strarry.Add(szLight);
		strarry.Add(szAlg);
		strarry.Add(szPreProcess);
		strarry.Add(szProperty);
		strarry.Add(szFilePath);
		strarry.Add(szReserve1);
		strarry.Add(szReserve2);
	}

	void setStringArray(	CStringArray  strarry)
	{
		int nIndex = 0;
		szId = strarry.GetAt(nIndex++);
		szName = strarry.GetAt(nIndex++);
		szPosition = strarry.GetAt(nIndex++);
		szCamera =strarry.GetAt(nIndex++);
		szLight = strarry.GetAt(nIndex++);
		szAlg = strarry.GetAt(nIndex++);
		szPreProcess =  strarry.GetAt(nIndex++);
		szProperty = strarry.GetAt(nIndex++);
		szFilePath = strarry.GetAt(nIndex++);
		szReserve1 = strarry.GetAt(nIndex++);
		szReserve2 = strarry.GetAt(nIndex++);
	}
}*p_hsb_work_file;


class CWorkingProcDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWorkingProcDlg)

public:
	CWorkingProcDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWorkingProcDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_WORKING_PROC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl  *m_ListWorkingProc;
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT  OnAddData(WPARAM wParam, LPARAM lParam);


public:
	vector<_HSB_WORK_FILE>  m_vecWorkFile;

};
