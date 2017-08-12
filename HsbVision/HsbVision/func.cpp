#include "stdafx.h"
#include "func.h"
#include "Psapi.h"
#pragma  comment(lib, "Psapi.lib")
// 	MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, buffer, -1, buffer_t, sizeof(buffer_t)/sizeof(TCHAR));

#define  HALCON_LICENSE_DIR   _T("C:\\Program Files\\MVTec\\HALCON-12.0\\license")
#define  HALCON_LICENSE_DIR1  _T("D:\\Program Files\\MVTec\\HALCON-12.0\\license")

LARGE_INTEGER g_Frequency;
LARGE_INTEGER g_BeginTime;
LARGE_INTEGER g_EndTime;

void  GetExePath(TCHAR *pPath)
{
	static TCHAR exeFullPath[MAX_PATH] = {0};
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);
	TCHAR *p = _tcsrchr(exeFullPath, _T('\\'));
	if (NULL!=p)
	{
		*p=0x00;
		_tcscpy(pPath,exeFullPath);
	}
}

void GetProcessMemory()
{
	HANDLE handle = GetCurrentProcess();
	PROCESS_MEMORY_COUNTERS pmc;

	GetProcessMemoryInfo(handle,&pmc,sizeof(pmc));
	DWORD size = pmc.WorkingSetSize/1024;
}

BOOL FolderExist(CString strPath)
{
	WIN32_FIND_DATA wfd;
	BOOL rValue = FALSE;
	HANDLE hFind = FindFirstFile(strPath, &wfd);
	if ((hFind!=INVALID_HANDLE_VALUE) &&
		(wfd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY))
	{
		rValue = TRUE;
	}
	FindClose(hFind);
	return rValue;
}

BOOL FileExist(CString strPath)
{
	return PathFileExists(strPath);
}

BOOL CreateFolder(CString strPath)
{
	SECURITY_ATTRIBUTES attrib;
	attrib.bInheritHandle = FALSE;
	attrib.lpSecurityDescriptor = NULL;
	attrib.nLength = sizeof(SECURITY_ATTRIBUTES);
	//上面定义的属性可以省略
	//直接使用return ::CreateDirectory(path, NULL);即可
	return ::CreateDirectory(strPath, &attrib);
}

void  OpenExplorerFolder(LPCTSTR  lpFolder)
{
	SHELLEXECUTEINFO ShExecInfo;
	memset( &ShExecInfo, 0, sizeof( SHELLEXECUTEINFO ) );
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = _T("Open");
	ShExecInfo.lpFile = _T("explorer.exe");        
	ShExecInfo.lpParameters =lpFolder;  
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_SHOWNORMAL;
	ShExecInfo.hInstApp = NULL; 
	ShellExecuteEx(&ShExecInfo);
}

void FileCopy(CString strSrcPath, CString strDestPath)
{}

void BeginTime()
{
	QueryPerformanceFrequency( &g_Frequency );
	QueryPerformanceCounter( &g_BeginTime );
}

double  EndTime()
{
	QueryPerformanceCounter(&g_EndTime);
	return double(g_EndTime.LowPart-g_BeginTime.LowPart)/double(g_Frequency.LowPart);
}

void CheckLicense()
{
	TCHAR szPath[MAX_PATH] = {0};
	GetExePath(szPath);
	CString strFilepath,strTemp;
	strFilepath = CString(szPath) + CString("\\*.*");
	HANDLE hFind;
	WIN32_FIND_DATA wfd;
	hFind = FindFirstFile(strFilepath,&wfd);
	if (INVALID_HANDLE_VALUE == hFind)	return;
	do
	{
		strFilepath = wfd.cFileName;
		int nFind = strFilepath.Find(_T("."));
		strTemp = strFilepath.Right(strFilepath.GetLength() - nFind);
		if (_T(".dat") == strTemp)
		{
			CString strSrcPath = szPath+CString("\\")+CString(wfd.cFileName);
			if (FolderExist(HALCON_LICENSE_DIR))
			{
				CString  strDestPath = HALCON_LICENSE_DIR+CString(_T("\\"))+CString(wfd.cFileName);
				FileCopy(strSrcPath,strDestPath);
				if (FileExist(strDestPath))
				{
// 					DeleteFileA(strSrcPath);
				}
			}
			else	if (FolderExist(HALCON_LICENSE_DIR1))
			{
				CString  strDestPath = HALCON_LICENSE_DIR1+CString(_T("\\"))+CString(wfd.cFileName);
				FileCopy(strSrcPath,strDestPath);
				if (FileExist(strDestPath))
				{
// 					DeleteFileA(strSrcPath);
				}
			}
			else	break;
		}
	}while(FindNextFile(hFind, &wfd));
}

CString  int2String(int val)
{
	CString str;
	str.Format("%d", val);
	return str;
}

CString  double2String(double val)
{
	CString str;
	str.Format("%.4f", val);
	return str;
}


CStatic*		  NewStatic(LPCTSTR lpszText, DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID  )
{
	CStatic *pStatic = new CStatic();
	pStatic->Create(lpszText, WS_CHILD | WS_VISIBLE|dwStyle, rect, pParentWnd, nID);
	return pStatic;
}

CEdit*		  NewEdit(DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID  )
{
	CEdit *pEdit = new CEdit();
	pEdit->Create(WS_CHILD | WS_VISIBLE|dwStyle, rect, pParentWnd, nID);
	return pEdit;
}


CButton*		  NewButton(LPCTSTR lpszText, DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	CButton* pButton = new CButton();
	pButton->Create(lpszText, WS_CHILD | WS_VISIBLE|dwStyle, rect, pParentWnd, nID);
	return pButton;
}

CSliderCtrl * NewSliderCtrl(DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	CSliderCtrl* pSliderCtrl = new CSliderCtrl();
	pSliderCtrl->Create( WS_CHILD | WS_VISIBLE|TBS_NOTICKS |TBS_HORZ|dwStyle, rect, pParentWnd, nID);
	return pSliderCtrl;
}

CComboBox * NewComboBox(DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	CComboBox* pComboBox= new CComboBox();
	pComboBox->Create( WS_CHILD | WS_VISIBLE|dwStyle, rect, pParentWnd, nID);
	return pComboBox;
}



CFont *NewFont()
{
	CFont *font = new CFont();
	font->CreateFontA(18,0,0,0,300,0,0,0,1,0,0,0,0,_T("微软雅黑"));
	return font;
}