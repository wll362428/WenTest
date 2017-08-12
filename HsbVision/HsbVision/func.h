
void GetExePath(TCHAR *pPath);
void GetProcessMemory();
BOOL FolderExist(CString strPath);
BOOL FileExist(CString strPath);
void  OpenExplorerFolder(LPCTSTR  lpFolder);

BOOL CreateFolder(CString strPath);
void FileCopy(CString strSrcPath, CString strDestPath);
void CheckLicense();
void BeginTime();
double EndTime();
CString  int2String(int val);
CString  double2String(double val);

CStatic*		  NewStatic(LPCTSTR lpszText, DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID);
CEdit*		  NewEdit( DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID );
CButton*	  NewButton(LPCTSTR lpszText, DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID);
CSliderCtrl * NewSliderCtrl(DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID);
CComboBox * NewComboBox(DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID);
// CWnd *NewLayers(Layers eLayers, LPCTSTR lpszText, DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID=0xffff);
CFont *NewFont();