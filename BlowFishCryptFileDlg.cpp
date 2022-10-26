// BlowFishCryptFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BlowFishCryptFile.h"
#include "BlowFishCryptFileDlg.h"

#include "BlowFishFileCrypt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBlowFishCryptFileDlg dialog

CBlowFishCryptFileDlg::CBlowFishCryptFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBlowFishCryptFileDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBlowFishCryptFileDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBlowFishCryptFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBlowFishCryptFileDlg)	
	DDX_Control(pDX, IDC_CHECK_OVERWRITE, m_CheckOverWrite_Ctrl);
	DDX_Control(pDX, IDC_CHECK_KEY2, m_Checkkey2_Ctrl);
	DDX_Control(pDX, IDC_CHECK_KEY1, m_CheckKey1_Ctrl);
	DDX_Control(pDX, IDC_EDIT_FILE, m_EditFile_Ctrl);
	DDX_Control(pDX, IDC_CHECK_DECRIPT, m_CheckDecrypt_Ctrl);
	DDX_Control(pDX, IDC_CHECK_CRYPT, m_CheckCrypt_Ctrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBlowFishCryptFileDlg, CDialog)
	//{{AFX_MSG_MAP(CBlowFishCryptFileDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()	
	ON_BN_CLICKED(ID_BUTTON_DO, OnButtonDoIt)
	ON_BN_CLICKED(IDC_BUTTON_SFOGLIA, OnButtonSfoglia)
	ON_BN_CLICKED(IDC_CHECK_KEY1, OnCheckKey1)
	ON_BN_CLICKED(IDC_CHECK_KEY2, OnCheckKey2)
	ON_BN_CLICKED(IDC_CHECK_CRYPT, OnCheckCrypt)
	ON_BN_CLICKED(IDC_CHECK_DECRIPT, OnCheckDecript)
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBlowFishCryptFileDlg message handlers

BOOL CBlowFishCryptFileDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	
	m_CheckKey1_Ctrl.SetCheck(TRUE);
	m_CheckOverWrite_Ctrl.SetCheck(FALSE);
	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBlowFishCryptFileDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBlowFishCryptFileDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBlowFishCryptFileDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBlowFishCryptFileDlg::OnButtonSfoglia() 
{
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() != IDOK)
		return;

	m_EditFile_Ctrl.SetWindowText(dlg.GetPathName());	
}


void CBlowFishCryptFileDlg::OnCheckKey1() 
{
	if (m_Checkkey2_Ctrl.GetCheck())
		m_Checkkey2_Ctrl.SetCheck(FALSE);

	m_CheckKey1_Ctrl.SetCheck(TRUE);
}

void CBlowFishCryptFileDlg::OnCheckKey2() 
{
	if (m_CheckKey1_Ctrl.GetCheck())
		m_CheckKey1_Ctrl.SetCheck(FALSE);

	m_Checkkey2_Ctrl.SetCheck(TRUE);
}


void CBlowFishCryptFileDlg::OnCheckCrypt() 
{
	if (m_CheckDecrypt_Ctrl.GetCheck())
		m_CheckDecrypt_Ctrl.SetCheck(FALSE);

	m_CheckCrypt_Ctrl.SetCheck(TRUE);
	
}


void CBlowFishCryptFileDlg::OnCheckDecript() 
{
	if (m_CheckCrypt_Ctrl.GetCheck())
		m_CheckCrypt_Ctrl.SetCheck(FALSE);

	m_CheckDecrypt_Ctrl.SetCheck(TRUE);
}

void CBlowFishCryptFileDlg::OnButtonDoIt() 
{
	CString filePath;
	m_EditFile_Ctrl.GetWindowText(filePath);
	if (filePath.IsEmpty())
	{
		AfxMessageBox("Select a file", MB_ICONINFORMATION);
		return;
	}


	int numKey = 0;
	if (m_CheckKey1_Ctrl.GetCheck())
		numKey = 0;
	else
		numKey = 1;


	if (!m_CheckCrypt_Ctrl.GetCheck() && !m_CheckDecrypt_Ctrl.GetCheck())
	{
		AfxMessageBox("Select an action", MB_ICONINFORMATION);
		return;
	}

	BOOL bOverWrite = m_CheckOverWrite_Ctrl.GetCheck();
	if (bOverWrite)
	{
		if (IDNO == AfxMessageBox("Attention: overwrite is selected. It's potentially dangerous if you don't know what are you doing!\nProceed?", MB_YESNO))
			return;
	}


	CBlowFishFileCrypt blow(filePath.GetBuffer(0), numKey);

	if (m_CheckCrypt_Ctrl.GetCheck())
		blow.DoCrypt(bOverWrite);
	else
		blow.DoDecrypt(bOverWrite);
}
