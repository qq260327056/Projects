// client_simulator.h : main header file for the client_simulator application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Cclient_simulatorApp:
// See client_simulator.cpp for the implementation of this class
//

class Cclient_simulatorApp : public CWinApp
{
public:
	Cclient_simulatorApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Cclient_simulatorApp theApp;