
// KSJDemoVC_CameraManagerClassDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KSJDemoVC_CameraManagerClass.h"
#include "KSJDemoVC_CameraManagerClassDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CKSJDemoVC_CameraManagerClassDlg �Ի���



CKSJDemoVC_CameraManagerClassDlg::CKSJDemoVC_CameraManagerClassDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CKSJDemoVC_CameraManagerClassDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_CameraManager = new CKSJCameraManager;
}

CKSJDemoVC_CameraManagerClassDlg::~CKSJDemoVC_CameraManagerClassDlg()
{
	delete m_CameraManager;
}

void CKSJDemoVC_CameraManagerClassDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CKSJDemoVC_CameraManagerClassDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT_EXTIME1, &CKSJDemoVC_CameraManagerClassDlg::OnEnChangeEditExtime1)
	ON_EN_CHANGE(IDC_EDIT_EXLINES1, &CKSJDemoVC_CameraManagerClassDlg::OnEnChangeEditExlines1)
	ON_EN_CHANGE(IDC_EDIT_GAIN1, &CKSJDemoVC_CameraManagerClassDlg::OnEnChangeEditGain1)
	ON_BN_CLICKED(IDC_CHECK_PREVIEWSTART1, &CKSJDemoVC_CameraManagerClassDlg::OnBnClickedCheckPreviewstart1)
	ON_BN_CLICKED(IDC_CHECK_PAUSE1, &CKSJDemoVC_CameraManagerClassDlg::OnBnClickedCheckPause1)
	ON_EN_CHANGE(IDC_EDIT_EXTIME2, &CKSJDemoVC_CameraManagerClassDlg::OnEnChangeEditExtime2)
	ON_EN_CHANGE(IDC_EDIT_EXLINES2, &CKSJDemoVC_CameraManagerClassDlg::OnEnChangeEditExlines2)
	ON_EN_CHANGE(IDC_EDIT_GAIN2, &CKSJDemoVC_CameraManagerClassDlg::OnEnChangeEditGain2)
	ON_BN_CLICKED(IDC_CHECK_PREVIEWSTART2, &CKSJDemoVC_CameraManagerClassDlg::OnBnClickedCheckPreviewstart2)
	ON_BN_CLICKED(IDC_CHECK_PAUSE2, &CKSJDemoVC_CameraManagerClassDlg::OnBnClickedCheckPause2)
	ON_EN_CHANGE(IDC_EDIT_EXTIME3, &CKSJDemoVC_CameraManagerClassDlg::OnEnChangeEditExtime3)
	ON_EN_CHANGE(IDC_EDIT_EXLINES3, &CKSJDemoVC_CameraManagerClassDlg::OnEnChangeEditExlines3)
	ON_EN_CHANGE(IDC_EDIT_GAIN3, &CKSJDemoVC_CameraManagerClassDlg::OnEnChangeEditGain3)
	ON_BN_CLICKED(IDC_CHECK_PREVIEWSTART3, &CKSJDemoVC_CameraManagerClassDlg::OnBnClickedCheckPreviewstart3)
	ON_BN_CLICKED(IDC_CHECK_PAUSE3, &CKSJDemoVC_CameraManagerClassDlg::OnBnClickedCheckPause3)
END_MESSAGE_MAP()


// CKSJDemoVC_CameraManagerClassDlg ��Ϣ�������

BOOL CKSJDemoVC_CameraManagerClassDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	UpdateUI();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CKSJDemoVC_CameraManagerClassDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CKSJDemoVC_CameraManagerClassDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CKSJDemoVC_CameraManagerClassDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CKSJDemoVC_CameraManagerClassDlg::UpdateUI()
{
	int nValue;
	m_CameraManager->GetExposureTime(1, &nValue);
	SetDlgItemInt(IDC_EDIT_EXTIME1, nValue);
	m_CameraManager->GetExposureLines(1, &nValue);
	SetDlgItemInt(IDC_EDIT_EXLINES1, nValue);
	m_CameraManager->GetGain(1, &nValue);
	SetDlgItemInt(IDC_EDIT_GAIN1, nValue);

	m_CameraManager->GetExposureTime(2, &nValue);
	SetDlgItemInt(IDC_EDIT_EXTIME2, nValue);
	m_CameraManager->GetExposureLines(2, &nValue);
	SetDlgItemInt(IDC_EDIT_EXLINES2, nValue);
	m_CameraManager->GetGain(2, &nValue);
	SetDlgItemInt(IDC_EDIT_GAIN2, nValue);

	m_CameraManager->GetExposureTime(3, &nValue);
	SetDlgItemInt(IDC_EDIT_EXTIME3, nValue);
	m_CameraManager->GetExposureLines(3, &nValue);
	SetDlgItemInt(IDC_EDIT_EXLINES3, nValue);
	m_CameraManager->GetGain(3, &nValue);
	SetDlgItemInt(IDC_EDIT_GAIN3, nValue);

	m_CameraManager->ConnectView(1, GetDlgItem(IDC_STATIC_SERIALS1));
	m_CameraManager->ConnectView(2, GetDlgItem(IDC_STATIC_SERIALS2));
	m_CameraManager->ConnectView(3, GetDlgItem(IDC_STATIC_SERIALS3));
}


