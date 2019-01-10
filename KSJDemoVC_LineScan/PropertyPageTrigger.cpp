// PropertyPageTrigger.cpp : 实现文件
//

#include "stdafx.h"
#include "KSJDemoVC_LineScan.h"
#include "PropertyPageTrigger.h"
#include "afxdialogex.h"


// CPropertyPageTrigger 对话框

IMPLEMENT_DYNAMIC(CPropertyPageTrigger, CPropertyPage)

CPropertyPageTrigger::CPropertyPageTrigger()
	: CPropertyPage(CPropertyPageTrigger::IDD)
	, m_bInitial(false)
{

}

CPropertyPageTrigger::~CPropertyPageTrigger()
{
}

void CPropertyPageTrigger::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPropertyPageTrigger, CPropertyPage)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO_TIMEOUT, &CPropertyPageTrigger::OnCbnSelchangeComboTimeout)
	ON_BN_CLICKED(IDC_CHECK_RECOVER, &CPropertyPageTrigger::OnBnClickedCheckRecover)
	ON_CBN_SELCHANGE(IDC_COMBO_MODE, &CPropertyPageTrigger::OnCbnSelchangeComboMode)
	ON_CBN_SELCHANGE(IDC_COMBO_METHOD, &CPropertyPageTrigger::OnCbnSelchangeComboMethod)
	ON_EN_CHANGE(IDC_EDIT_DELAY, &CPropertyPageTrigger::OnEnChangeEditDelay)
	ON_EN_CHANGE(IDC_EDIT_FIXED_FRAME_RATE_HW, &CPropertyPageTrigger::OnEnChangeEditFixedFrameRateHw)
	ON_BN_CLICKED(IDC_CHECK_INVERT, &CPropertyPageTrigger::OnBnClickedCheckInvert)
	ON_BN_CLICKED(IDC_CHECK_FLASH_ENABLE, &CPropertyPageTrigger::OnBnClickedCheckFlashEnable)
END_MESSAGE_MAP()


// CPropertyPageTrigger 消息处理程序


void CPropertyPageTrigger::OnDestroy()
{
	CPropertyPage::OnDestroy();

	// TODO:  在此处添加消息处理程序代码
}


BOOL CPropertyPageTrigger::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	bool bEnable;
	bool bInvert;
	int nMode;
	m_pCam->FlashControlGet(&bEnable, &bInvert, &nMode);
	((CButton*)GetDlgItem(IDC_CHECK_FLASH_ENABLE))->SetCheck(bEnable);
	((CButton*)GetDlgItem(IDC_CHECK_INVERT))->SetCheck(bInvert);

	CComboBox    *pComboBox = NULL;
	int i = 0;
	// Time Out
	pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_TIMEOUT);
	pComboBox->ResetContent();
	unsigned long nTimeOut = 0;
	m_pCam->CaptureGetTimeOut(&nTimeOut);
	for (i = 0; i < sizeof(g_szTimeOut) / sizeof(TCHAR*); i++)
	{
		pComboBox->AddString(g_szTimeOut[i]);
		if (nTimeOut == g_nTimeOut[i])
		{
			pComboBox->SetCurSel(i);
		}
	}

	bool bRecover = true;
	m_pCam->CaptureSetRecover(bRecover);
	((CButton*)GetDlgItem(IDC_CHECK_RECOVER))->SetCheck(bRecover);

	pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_MODE);
	pComboBox->ResetContent();

	for (i = 0; i < g_nTriggerMode; i++)
	{
		pComboBox->AddString(g_szTriggerMode[i]);
	}

	KSJ_TRIGGERMODE    TriggerMode;
	m_pCam->TriggerModeGet(&TriggerMode);

	pComboBox->SetCurSel((int)TriggerMode);



	pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_METHOD);
	pComboBox->ResetContent();

	for (i = 0; i < g_nTriggerMethod; i++)
	{
		pComboBox->AddString(g_szTriggerMethod[i]);
	}

	KSJ_TRIGGERMETHOD    TriggerMethod;
	m_pCam->TriggerMethodGet(&TriggerMethod);
	pComboBox->SetCurSel((int)TriggerMethod);

	CSpinButtonCtrl * pSpinCtrlTriggerDelay = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_DELAY);
	pSpinCtrlTriggerDelay->SetBuddy(GetDlgItem(IDC_EDIT_DELAY));
	pSpinCtrlTriggerDelay->SetBase(10);

	int nMin = 0;
	int nMax = 0;
	int nCur = 0;
	m_pCam->TriggerDelayGetRange((WORD*)&nMin, (WORD*)&nMax);
	pSpinCtrlTriggerDelay->SetRange32(nMin, nMax);
	m_pCam->TriggerDelayGet((WORD*)&nCur);
	pSpinCtrlTriggerDelay->SetPos32(nCur);
	SetDlgItemInt(IDC_EDIT_DELAY, nCur);

	CSpinButtonCtrl * pSpinCtrlFixedFrameRateHw = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_FIXED_FRAME_RATE_HW);
	pSpinCtrlFixedFrameRateHw->SetBuddy(GetDlgItem(IDC_EDIT_FIXED_FRAME_RATE_HW));
	pSpinCtrlFixedFrameRateHw->SetBase(10);
	pSpinCtrlFixedFrameRateHw->SetRange32(1, 760000);    // Frame Rate is decided by Exposure, aoi, so it's difficult to get range, use can test it.

	float fFixedFrameRate = 0.0f;
	m_pCam->GetFixedFrameRateEx(&fFixedFrameRate);
	pSpinCtrlFixedFrameRateHw->SetPos32((int)fFixedFrameRate);

	m_bInitial = true;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CPropertyPageTrigger::OnCbnSelchangeComboTimeout()
{
	CComboBox *pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_TIMEOUT);
	int nIndex = pComboBox->GetCurSel();
	if (nIndex == CB_ERR)    return;

	m_pCam->CaptureSetTimeOut(g_nTimeOut[nIndex]);
}


