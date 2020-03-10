
// RemotePCProject.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CRemotePCProjectApp:
// See RemotePCProject.cpp for the implementation of this class
//

class CRemotePCProjectApp : public CWinApp
{
public:
	CRemotePCProjectApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CRemotePCProjectApp theApp;
