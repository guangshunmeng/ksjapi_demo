
// KSJDemoVC_LineScanDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "KSJDemoVC_LineScan.h"
#include "KSJDemoVC_LineScanDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CKSJDemoVC_LineScanDlg 对话框



CKSJDemoVC_LineScanDlg::CKSJDemoVC_LineScanDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CKSJDemoVC_LineScanDlg::IDD, pParent)
, m_nDeviceNum(0)
,m_nDeviceCurSel(-1)
, m_nComIndex(-1)
,m_nTriggerCount(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	KSJ_Init();
	KSJCOM_Init();
	m_PageNormal.m_psp.dwFlags &= ~(PSP_HASHELP);
	m_PageTrigger.m_psp.dwFlags &= ~(PSP_HASHELP);
	InitialIni(NULL);
	m_pCam = new CKSJCamClass;
}

void CKSJDemoVC_LineScanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CKSJDemoVC_LineScanDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, &CKSJDemoVC_LineScanDlg::OnCbnSelchangeComboType)
	ON_CBN_SELCHANGE(IDC_COMBO_COMS, &CKSJDemoVC_LineScanDlg::OnCbnSelchangeComboComs)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, &CKSJDemoVC_LineScanDlg::OnBnClickedButtonRefresh)
	ON_BN_CLICKED(IDC_BUTTON_START, &CKSJDemoVC_LineScanDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CKSJDemoVC_LineScanDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_CAMERA_SET, &CKSJDemoVC_LineScanDlg::OnBnClickedCameraSet)
	ON_BN_CLICKED(IDC_CTRLBOARD_SET, &CKSJDemoVC_LineScanDlg::OnBnClickedCtrlboardSet)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO_BAUD, &CKSJDemoVC_LineScanDlg::OnCbnSelchangeComboBaud)
	ON_CBN_SELCHANGE(IDC_COMBO_SIZE, &CKSJDemoVC_LineScanDlg::OnCbnSelchangeComboSize)
	ON_CBN_SELCHANGE(IDC_COMBO_PARITY, &CKSJDemoVC_LineScanDlg::OnCbnSelchangeComboParity)
	ON_CBN_SELCHANGE(IDC_COMBO_STOP, &CKSJDemoVC_LineScanDlg::OnCbnSelchangeComboStop)
	ON_MESSAGE(WM_TRIGGER, &CKSJDemoVC_LineScanDlg::OnMsgSetTrigger)
	ON_BN_CLICKED(IDCANCEL, &CKSJDemoVC_LineScanDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


void CKSJDemoVC_LineScanDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if (m_pKSJCtrlBoardDlg != NULL) delete m_pKSJCtrlBoardDlg;
	WriteComParam();
	delete m_pCam;
	m_pCam = NULL;
	CloseIni();
	KSJCOM_UnInit();
	KSJ_UnInit();
}

// CKSJDemoVC_LineScanDlg 消息处理程序

BOOL CKSJDemoVC_LineScanDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	m_pKSJCtrlBoardDlg = new CKSJCtrlBoardDlg;

	ReadComParam();
	OnBnClickedButtonRefresh();
	UpdateUI();
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CKSJDemoVC_LineScanDlg::UpdateDeviceList()
{
	KSJ_UnInit();
	KSJ_Init();

	CComboBox    *pComboBox = NULL;
	pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_TYPE);
	pComboBox->ResetContent();

	m_nDeviceNum = KSJ_DeviceGetCount();

	if (m_nDeviceNum == 0)
	{
		m_nDeviceCurSel = -1;
		return;
	}

	if (m_nDeviceCurSel >= m_nDeviceNum)
	{
		m_nDeviceCurSel = 0;
	}

	for (int i = 0; i < m_nDeviceNum; i++)
	{
		m_DeviceInfo[i].nIndex = i;
		// KSJ_DeviceGetInformation( i, &(m_DeviceInfo[i].DeviceType), &(m_DeviceInfo[i].nSerials), &(m_DeviceInfo[i].wFirmwareVersion) );
		KSJ_DeviceGetInformationEx(i, &(m_DeviceInfo[i].DeviceType), &(m_DeviceInfo[i].nSerials), &(m_DeviceInfo[i].wFirmwareVersion), &(m_DeviceInfo[i].wFpgaVersion));

		BYTE btMajVersion = (m_DeviceInfo[i].wFirmwareVersion & 0xFF00) >> 8;		// 得到主版本号
		BYTE btMinVersion = m_DeviceInfo[i].wFirmwareVersion & 0x00FF;				// 得到副版本号

		BYTE btFpgaMajVersion = (m_DeviceInfo[i].wFpgaVersion & 0xFF00) >> 8;		// 得到主版本号
		BYTE btFpgaMinVersion = m_DeviceInfo[i].wFpgaVersion & 0x00FF;				// 得到副版本号

		char  szMenuItem[256] = { 0 };
		sprintf(szMenuItem, _T("Index(%d)-Type(%s)-Serials(%d)-FwVer(%d.%d)-FpgaVer(%d.%d)"), i, g_szDeviceType[m_DeviceInfo[i].DeviceType], m_DeviceInfo[i].nSerials, btMajVersion, btMinVersion, btFpgaMajVersion, btFpgaMinVersion);
		pComboBox->AddString(szMenuItem);
	}

	pComboBox->SetCurSel(m_nDeviceCurSel);
}

