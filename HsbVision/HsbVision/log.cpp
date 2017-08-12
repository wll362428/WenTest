#include "StdAfx.h"
#include "log.h"
TCHAR m_szFilePathName[MAX_PATH] = {0};
char buf[LOG_BUFFER_SIZE] = {0};

void CDebugLog::SetLogFilePath(TCHAR *szPath)
{
	if (szPath == NULL)
	{
		return;
	}
	m_bLogWriteFile = true;
	memset(m_szFilePathName,0,MAX_PATH);
	_tcsncpy(m_szFilePathName, szPath,_tcslen(szPath));

	SYSTEMTIME st;
	GetLocalTime(&st);
	TCHAR tempbuf[20];
	ZeroMemory(tempbuf,sizeof(tempbuf));
	wsprintf(tempbuf,_T("\\HsbDFIns%02d.log"),st.wDayOfWeek);
	_tcscat(m_szFilePathName,tempbuf);
}

CDebugLog::CDebugLog(void)
{
// 	InitializeCriticalSection(&m_criticalSection_log);
	m_bLogWriteFile = false;
//	wcscpy_s(m_szFilePathName, _countof(m_szFilePathName), DEBUG_LOG_FILE);
	m_hCom1 = INVALID_HANDLE_VALUE;
}

CDebugLog::CDebugLog(TCHAR *lpPath)
{
	m_bLogWriteFile = false;
	m_hCom1 = INVALID_HANDLE_VALUE;

	if (NULL != lpPath)
	{
		SetLogFilePath(lpPath);
	}
}

CDebugLog::~CDebugLog(void)
{
// 	DeleteCriticalSection(&m_criticalSection_log);
}
// void CDebugLog::WriteLog(const wchar_t* wstr, ...)
// {
// 	if (wstr == NULL)
// 		return;
// 	va_list arg_ptr;
// 	va_start(arg_ptr, wstr);
// 	TCHAR wbuf[LOG_BUFFER_SIZE];
// 	memset(wbuf,0,sizeof(wbuf));
// 	vswprintf( &wbuf[wcslen(wbuf)], wstr,arg_ptr);
// 	
// 	TRACE(L"%s\r\nL",wbuf);
// 	
// 	int wLen = WideCharToMultiByte(CP_ACP,0,wbuf,-1,NULL,0,NULL,NULL);
// 	if (wLen == 0)
// 	{
// 		return;
// 	}
// 	char* pTemp = new char[wLen];
// 	memset(pTemp,0,wLen);
// 	WideCharToMultiByte(CP_ACP,0,wbuf,-1,pTemp,wLen,NULL,NULL);
// 	if (wLen > 0)
// 	{
// 		WriteLog(pTemp);
// 	}
// 	delete []pTemp;
// 	pTemp = NULL;
// 	va_end(arg_ptr);
// }

