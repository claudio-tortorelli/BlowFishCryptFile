// BlowFishCryptFileDlg.h : header file
//

#if !defined(AFX_BLOWFISHCRYPTFILEDLG_H__9BC88D53_61DA_45B9_A36D_779326ADE9E3__INCLUDED_)
#define AFX_BLOWFISHCRYPTFILEDLG_H__9BC88D53_61DA_45B9_A36D_779326ADE9E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBlowFishCryptFileDlg dialog

class CBlowFishCryptFileDlg : public CDialog
{
// Construction
public:
	CBlowFishCryptFileDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBlowFishCryptFileDlg)
	enum { IDD = IDD_BLOWFISHCRYPTFILE_DIALOG };	
	CButton	m_CheckOverWrite_Ctrl;
	CButton	m_Checkkey2_Ctrl;
	CButton	m_CheckKey1_Ctrl;
	CEdit	m_EditFile_Ctrl;
	CButton	m_CheckDecrypt_Ctrl;
	CButton	m_CheckCrypt_Ctrl;	
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBlowFishCryptFileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBlowFishCryptFileDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	
	afx_msg void OnButtonDoIt();	
	afx_msg void OnCheckDecript();
	afx_msg void OnCheckCrypt();
	afx_msg void OnCheckKey2();
	afx_msg void OnCheckKey1();
	afx_msg void OnButtonSfoglia();	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BLOWFISHCRYPTFILEDLG_H__9BC88D53_61DA_45B9_A36D_779326ADE9E3__INCLUDED_)
