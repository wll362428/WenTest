#pragma once

class CLock
{
public:
	CLock(void);
	~CLock(void);
	void Lock();
	void Unlock();
protected:
	CRITICAL_SECTION m_criticalSection;
};

class Autolock{
public:
	Autolock(CLock *p)
	{
		m_plock = p;
		m_plock->Lock();
	}
	~Autolock()
	{
		m_plock->Unlock();	
	}
private:
	CLock *m_plock;
};