void CKSJDemoVC_CameraManagerClassDlg::OnEnChangeEditExtime1()
{
	m_CameraManager->SetExposureTime(1, GetDlgItemInt(IDC_EDIT_EXTIME1));
}


void CKSJDemoVC_CameraManagerClassDlg::OnEnChangeEditExlines1()
{
	m_CameraManager->SetExposureTime(1, GetDlgItemInt(IDC_EDIT_EXLINES1));
}


void CKSJDemoVC_CameraManagerClassDlg::OnEnChangeEditGain1()
{
	m_CameraManager->SetExposureTime(1, GetDlgItemInt(IDC_EDIT_GAIN1));
}


void CKSJDemoVC_CameraManagerClassDlg::OnBnClickedCheckPreviewstart1()
{
	BOOL bCheck = ((CButton*)GetDlgItem(IDC_CHECK_PREVIEWSTART1))->GetCheck();
	m_CameraManager->ConnectCamera(1, bCheck);
}

void CKSJDemoVC_CameraManagerClassDlg::OnBnClickedCheckPause1()
{
	BOOL bCheck = ((CButton*)GetDlgItem(IDC_CHECK_PREVIEWSTART1))->GetCheck();
	m_CameraManager->PauseCamera(1, bCheck);
}

void CKSJDemoVC_CameraManagerClassDlg::OnEnChangeEditExtime2()
{
	m_CameraManager->SetExposureTime(2, GetDlgItemInt(IDC_EDIT_EXTIME2));
}


void CKSJDemoVC_CameraManagerClassDlg::OnEnChangeEditExlines2()
{
	m_CameraManager->SetExposureTime(2, GetDlgItemInt(IDC_EDIT_EXLINES2));
}


void CKSJDemoVC_CameraManagerClassDlg::OnEnChangeEditGain2()
{
	m_CameraManager->SetExposureTime(2, GetDlgItemInt(IDC_EDIT_GAIN2));
}


void CKSJDemoVC_CameraManagerClassDlg::OnBnClickedCheckPreviewstart2()
{
	BOOL bCheck = ((CButton*)GetDlgItem(IDC_CHECK_PREVIEWSTART2))->GetCheck();
	m_CameraManager->ConnectCamera(2, bCheck);
}


void CKSJDemoVC_CameraManagerClassDlg::OnBnClickedCheckPause2()
{
	BOOL bCheck = ((CButton*)GetDlgItem(IDC_CHECK_PREVIEWSTART2))->GetCheck();
	m_CameraManager->PauseCamera(2, bCheck);
}


void CKSJDemoVC_CameraManagerClassDlg::OnEnChangeEditExtime3()
{
	m_CameraManager->SetExposureTime(3, GetDlgItemInt(IDC_EDIT_EXTIME3));
}


void CKSJDemoVC_CameraManagerClassDlg::OnEnChangeEditExlines3()
{
	m_CameraManager->SetExposureTime(3, GetDlgItemInt(IDC_EDIT_EXLINES3));
}


void CKSJDemoVC_CameraManagerClassDlg::OnEnChangeEditGain3()
{
	m_CameraManager->SetExposureTime(3, GetDlgItemInt(IDC_EDIT_GAIN3));
}


void CKSJDemoVC_CameraManagerClassDlg::OnBnClickedCheckPreviewstart3()
{
	BOOL bCheck = ((CButton*)GetDlgItem(IDC_CHECK_PREVIEWSTART3))->GetCheck();
	m_CameraManager->ConnectCamera(3, bCheck);
}


void CKSJDemoVC_CameraManagerClassDlg::OnBnClickedCheckPause3()
{
	BOOL bCheck = ((CButton*)GetDlgItem(IDC_CHECK_PREVIEWSTART3))->GetCheck();
	m_CameraManager->PauseCamera(3, bCheck);
}



