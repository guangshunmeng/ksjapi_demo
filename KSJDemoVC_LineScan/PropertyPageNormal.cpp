// PropertyPageNormal.cpp : 实现文件
//

#include "stdafx.h"
#include "KSJDemoVC_LineScan.h"
#include "PropertyPageNormal.h"
#include "afxdialogex.h"


// CPropertyPageNormal 对话框

IMPLEMENT_DYNAMIC(CPropertyPageNormal, CPropertyPage)

CPropertyPageNormal::CPropertyPageNormal()
	: CPropertyPage(CPropertyPageNormal::IDD)
	, m_bInitial(false)
{

}

CPropertyPageNormal::~CPropertyPageNormal()
{
}

void CPropertyPageNormal::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPropertyPageNormal, CPropertyPage)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &CPropertyPageNormal::OnBnClickedButtonApply)
	ON_EN_CHANGE(IDC_EDIT_GAIN_RED, &CPropertyPageNormal::OnEnChangeEditGainRed)
	ON_EN_CHANGE(IDC_EDIT_GAIN_GREEN, &CPropertyPageNormal::OnEnChangeEditGainGreen)
	ON_EN_CHANGE(IDC_EDIT_GAIN_BLUE, &CPropertyPageNormal::OnEnChangeEditGainBlue)
	ON_EN_CHANGE(IDC_EDIT_EXPOSURE_TIME_MS, &CPropertyPageNormal::OnEnChangeEditExposureTimeMs)
	ON_EN_CHANGE(IDC_EDIT_EXPOSURE_LINES, &CPropertyPageNormal::OnEnChangeEditExposureLines)
END_MESSAGE_MAP()


// CPropertyPageNormal 消息处理程序


void CPropertyPageNormal::OnDestroy()
{
	CPropertyPage::OnDestroy();

	// TODO:  在此处添加消息处理程序代码
}


