// client_simulator3.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Cclient_simulator3App:
// See client_simulator3.cpp for the implementation of this class
//

class Cclient_simulator3App : public CWinApp
{
public:
	Cclient_simulator3App();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Cclient_simulator3App theApp;