void CPropertyPageTrigger::OnBnClickedCheckRecover()
{
	BOOL bRecover = ((CButton*)GetDlgItem(IDC_CHECK_RECOVER))->GetCheck();

	m_pCam->CaptureSetRecover(bRecover == BST_CHECKED ? TRUE : FALSE);
}


void CPropertyPageTrigger::OnCbnSelchangeComboMode()
{
	CComboBox *pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_MODE);
	int nIndex = pComboBox->GetCurSel();
	if (nIndex == CB_ERR)    return;
	m_pCam->PreviewStart(false);
	Sleep(10);
	m_pCam->TriggerModeSet((KSJ_TRIGGERMODE)nIndex);

	KSJ_TRIGGERMODE    TriggerMode;
	m_pCam->TriggerModeGet(&TriggerMode);

	pComboBox->SetCurSel((int)TriggerMode);
	m_pCam->PreviewStart(true);

	if (TriggerMode != KSJ_TRIGGER_FIXFRAMERATE)
	{
		GetDlgItem(IDC_EDIT_FIXED_FRAME_RATE_HW)->EnableWindow(FALSE);
		GetDlgItem(IDC_SPIN_FIXED_FRAME_RATE_HW)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_FIXED_FRAME_RATE_HW)->EnableWindow(TRUE);
		GetDlgItem(IDC_SPIN_FIXED_FRAME_RATE_HW)->EnableWindow(TRUE);
	}
}


void CPropertyPageTrigger::OnCbnSelchangeComboMethod()
{
	CComboBox *pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_METHOD);
	int nIndex = pComboBox->GetCurSel();
	if (nIndex == CB_ERR)    return;
	m_pCam->PreviewStart(false);
	Sleep(10);
	m_pCam->TriggerMethodSet((KSJ_TRIGGERMETHOD)nIndex);

	KSJ_TRIGGERMETHOD    TriggerMethod;
	m_pCam->TriggerMethodGet(&TriggerMethod);

	pComboBox->SetCurSel((int)TriggerMethod);
	m_pCam->PreviewStart(true);
}


void CPropertyPageTrigger::OnEnChangeEditDelay()
{
	if (!m_bInitial) return;

	int nValue = GetDlgItemInt(IDC_EDIT_DELAY);
	m_pCam->TriggerDelaySet(nValue);
}


void CPropertyPageTrigger::OnEnChangeEditFixedFrameRateHw()
{
	if (!m_bInitial) return;

	int nValue = GetDlgItemInt(IDC_EDIT_FIXED_FRAME_RATE_HW);
	m_pCam->SetFixedFrameRateEx(nValue);
}

void CPropertyPageTrigger::OnBnClickedCheckInvert()
{
	SetFlash();
}


void CPropertyPageTrigger::OnBnClickedCheckFlashEnable()
{
	SetFlash();
}

void CPropertyPageTrigger::SetFlash()
{
	BOOL bEnable = ((CButton*)GetDlgItem(IDC_CHECK_FLASH_ENABLE))->GetCheck();
	BOOL bInvert = ((CButton*)GetDlgItem(IDC_CHECK_INVERT))->GetCheck();
	m_pCam->FlashControlSet(bEnable == BST_CHECKED ? TRUE : FALSE, bInvert == BST_CHECKED ? TRUE : FALSE, 0);
}