BOOL CPropertyPageNormal::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	CPropertyPage::OnInitDialog();
	CSpinButtonCtrl * pSpinCtrl = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_EXPOSURE_TIME_MS);
	pSpinCtrl->SetBuddy(GetDlgItem(IDC_EDIT_EXPOSURE_TIME_MS));
	pSpinCtrl->SetBase(10);

	//CEdit *pEditCtrlExposureLines = ((CEdit*)GetDlgItem(IDC_EDIT_EXPOSURE_LINES));
	pSpinCtrl = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_EXPOSURE_LINES);
	pSpinCtrl->SetBuddy(GetDlgItem(IDC_EDIT_EXPOSURE_LINES));
	pSpinCtrl->SetBase(10);

	pSpinCtrl = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_GAIN_RED);
	pSpinCtrl->SetBuddy(GetDlgItem(IDC_EDIT_GAIN_RED));
	pSpinCtrl->SetBase(10);

	pSpinCtrl = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_GAIN_GREEN);
	pSpinCtrl->SetBuddy(GetDlgItem(IDC_EDIT_GAIN_GREEN));
	pSpinCtrl->SetBase(10);

	pSpinCtrl = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_GAIN_BLUE);
	pSpinCtrl->SetBuddy(GetDlgItem(IDC_EDIT_GAIN_BLUE));
	pSpinCtrl->SetBase(10);

	int nSupport = 0;
	m_pCam->QueryFunction(KSJ_SUPPORT_MULTI_FRAMES, &nSupport);
	m_bMultiFrame = (nSupport == TRUE ? TRUE : FALSE);

	// FOV
	int nColStart;
	int nRowStart;
	int nColSize;
	int nRowSize;
	KSJ_ADDRESSMODE ColAddressMode;
	KSJ_ADDRESSMODE RowAddressMode;
	int nRet = 0;
	if (m_bMultiFrame)
	{
		GetDlgItem(IDC_EDIT_MULTIFRAME_NUM)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_MULTIFRAME_NUM)->ShowWindow(SW_SHOW);
		unsigned short wMultiFrameNum;
		m_pCam->PreviewGetFieldOfViewEx(&nColStart, &nRowStart, &nColSize, &nRowSize, &ColAddressMode, &RowAddressMode, &wMultiFrameNum);
		m_pCam->CaptureSetFieldOfViewEx(nColStart, nRowStart, nColSize, nRowSize, ColAddressMode, RowAddressMode, wMultiFrameNum);
		SetDlgItemInt(IDC_EDIT_MULTIFRAME_NUM, wMultiFrameNum);
	}
	else
	{
		GetDlgItem(IDC_EDIT_MULTIFRAME_NUM)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_MULTIFRAME_NUM)->ShowWindow(SW_HIDE);
		m_pCam->PreviewGetFieldOfView(&nColStart, &nRowStart, &nColSize, &nRowSize, &ColAddressMode, &RowAddressMode);
		m_pCam->CaptureSetFieldOfView(nColStart, nRowStart, nColSize, nRowSize, ColAddressMode, RowAddressMode);
	}

	SetDlgItemInt(IDC_EDIT_COL_START, nColStart);
	SetDlgItemInt(IDC_EDIT_ROW_START, nRowStart);
	SetDlgItemInt(IDC_EDIT_COL_SIZE, nColSize);
	SetDlgItemInt(IDC_EDIT_ROW_SIZE, nRowSize);

	m_pCam->AWAIBA_IsUsed(&m_bUsed);

	int nMin = 0;
	int nMax = 0;
	int nCur = 0;
	if (m_bUsed)
	{
		m_pCam->AWAIBA_GetSegmentNum(&nMax);
		pSpinCtrl = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_GAIN_RED);
		pSpinCtrl->SetRange32(nMin, nMax - 1);
		pSpinCtrl->SetPos32(nCur);
		int nGain = 0;
		m_pCam->AWAIBA_GetGainRange(nCur, &nMin, &nMax);
		nRet = m_pCam->AWAIBA_GetGain(nCur, &nGain);
		pSpinCtrl = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_GAIN_GREEN);
		pSpinCtrl->SetRange32(nMin, nMax);

		pSpinCtrl->SetPos32(nGain);
		GetDlgItem(IDC_STATIC_GAIN3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_GAIN_BLUE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SPIN_GAIN_BLUE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECK_SAMETO)->ShowWindow(SW_HIDE);
		((CStatic*)GetDlgItem(IDC_STATIC_GAIN1))->SetWindowText("Segment:");
		((CStatic*)GetDlgItem(IDC_STATIC_GAIN2))->SetWindowText("Gain:");
	}
	else
	{
		m_pCam->GetParamRange(KSJ_RED, &nMin, &nMax);
		m_pCam->GetParam(KSJ_RED, &nCur);
		SetDlgItemInt(IDC_EDIT_GAIN_RED, nCur);
		pSpinCtrl = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_GAIN_RED);
		pSpinCtrl->SetRange32(nMin, nMax);
		pSpinCtrl->SetPos32(nCur);

		m_pCam->GetParamRange(KSJ_GREEN, &nMin, &nMax);
		m_pCam->GetParam(KSJ_GREEN, &nCur);
		SetDlgItemInt(IDC_EDIT_GAIN_GREEN, nCur);
		pSpinCtrl = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_GAIN_GREEN);
		pSpinCtrl->SetRange32(nMin, nMax);
		pSpinCtrl->SetPos32(nCur);

		m_pCam->GetParamRange(KSJ_BLUE, &nMin, &nMax);
		m_pCam->GetParam(KSJ_BLUE, &nCur);
		SetDlgItemInt(IDC_EDIT_GAIN_BLUE, nCur);
		pSpinCtrl = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_GAIN_BLUE);
		pSpinCtrl->SetRange32(nMin, nMax);
		pSpinCtrl->SetPos32(nCur);

		GetDlgItem(IDC_STATIC_GAIN3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_GAIN_BLUE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_SPIN_GAIN_BLUE)->ShowWindow(SW_SHOW);
		((CStatic*)GetDlgItem(IDC_CHECK_SAMETO))->ShowWindow(SW_SHOW);
		((CStatic*)GetDlgItem(IDC_STATIC_GAIN1))->SetWindowText("RED:");
		((CStatic*)GetDlgItem(IDC_STATIC_GAIN2))->SetWindowText("GREED:");
	}

	m_pCam->GetParamRange(KSJ_EXPOSURE, &nMin, &nMax);
	m_pCam->GetParam(KSJ_EXPOSURE, &nCur);
	SetDlgItemInt(IDC_EDIT_EXPOSURE_TIME_MS, nCur);
	pSpinCtrl = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_EXPOSURE_TIME_MS);
	pSpinCtrl->SetRange32(nMin, nMax);
	pSpinCtrl->SetPos32(nCur);

	m_pCam->GetParamRange(KSJ_EXPOSURE_LINES, &nMin, &nMax);
	m_pCam->GetParam(KSJ_EXPOSURE_LINES, &nCur);
	SetDlgItemInt(IDC_EDIT_EXPOSURE_LINES, nCur);
	pSpinCtrl = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_EXPOSURE_LINES);
	pSpinCtrl->SetRange32(nMin, nMax);
	pSpinCtrl->SetPos32(nCur);
	m_bInitial = true;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE

}


