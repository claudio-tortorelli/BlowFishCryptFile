// BlowFishCryptFile.h : main header file for the BLOWFISHCRYPTFILE application
//

#if !defined(AFX_BLOWFISHCRYPTFILE_H__D275C3C5_A581_4739_B465_AFA2F9941993__INCLUDED_)
#define AFX_BLOWFISHCRYPTFILE_H__D275C3C5_A581_4739_B465_AFA2F9941993__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBlowFishCryptFileApp:
// See BlowFishCryptFile.cpp for the implementation of this class
//

class CBlowFishCryptFileApp : public CWinApp
{
public:
	CBlowFishCryptFileApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBlowFishCryptFileApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBlowFishCryptFileApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BLOWFISHCRYPTFILE_H__D275C3C5_A581_4739_B465_AFA2F9941993__INCLUDED_)
