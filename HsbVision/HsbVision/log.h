#pragma once
#include "lock.h"

//#define EMULATOR_TEST

#define DEBUG_LOG_FILE         _T("log.txt")

#define LOG_BUFFER_SIZE    4096

class CDebugLog
{
public:
	CDebugLog(void);
	CDebugLog(TCHAR *lpPath);

	 ~CDebugLog(void);
	//void WriteLog(const wchar_t* wstr, ...);		// 写日志(宽字节版本)
	void WriteLog(const char* str, ...);			// 写日志(多字节版本)
	void WriteLogHex(const char * buf, int len);
	void OpenLog(LPCTSTR szPath =_T("COM_OUTPUT"));
	void CloseLog();
	void SetLogFilePath(TCHAR* szPath);
private:
	bool m_bLogWriteFile;
// 	CRITICAL_SECTION m_criticalSection_log;
	CLock m_csLogLock;
	HANDLE m_hCom1;
	
};
