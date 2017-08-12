#include "StdAfx.h"
#include "lock.h"

CLock::CLock(void)
{
	InitializeCriticalSection(&m_criticalSection);
}

CLock::~CLock(void)
{
	DeleteCriticalSection(&m_criticalSection);
}
void CLock::Lock()
{
	EnterCriticalSection(&m_criticalSection);
}

void CLock::Unlock()
{
	LeaveCriticalSection(&m_criticalSection);
}