void CKSJDemoVC_LineScanDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CKSJDemoVC_LineScanDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CKSJDemoVC_LineScanDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CKSJDemoVC_LineScanDlg::OnCbnSelchangeComboType()
{
	CComboBox *pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_TYPE);
	m_nDeviceCurSel = pComboBox->GetCurSel();
	if (m_nDeviceCurSel == CB_ERR)    return;
	if (m_pCam->GetDeviceIndex() != m_nDeviceCurSel || (!m_pCam->IsOpen()))
	{
		HWND   hPreviewWnd = ((CStatic*)GetDlgItem(IDC_VIEW))->m_hWnd;
		RECT   rtPreviewWndClient;
		((CStatic*)GetDlgItem(IDC_VIEW))->GetClientRect(&rtPreviewWndClient);

		m_pCam->Preview(hPreviewWnd, rtPreviewWndClient, false);
		m_pCam->Initial(m_nDeviceCurSel);
		m_pCam->Preview(hPreviewWnd, rtPreviewWndClient, true);
	}
}


void CKSJDemoVC_LineScanDlg::OnCbnSelchangeComboComs()
{
	if (m_nComIndex != -1)
	{
		KSJCOM_Close(m_nComIndex);
	}

	CComboBox    *pComboBox;
	pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_COMS);
	m_nComIndex = pComboBox->GetCurSel();
	if (CB_ERR == m_nComIndex)    return;

	KSJCOM_Open(m_nComIndex, m_nComBaud, m_nComBytesSize, m_nComStopBits, m_nComParity);
	KSJCOM_SetTimeOut(m_nComIndex, 1000, 1000);
	m_pKSJCtrlBoardDlg->m_nComIndex = m_nComIndex;
	m_pKSJCtrlBoardDlg->SetType();
	m_pKSJCtrlBoardDlg->m_Speed = GetDlgItem(IDC_EDIT_SPEED);
}


void CKSJDemoVC_LineScanDlg::OnBnClickedButtonRefresh()
{
	KSJCOM_UnInit();
	KSJCOM_Init();

	CComboBox    *pComboBox;
	int i;

	// 串口
	pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_COMS);
	pComboBox->ResetContent();

	int nComNum = KSJCOM_GetCount();

	TCHAR   szComs[64] = { '\0' };
	_stprintf_s(szComs, _T("%d COM Found:"), nComNum);
	((CStatic*)GetDlgItem(IDC_COMBO_COMS))->SetWindowText(szComs);

	for (i = 0; i<nComNum; i++)
	{
		TCHAR    szComName[256] = { '\0' };
		KSJCOM_GetInfo(i, szComName);
		pComboBox->AddString(szComName);
	}

	if (nComNum == 0)
		m_nComIndex = -1;

	if (m_nComIndex > nComNum - 1)
		m_nComIndex = 0;

	pComboBox->SetCurSel(m_nComIndex);

	UpdateDeviceList();
}

VOID WINAPI PREVIEWCALLBACK(unsigned char *pImageData, int nWidth, int nHeight, int nBitCount, void *lpContext)
{
	CKSJDemoVC_LineScanDlg *pVCDemoDlg = (CKSJDemoVC_LineScanDlg *)lpContext;
	pVCDemoDlg->PreviewCallback();
	
}

