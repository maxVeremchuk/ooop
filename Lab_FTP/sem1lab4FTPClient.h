
// sem1lab4FTPClient.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Csem1lab4FTPClientApp:
// See sem1lab4FTPClient.cpp for the implementation of this class
//

class Csem1lab4FTPClientApp : public CWinApp
{
public:
	Csem1lab4FTPClientApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Csem1lab4FTPClientApp theApp;