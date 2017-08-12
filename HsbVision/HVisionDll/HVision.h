// HVision.h : main header file for the HVision DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CHVisionWindowApp
// See HVision.cpp for the implementation of this class
//

class CHVisionApp : public CWinApp
{
public:
	CHVisionApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