void CKSJDemoVC_LineScanDlg::PreviewCallback()
{
	m_nTriggerCount++;
	PostMessage(WM_TRIGGER, 0, 0);
}

LRESULT CKSJDemoVC_LineScanDlg::OnMsgSetTrigger(WPARAM wParam, LPARAM lParam)
{
	TCHAR   szText[64] = { 0 };
	sprintf_s(szText, _T("%d"), m_nTriggerCount);
	GetDlgItem(IDC_EDIT_TRIGGER_COUNT)->SetWindowText(szText);
	return 0;
}

void CKSJDemoVC_LineScanDlg::OnBnClickedButtonStart()
{
	if (m_nDeviceCurSel == -1 || m_nDeviceCurSel == -1) return;
	if (m_pKSJCtrlBoardDlg->GetSafeHwnd())
	{
		GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_COMS)->EnableWindow(FALSE);
		KSJ_TRIGGERMODE TriggerMode;
		KSJ_TriggerModeGet(m_nDeviceCurSel, &TriggerMode);
		if (TriggerMode == KSJ_TRIGGER_EXTERNAL)
		{
			m_nTriggerCount = 0;
			KSJ_PreviewSetCallback(m_nDeviceCurSel, PREVIEWCALLBACK, this);
		}

		m_pKSJCtrlBoardDlg->OnBnClickedCheckStart(TRUE);
	}
	else
	{
		MessageBox("请打开控制板设置界面");
	}
}


void CKSJDemoVC_LineScanDlg::OnBnClickedButtonStop()
{
	if (m_nDeviceCurSel == -1 || m_nDeviceCurSel == -1) return;
	if (m_pKSJCtrlBoardDlg->GetSafeHwnd())
	{
		GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_TYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_COMS)->EnableWindow(TRUE);
		KSJ_TRIGGERMODE TriggerMode;
		KSJ_TriggerModeGet(m_nDeviceCurSel, &TriggerMode);
		if (TriggerMode == KSJ_TRIGGER_EXTERNAL) KSJ_PreviewSetCallback(m_nDeviceCurSel, NULL, this);
		m_pKSJCtrlBoardDlg->OnBnClickedCheckStart(FALSE);
		KSJ_EmptyFrameBuffer(m_nDeviceCurSel);
	}
	else
	{
		MessageBox("请打开控制板设置界面");
	}
}


void CKSJDemoVC_LineScanDlg::OnBnClickedCameraSet()
{
	if (m_nDeviceCurSel == -1)
	{
		MessageBox("请选择相机");
		return;
	}

	HWND hwndSheetSettings = m_SheetSettings.GetSafeHwnd();
	if (!hwndSheetSettings)
	{
		CPropertyPageNormal  *pPageNormal = new CPropertyPageNormal();
		//CPropertyPageImage  *pPageImage = new CPropertyPageImage();
		CPropertyPageTrigger  *pPageTrigger = new CPropertyPageTrigger();
		//CPropertyPageMatrix  *pPageMatrix = new CPropertyPageMatrix();
		m_SheetSettings.AddPage(pPageNormal);
		//m_SheetSettings.AddPage(pPageImage);
		m_SheetSettings.AddPage(pPageTrigger);
		//m_SheetSettings.AddPage(pPageMatrix);

		pPageNormal->m_pCam = m_pCam;
		//pPageImage->m_pCam = m_pCam;
		pPageTrigger->m_pCam = m_pCam;
		//pPageMatrix->m_pCam = m_pCam;

		m_SheetSettings.Create(this, WS_SYSMENU | WS_POPUP | WS_CAPTION | DS_MODALFRAME | DS_CONTEXTHELP | WS_VISIBLE | WS_MINIMIZEBOX, 0);
		m_SheetSettings.SetWindowText(_T("Settings"));
	}
	else
	{
		m_SheetSettings.BringWindowToTop();
	}
}


void CKSJDemoVC_LineScanDlg::OnBnClickedCtrlboardSet()
{
	if (m_nComIndex == -1)
	{
		MessageBox("请选择串口");
		return;
	}

	if (!m_pKSJCtrlBoardDlg->GetSafeHwnd())
	{
		m_pKSJCtrlBoardDlg->Create(IDD_KSJCTRLBOARD_DIALOG, this);
	}

	m_pKSJCtrlBoardDlg->ShowWindow(SW_SHOW);
}

