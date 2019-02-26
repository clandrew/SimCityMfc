// SimCity2.h : main header file for the SIMCITY2 application
//

#if !defined(AFX_SIMCITY2_H__DA3D8C69_9FC1_44F0_98C4_44FD4478A9BC__INCLUDED_)
#define AFX_SIMCITY2_H__DA3D8C69_9FC1_44F0_98C4_44FD4478A9BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSimCity2App:
// See SimCity2.cpp for the implementation of this class
//

class CSimCity2App : public CWinApp
{
public:
	CSimCity2App();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimCity2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSimCity2App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMCITY2_H__DA3D8C69_9FC1_44F0_98C4_44FD4478A9BC__INCLUDED_)
