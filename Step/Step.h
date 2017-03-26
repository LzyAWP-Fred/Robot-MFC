
// Step.h : main header file for the Step application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CStepApp:
// See Step.cpp for the implementation of this class
//

class CStepApp : public CWinAppEx
{
public:
	CStepApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CStepApp theApp;
