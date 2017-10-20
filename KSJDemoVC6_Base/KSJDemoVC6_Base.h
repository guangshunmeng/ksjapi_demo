// KSJDemoVC6_Base.h : main header file for the KSJDEMOVC6_BASE application
//

#if !defined(AFX_KSJDEMOVC6_BASE_H__5CD5A160_157F_4B5E_8CBA_AD20EDF70F26__INCLUDED_)
#define AFX_KSJDEMOVC6_BASE_H__5CD5A160_157F_4B5E_8CBA_AD20EDF70F26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CKSJDemoVC6_BaseApp:
// See KSJDemoVC6_Base.cpp for the implementation of this class
//

class CKSJDemoVC6_BaseApp : public CWinApp
{
public:
	CKSJDemoVC6_BaseApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKSJDemoVC6_BaseApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CKSJDemoVC6_BaseApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KSJDEMOVC6_BASE_H__5CD5A160_157F_4B5E_8CBA_AD20EDF70F26__INCLUDED_)
