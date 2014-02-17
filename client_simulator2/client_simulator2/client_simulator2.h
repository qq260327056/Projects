// client_simulator2.h : main header file for the client_simulator2 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Cclient_simulator2App:
// See client_simulator2.cpp for the implementation of this class
//

class Cclient_simulator2App : public CWinApp
{
public:
	Cclient_simulator2App();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Cclient_simulator2App theApp;