void CPropertyPageNormal::OnBnClickedButtonApply()
{
	int nColStart;
	int nRowStart;
	int nColSize;
	int nRowSize;

	KSJ_ADDRESSMODE ColAddressMode = KSJ_SKIPNONE;
	KSJ_ADDRESSMODE RowAddressMode = KSJ_SKIPNONE;

	nColStart = GetDlgItemInt(IDC_EDIT_COL_START);
	nRowStart = GetDlgItemInt(IDC_EDIT_ROW_START);
	nColSize = GetDlgItemInt(IDC_EDIT_COL_SIZE);
	nRowSize = GetDlgItemInt(IDC_EDIT_ROW_SIZE);

	if (m_bMultiFrame)
	{
		unsigned short wMultiFrameNum = GetDlgItemInt(IDC_EDIT_MULTIFRAME_NUM);
		m_pCam->PreviewSetFieldOfViewEx(nColStart, nRowStart, nColSize, nRowSize, ColAddressMode, RowAddressMode, wMultiFrameNum);
		m_pCam->CaptureSetFieldOfViewEx(nColStart, nRowStart, nColSize, nRowSize, ColAddressMode, RowAddressMode, wMultiFrameNum);
		m_pCam->PreviewGetFieldOfViewEx(&nColStart, &nRowStart, &nColSize, &nRowSize, &ColAddressMode, &RowAddressMode, &wMultiFrameNum);
		SetDlgItemInt(IDC_EDIT_MULTIFRAME_NUM, wMultiFrameNum);
	}
	else
	{
		m_pCam->PreviewSetFieldOfView(nColStart, nRowStart, nColSize, nRowSize, ColAddressMode, RowAddressMode);
		m_pCam->CaptureSetFieldOfView(nColStart, nRowStart, nColSize, nRowSize, ColAddressMode, RowAddressMode);
		m_pCam->PreviewGetFieldOfView(&nColStart, &nRowStart, &nColSize, &nRowSize, &ColAddressMode, &RowAddressMode);
	}

	SetDlgItemInt(IDC_EDIT_COL_START, nColStart);
	SetDlgItemInt(IDC_EDIT_ROW_START, nRowStart);
	SetDlgItemInt(IDC_EDIT_COL_SIZE, nColSize);
	SetDlgItemInt(IDC_EDIT_ROW_SIZE, nRowSize);
}


void CPropertyPageNormal::OnEnChangeEditGainRed()
{
	if (!m_bInitial) return;
	int nGain = 0;
	if (m_bUsed)
	{
		m_nSegIndex = GetDlgItemInt(IDC_EDIT_GAIN_RED);
		m_pCam->AWAIBA_GetGain(m_nSegIndex, &nGain);
		SetDlgItemInt(IDC_EDIT_GAIN_GREEN, nGain);
	}
	else
	{

		nGain = GetDlgItemInt(IDC_EDIT_GAIN_RED);

		BOOL bSame = ((CButton*)GetDlgItem(IDC_CHECK_SAMETO))->GetCheck();
		if (bSame)
		{
			m_pCam->SetParam(KSJ_RED, nGain);
			m_pCam->SetParam(KSJ_GREEN, nGain);
			m_pCam->SetParam(KSJ_BLUE, nGain);
			SetDlgItemInt(IDC_EDIT_GAIN_GREEN, nGain);
			SetDlgItemInt(IDC_EDIT_GAIN_BLUE, nGain);
		}
		else
		{
			m_pCam->SetParam(KSJ_RED, nGain);
		}
	}
}


void CPropertyPageNormal::OnEnChangeEditGainGreen()
{
	if (!m_bInitial) return;
	int nGain = 0;
	nGain = GetDlgItemInt(IDC_EDIT_GAIN_GREEN);

	if (m_bUsed)
	{
		m_pCam->AWAIBA_SetGain(m_nSegIndex, nGain);
	}
	else
	{
		m_pCam->SetParam(KSJ_GREEN, nGain);
	}
}


void CPropertyPageNormal::OnEnChangeEditGainBlue()
{
	if (!m_bInitial) return;

	int nGain = 0;
	nGain = GetDlgItemInt(IDC_EDIT_GAIN_BLUE);
	m_pCam->SetParam(KSJ_BLUE, nGain);
}


void CPropertyPageNormal::OnEnChangeEditExposureTimeMs()
{
	if (!m_bInitial) return;

	int nExposureTimeMs = 0;
	nExposureTimeMs = GetDlgItemInt(IDC_EDIT_EXPOSURE_TIME_MS);
	m_pCam->SetParam(KSJ_EXPOSURE, nExposureTimeMs);

	int nCur = 0;
	m_pCam->GetParam(KSJ_EXPOSURE_LINES, &nCur);
}


void CPropertyPageNormal::OnEnChangeEditExposureLines()
{
	if (!m_bInitial) return;

	int nExposureLines = 0;
	nExposureLines = GetDlgItemInt(IDC_EDIT_EXPOSURE_LINES);
	m_pCam->SetParam(KSJ_EXPOSURE_LINES, nExposureLines);

	int nCur = 0;
	m_pCam->GetParam(KSJ_EXPOSURE, &nCur);
}
