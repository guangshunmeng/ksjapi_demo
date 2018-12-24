#include "stdafx.h"
#include "KSJDemoVC.h"
#include "KSJDemoVCDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define _USER_CODE 1

//////////////////////////////////////////////////////////////////////////////////////////////
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


//////////////////////////////////////////////////////////////////////////////////////////////
void CKSJDemoVCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PREVIEWWND1, m_SnapStatic1);
	DDX_Control(pDX, IDC_STATIC_PREVIEWWND2, m_SnapStatic2);
	DDX_Control(pDX, IDC_STATIC_PREVIEWWND3, m_SnapStatic3);
	DDX_Control(pDX, IDC_STATIC_PREVIEWWND4, m_SnapStatic4);
}

BEGIN_MESSAGE_MAP(CKSJDemoVCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_STARTPREVIEW, &CKSJDemoVCDlg::OnBnClickedButtonStartpreview)
	ON_BN_CLICKED(IDC_BUTTON_CHANGETRIGGERMODE, &CKSJDemoVCDlg::OnBnClickedButtonChangetriggermode)
END_MESSAGE_MAP()

void CKSJDemoVCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CKSJDemoVCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CKSJDemoVCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
CKSJDemoVCDlg::CKSJDemoVCDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CKSJDemoVCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

#ifndef _USER_CODE
	KSJ_Init();
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////
void CKSJDemoVCDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

#ifdef _USER_CODE
	m_KSJCamera.CloseCamera();
#else
	KSJ_Init();
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////
BOOL CKSJDemoVCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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

	KSJ_LogSet(true, NULL);

#ifdef _USER_CODE
	m_KSJCamera.ConnectCamera();

	m_KSJCamera.SetExposureTime(0, 200);
	m_KSJCamera.SetExposureTime(1, 200);
	m_KSJCamera.SetExposureTime(2, 200);
	m_KSJCamera.SetExposureTime(3, 200);

	m_KSJCamera.SetPreviewPos(0, m_SnapStatic1.m_hWnd, CRect(0, 0, 460, 460));
	m_KSJCamera.SetPreviewPos(1, m_SnapStatic2.m_hWnd, CRect(0, 0, 460, 460));
	m_KSJCamera.SetPreviewPos(2, m_SnapStatic3.m_hWnd, CRect(0, 0, 460, 460));
	m_KSJCamera.SetPreviewPos(3, m_SnapStatic4.m_hWnd, CRect(0, 0, 460, 460));
#else
	KSJ_CaptureSetFieldOfView(0, 0, 0, 1024, 768, KSJ_SKIPNONE, KSJ_SKIPNONE);
	//KSJ_CaptureSetFieldOfView(0, 0, 0, 752, 480, KSJ_SKIPNONE, KSJ_SKIPNONE);
	KSJ_PreviewSetFieldOfView(0, 0, 0, 752, 480, KSJ_SKIPNONE, KSJ_SKIPNONE);
	KSJ_PreviewSetPos(0, m_SnapStatic1.m_hWnd, 0, 0, 752, 480);
	KSJ_PreviewStart(0, true);
	KSJ_CaptureSetTimeOut(0, 2000);
	KSJ_CaptureSetRecover(0, true);
	KSJ_TriggerModeSet(0, KSJ_TRIGGER_SOFTWARE);
#endif

	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CKSJDemoVCDlg::OnBnClickedButtonStartpreview()
{
#ifdef _USER_CODE
	m_KSJCamera.CloseCamera();
	m_KSJCamera.ConnectCamera();

	m_KSJCamera.SetExposureTime(0, 200);
	m_KSJCamera.SetExposureTime(1, 200);
	m_KSJCamera.SetExposureTime(2, 200);
	m_KSJCamera.SetExposureTime(3, 200);

	m_KSJCamera.SetPreviewPos(0, m_SnapStatic1.m_hWnd, CRect(0, 0, 460, 460));
	m_KSJCamera.SetPreviewPos(1, m_SnapStatic2.m_hWnd, CRect(0, 0, 460, 460));
	m_KSJCamera.SetPreviewPos(2, m_SnapStatic3.m_hWnd, CRect(0, 0, 460, 460));
	m_KSJCamera.SetPreviewPos(3, m_SnapStatic4.m_hWnd, CRect(0, 0, 460, 460));
#endif
}


void CKSJDemoVCDlg::OnBnClickedButtonChangetriggermode()
{
#ifdef _USER_CODE
	KSJ_TRIGGERMODE TriggerMode;
	KSJ_TriggerModeGet(0, &TriggerMode);
	if (TriggerMode == KSJ_TRIGGER_SOFTWARE)
	{
		KSJ_TriggerModeSet(0, KSJ_TRIGGER_INTERNAL);
		KSJ_TriggerModeSet(1, KSJ_TRIGGER_INTERNAL);
		KSJ_TriggerModeSet(2, KSJ_TRIGGER_INTERNAL);
		KSJ_TriggerModeSet(3, KSJ_TRIGGER_INTERNAL);
	}
	else
	{
		KSJ_TriggerModeSet(0, KSJ_TRIGGER_SOFTWARE);
		KSJ_TriggerModeSet(1, KSJ_TRIGGER_SOFTWARE);
		KSJ_TriggerModeSet(2, KSJ_TRIGGER_SOFTWARE);
		KSJ_TriggerModeSet(3, KSJ_TRIGGER_SOFTWARE);
	}

	//KSJ_TriggerModeSet(0, KSJ_TRIGGER_SOFTWARE);
#else
	KSJ_TRIGGERMODE TriggerMode;
	KSJ_TriggerModeGet(0, &TriggerMode);
	if (TriggerMode == KSJ_TRIGGER_SOFTWARE) KSJ_TriggerModeSet(0, KSJ_TRIGGER_INTERNAL);
	else                                     KSJ_TriggerModeSet(0, KSJ_TRIGGER_SOFTWARE);

	//KSJ_TriggerModeSet(0, KSJ_TRIGGER_SOFTWARE);
#endif
}