void CDebugLog::WriteLog(const char* str, ...)
{
	if (str == NULL)
		return;
	Autolock autolock(&m_csLogLock);
	//m_csLogLock.Lock();
	va_list arg_ptr;
	va_start(arg_ptr, str);
	SYSTEMTIME st;
	GetLocalTime(&st);
	ZeroMemory(buf,LOG_BUFFER_SIZE);
	sprintf(buf,"[%04d/%02d/%02d %02d:%02d:%02d]",st.wYear,st.wMonth,st.wDay,st.wHour, st.wMinute, st.wSecond);
	vsprintf( &buf[strlen(buf)], str,arg_ptr);
	strcat_s( buf, sizeof(buf), "\r\n");
	
	if (m_bLogWriteFile)
	{
		CFile cfile;
		if (!cfile.Open(m_szFilePathName, CFile::modeCreate|CFile::modeReadWrite|CFile::modeNoTruncate,NULL))
		{
			TRACE("create log.txt fiald!!\r\n");
			//printf(L"%sL",buf);
			va_end(arg_ptr);
			//m_csLogLock.Unlock();
			return;
		}
		DWORD dwsize = GetFileSize(cfile.m_hFile,NULL);
		if (dwsize != 0xFFFFFFFF)
		{
			if(dwsize > 0x20000000)//512MB
			{
				cfile.Close();
				cfile.Remove(m_szFilePathName);
				if (!cfile.Open(m_szFilePathName, CFile::modeCreate|CFile::modeReadWrite|CFile::modeNoTruncate,NULL))
				{
					TRACE("create log.txt fiald!!1\r\n");
					//printf(L"%sL",buf);
					va_end(arg_ptr);
					//m_csLogLock.Unlock();
					return;
				}
			}
		}
		else
		{
			//TRACE(L"create log.txt fiald!!\r\nL");
// 			printf(L"%sL",buf);
			va_end(arg_ptr);
			//m_csLogLock.Unlock();
			return;
		}
		cfile.SeekToEnd();
		cfile.Write(buf,strlen(buf));
		cfile.Close();
	}
	else
	{
		if (m_hCom1 != INVALID_HANDLE_VALUE)
		{
			DWORD dwWrited;
			WriteFile(m_hCom1,buf,strlen(buf),&dwWrited,NULL);
		}
	}
	
	//printf(L"%sL",buf);
	va_end(arg_ptr);
	//m_csLogLock.Unlock();
}
void CDebugLog::OpenLog(LPCTSTR szPath)
{
	/*
	if (wcscmp(szPath, L"COM_OUTPUTL")== 0)
	{   
		m_hCom1 = CreateFile(_T(L"COM1:L"), GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 
						FILE_ATTRIBUTE_NORMAL, (HANDLE)INVALID_HANDLE_VALUE);

		DCB commParam;
		if(!GetCommState(m_hCom1,&commParam))     
		{          
			return ;  
		}   

		commParam.BaudRate = 115200;                  // 设置波特率     
		commParam.fBinary = TRUE;                   // 设置二进制模式，此处必须设置TRUE    
		commParam.fParity = TRUE;                   // 支持奇偶校验     
		commParam.ByteSize = 8;              // 数据位,范围:4-8     
		commParam.Parity = NOPARITY;                // 校验模式    
		commParam.StopBits = 0;              // 停止位     

		commParam.fOutxCtsFlow = FALSE;             // No CTS output flow control     
		commParam.fOutxDsrFlow = FALSE;             // No DSR output flow control     
		commParam.fDtrControl = DTR_CONTROL_ENABLE;    
		// DTR flow control type     
		commParam.fDsrSensitivity = FALSE;          // DSR sensitivity     
		commParam.fTXContinueOnXoff = TRUE;         // XOFF continues Tx     
		commParam.fOutX = FALSE;                    // No XON/XOFF out flow control     
		commParam.fInX = FALSE;                     // No XON/XOFF in flow control     
		commParam.fErrorChar = FALSE;               // Disable error replacement     
		commParam.fNull = FALSE;                    // Disable null stripping     
		commParam.fRtsControl = RTS_CONTROL_ENABLE;    
		// RTS flow control     
		commParam.fAbortOnError = FALSE;            // 当串口发生错误，并不终止串口读写    

		if(!SetCommState(m_hCom1, &commParam))   
		{   
			DWORD dw =GetLastError(); 
			TRACE(_T(L"SetCommState errorL"));           
			return ;   
		}   
	}
	else if(wcscmp(szPath, L"FILE_OUTPUTL")== 0)
	{
		TCHAR m_szDbFilePath[MAX_PATH];
		wmemset(m_szFilePathName, 0, MAX_PATH);
		GetModuleFileName(NULL, m_szFilePathName, MAX_PATH);
		(wcsrchr(m_szFilePathName, '\\'))[1] = 0;
		
		wcscat(m_szFilePathName, DEBUG_LOG_FILE);
		//wcscpy(m_szFilePathName,szPath);
		//wcscat(m_szFilePathName,DEBUG_LOG_FILE);
		m_bLogWriteFile = true;
	}
	//wcscpy(m_szFilePathName,szPath);
	//wcscat(m_szFilePathName,DEBUG_LOG_FILE);
	//;
	*/
}
void CDebugLog::CloseLog()
{
	CloseHandle(m_hCom1);
	m_hCom1 = INVALID_HANDLE_VALUE;
	m_bLogWriteFile = false;
}


char strLog[LOG_BUFFER_SIZE];
TCHAR wstrLog[LOG_BUFFER_SIZE];
void CDebugLog::WriteLogHex(const char * buf, int len) 
{
// 	if (m_hCom1 != INVALID_HANDLE_VALUE)
// 	{
// 		DWORD dwWrited;
// 		WriteFile(m_hCom1, buf, len, &dwWrited, NULL);
// 		return;
// 	}
// 	memset(strLog, 0, LOG_BUFFER_SIZE);
// 	wmemset(wstrLog,0,LOG_BUFFER_SIZE);
// 	if (len > LOG_BUFFER_SIZE)
// 	{
// 		len = LOG_BUFFER_SIZE/4;
// 	}
// 
// 	if (len * 3 > LOG_BUFFER_SIZE)
// 	{
// 		len = LOG_BUFFER_SIZE/4;
// 	}
// 	for(int i=0; i<len; i++)
// 	{
// 		char tmsg[4];
// 		TCHAR wMsg[4];
// 		int tvalue = (unsigned char)buf[i];
// 		sprintf(tmsg,L"%02xL",tvalue);
// 		strcat(strLog, tmsg);
// 		wsprintf(wMsg, L"%02xL",tvalue);
// 		wcscat(wstrLog,wMsg);
// 	}
// 	TRACE(L"%s\r\nL",wstrLog);
// 	WriteLog(strLog);
}