void CKSJDemoVC_LineScanDlg::UpdateUI()
{
	CComboBox    *pComboBox;
	pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_BAUD);
	pComboBox->ResetContent();
	int nIndex = 0;
	CString szBaud[8] = { "300", "600", "1200", "2400", "4800", "9600", "19200", "38400" };
	for (int i = 0; i < 8; i++)
	{
		pComboBox->AddString(szBaud[i]);
		if (m_nComBaud == atoi(szBaud[i]))
		{
			nIndex = i;
		}
	}

	pComboBox->SetCurSel(nIndex);

	nIndex = 0;
	pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_SIZE);
	pComboBox->ResetContent();
	CString szSize[5] = { "4", "5", "6", "7", "8" };
	for (int i = 0; i < 5; i++)
	{
		pComboBox->AddString(szSize[i]);
		if (m_nComBytesSize == atoi(szSize[i]))
		{
			nIndex = i;
		}
	}

	pComboBox->SetCurSel(nIndex);

	pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_PARITY);
	pComboBox->ResetContent();
	CString szParity[5] = { "None", "Odd", "Even", "Mark", "Space" };
	for (int i = 0; i < 5; i++)
	{
		pComboBox->AddString(szParity[i]);
	}

	pComboBox->SetCurSel(m_nComParity);

	pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_STOP);
	pComboBox->ResetContent();
	CString szStop[3] = { "1", "1.5", "2" };
	for (int i = 0; i < 3; i++)
	{
		pComboBox->AddString(szStop[i]);
	}

	pComboBox->SetCurSel(m_nComStopBits);
}


void CKSJDemoVC_LineScanDlg::ReadComParam()
{
	KSJINI_GetDWORD(g_hKSJIni, _T("COM"), _T("ComBaud"), 115200, (DWORD*)&m_nComBaud);
	KSJINI_GetDWORD(g_hKSJIni, _T("COM"), _T("ComBytesSize"), 8, (DWORD*)&m_nComBytesSize);
	KSJINI_GetDWORD(g_hKSJIni, _T("COM"), _T("ComStopBits"), 0, (DWORD*)&m_nComStopBits);
	KSJINI_GetDWORD(g_hKSJIni, _T("COM"), _T("ComParity"), 0, (DWORD*)&m_nComParity);
}


void CKSJDemoVC_LineScanDlg::WriteComParam()
{
	KSJINI_SetInt(g_hKSJIni, _T("COM"), _T("ComBaud"), m_nComBaud);
	KSJINI_SetInt(g_hKSJIni, _T("COM"), _T("ComBytesSize"), m_nComBytesSize);
	KSJINI_SetInt(g_hKSJIni, _T("COM"), _T("ComStopBits"), m_nComStopBits);
	KSJINI_SetInt(g_hKSJIni, _T("COM"), _T("ComParity"), m_nComParity);
}


void CKSJDemoVC_LineScanDlg::OnCbnSelchangeComboBaud()
{
	CComboBox    *pComboBox;
	CString strTemp;
	pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_BAUD);
	pComboBox->GetWindowText(strTemp);
	m_nComBaud = atoi(strTemp);
}


void CKSJDemoVC_LineScanDlg::OnCbnSelchangeComboSize()
{
	CComboBox    *pComboBox;
	CString strTemp;
	pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_SIZE);
	pComboBox->GetWindowText(strTemp);
	m_nComBytesSize = atoi(strTemp);
}


void CKSJDemoVC_LineScanDlg::OnCbnSelchangeComboParity()
{
	CComboBox    *pComboBox;
	pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_PARITY);
	m_nComParity = pComboBox->GetCurSel();
}


void CKSJDemoVC_LineScanDlg::OnCbnSelchangeComboStop()
{
	CComboBox    *pComboBox;
	pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_STOP);
	m_nComStopBits = pComboBox->GetCurSel();
}



void CKSJDemoVC_LineScanDlg::OnBnClickedCancel()
{
	HWND   hPreviewWnd = ((CStatic*)GetDlgItem(IDC_VIEW))->m_hWnd;
	RECT   rtPreviewWndClient;
	((CStatic*)GetDlgItem(IDC_VIEW))->GetClientRect(&rtPreviewWndClient);
	m_pCam->Preview(hPreviewWnd, rtPreviewWndClient, false);
	CDialogEx::OnCancel();
}
