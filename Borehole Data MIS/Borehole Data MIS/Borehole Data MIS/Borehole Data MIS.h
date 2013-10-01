
// Borehole Data MIS.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
//#include "Prog.h"

// CBoreholeDataMISApp:
// See Borehole Data MIS.cpp for the implementation of this class
//

class CBoreholeDataMISApp : public CWinApp
{
public:
	CBoreholeDataMISApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CBoreholeDataMISApp theApp;