// KSJCtrlBoardDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "KSJDemoVC_LineScan.h"
#include "KSJCtrlBoardDlg.h"
#include "afxdialogex.h"

#define TIMERID_SPEED 1
// CKSJCtrlBoardDlg 对话框

IMPLEMENT_DYNAMIC(CKSJCtrlBoardDlg, CDialogEx)



void CKSJCtrlBoardDlg::ReadIni()
{
	KSJINI_GetDWORD(g_hKSJIni, _T("TRIGGER"), _T("TriggerModeIndex"), 0, (DWORD*)&m_nTriggerModeIndex);
	KSJINI_GetDWORD(g_hKSJIni, _T("TRIGGER"), _T("InputSourceIndex"), 0, (DWORD*)&m_nInputSourceIndex);
	KSJINI_GetDWORD(g_hKSJIni, _T("TRIGGER"), _T("TriggerMethodIndex"), 0, (DWORD*)&m_nTriggerMethodIndex);

	KSJINI_GetDWORD(g_hKSJIni, _T("TRIGGER"), _T("OutputFreq"), 1, (DWORD*)&m_wOutputFreq);
	KSJINI_GetDWORD(g_hKSJIni, _T("TRIGGER"), _T("OutputPulseNum"), 1, (DWORD*)&m_wOutputPulseNum);
	KSJINI_GetBOOL(g_hKSJIni, _T("TRIGGER"), _T("Infinite"), FALSE, &m_bInfinite);

	KSJINI_GetDWORD(g_hKSJIni, _T("TRIGGER"), _T("DelayModeIndex"), 0, (DWORD*)&m_nDelayModeIndex);
	KSJINI_GetDWORD(g_hKSJIni, _T("TRIGGER"), _T("DelayCountMethodIndex"), 0, (DWORD*)&m_nDelayCountMethodIndex);
	KSJINI_GetDWORD(g_hKSJIni, _T("TRIGGER"), _T("OutputChannelIndex"), 1, (DWORD*)&m_nOutputChannelIndex);

	KSJINI_GetDWORD(g_hKSJIni, _T("TRIGGER"), _T("DelayCount"), 0, (DWORD*)&m_wDelayCount);
	KSJINI_GetDWORD(g_hKSJIni, _T("TRIGGER"), _T("DelayTime"), 0, (DWORD*)&m_wDelayTime );
	m_wDelayTime *= 10;

	KSJINI_GetDWORD(g_hKSJIni, _T("TRIGGER"), _T("MultiFrames"), 0, (DWORD*)&g_nMultiFrames);
	KSJINI_GetDWORD(g_hKSJIni, _T("TRIGGER"), _T("LineTriggerPusles"), 0, (DWORD*)&m_nLineTriggerPusles);

	TCHAR szText[16] = { 0 };
	KSJINI_GetDWORD(g_hKSJIni, _T("MODE1"), _T("EncoderResolution"), 0, (DWORD*)&m_nEncoderResolution1);
	KSJINI_GetString(g_hKSJIni, _T("MODE1"), _T("CoderDiameter"), _T("0.0"), szText);
	m_fCoderDiameter1 = _tstof(szText);

	KSJINI_GetDWORD(g_hKSJIni, _T("MODE2"), _T("EncoderResolution"), 0, (DWORD*)&m_nEncoderResolution2);
	KSJINI_GetString(g_hKSJIni, _T("MODE2"), _T("CoderDiameter"), _T("0.0"), szText);
	m_fCoderDiameter2 = _tstof(szText);
}


void CKSJCtrlBoardDlg::WriteIni()
{
	KSJINI_SetInt(g_hKSJIni, _T("TRIGGER"), _T("TriggerModeIndex"), m_nTriggerModeIndex);
	KSJINI_SetInt(g_hKSJIni, _T("TRIGGER"), _T("InputSourceIndex"), m_nInputSourceIndex);
	KSJINI_SetInt(g_hKSJIni, _T("TRIGGER"), _T("TriggerMethodIndex"), m_nTriggerMethodIndex);

	KSJINI_SetInt(g_hKSJIni, _T("TRIGGER"), _T("OutputFreq"), m_wOutputFreq);

	KSJINI_SetInt(g_hKSJIni, _T("TRIGGER"), _T("OutputPulseNum"), m_wOutputPulseNum);
	KSJINI_SetBOOL(g_hKSJIni, _T("TRIGGER"), _T("Infinite"), m_bInfinite);

	KSJINI_SetInt(g_hKSJIni, _T("TRIGGER"), _T("OutputChannelIndex"), m_nOutputChannelIndex);

	KSJINI_SetInt(g_hKSJIni, _T("TRIGGER"), _T("DelayModeIndex"), m_nDelayModeIndex);
	KSJINI_SetInt(g_hKSJIni, _T("TRIGGER"), _T("DelayCountMethodIndex"), m_nDelayCountMethodIndex);

	KSJINI_SetInt(g_hKSJIni, _T("TRIGGER"), _T("DelayCount"), m_wDelayCount);
	KSJINI_SetInt(g_hKSJIni, _T("TRIGGER"), _T("DelayTime"), m_wDelayTime / 10);

	KSJINI_SetInt(g_hKSJIni, _T("TRIGGER"), _T("MultiFrames"), g_nMultiFrames);
	KSJINI_SetInt(g_hKSJIni, _T("TRIGGER"), _T("LineTriggerPusles"), m_nLineTriggerPusles);

	TCHAR szText[16] = { 0 };
	_stprintf_s(szText, _T("%f"), m_fCoderDiameter1);
	KSJINI_SetString(g_hKSJIni, _T("MODE1"), _T("CoderDiameter"), szText);
	KSJINI_SetInt(g_hKSJIni, _T("MODE1"), _T("EncoderResolution"), m_nEncoderResolution1);

	_stprintf_s(szText, _T("%f"), m_fCoderDiameter2);
	KSJINI_SetString(g_hKSJIni, _T("MODE2"), _T("CoderDiameter"), szText);
	KSJINI_SetInt(g_hKSJIni, _T("MODE2"), _T("EncoderResolution"), m_nEncoderResolution2);
	
}

CKSJCtrlBoardDlg::CKSJCtrlBoardDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CKSJCtrlBoardDlg::IDD, pParent)
{

	m_CtrlBoardType = KSJ_CONTROL_BOARD_UNKNOWN;

	for (int i = 0; i < UNO_OUTPUT_CHANNEL_NUM; i++)
	{
		memset(&m_UNO_Command[i], 0, sizeof(m_UNO_Command[i]));
		m_UNO_Command[i].ucPre = UNO_PROTOCOL_PRE;
		m_UNO_Command[i].ucChannel = i;
		m_UNO_Command[i].ucEnd = UNO_PROTOCOL_END;
	}

	m_bInitial = false;
	m_bStart = false;
	m_nTimer = 0;
	m_bAdjust = false;
	m_bSlider = true;
	m_bEdit = true;
}

CKSJCtrlBoardDlg::~CKSJCtrlBoardDlg()
{
}

void CKSJCtrlBoardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CKSJCtrlBoardDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_OUTPUT_CHANNEL, &CKSJCtrlBoardDlg::OnCbnSelchangeComboOutputChannel)
	ON_CBN_SELCHANGE(IDC_COMBO_TRIGGER_MODE, &CKSJCtrlBoardDlg::OnCbnSelchangeComboTriggerMode)
	ON_CBN_SELCHANGE(IDC_COMBO_INPUT_SOURCE, &CKSJCtrlBoardDlg::OnCbnSelchangeComboInputSource)
	ON_CBN_SELCHANGE(IDC_COMBO_TRIGGER_METHOD, &CKSJCtrlBoardDlg::OnCbnSelchangeComboTriggerMethod)
	ON_EN_CHANGE(IDC_EDIT_OUTPUT_FREQ, &CKSJCtrlBoardDlg::OnEnChangeEditOutputFreq)
	ON_EN_CHANGE(IDC_EDIT_OUTPUT_NUM, &CKSJCtrlBoardDlg::OnEnChangeEditOutputNum)
	ON_CBN_SELCHANGE(IDC_COMBO_DELAY_MODE, &CKSJCtrlBoardDlg::OnCbnSelchangeComboDelayMode)
	ON_EN_CHANGE(IDC_EDIT_DELAY_TIME, &CKSJCtrlBoardDlg::OnEnChangeEditDelayTime)
	ON_CBN_SELCHANGE(IDC_COMBO_DELAY_COUNT_MOTHED, &CKSJCtrlBoardDlg::OnCbnSelchangeComboDelayCountMothed)
	ON_EN_CHANGE(IDC_EDIT_DELAY_COUNT, &CKSJCtrlBoardDlg::OnEnChangeEditDelayCount)
	ON_BN_CLICKED(IDC_BUTTON_SET_FLASHTIME, &CKSJCtrlBoardDlg::OnBnClickedButtonSetFlashtime)
	ON_BN_CLICKED(IDC_BUTTON_SET_PREFLASHTIME, &CKSJCtrlBoardDlg::OnBnClickedButtonSetPreflashtime)
	ON_BN_CLICKED(IDC_CHECK_FLASHMODE, &CKSJCtrlBoardDlg::OnBnClickedCheckFlashmode)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_TRIGGER, &CKSJCtrlBoardDlg::OnNMCustomdrawSliderTrigger)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_EDIT_TRIGGER, &CKSJCtrlBoardDlg::OnEnChangeEditTrigger)
END_MESSAGE_MAP()


// CKSJCtrlBoardDlg 消息处理程序


BOOL CKSJCtrlBoardDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ReadIni();
	// TODO:  在此添加额外的初始化


	CSpinButtonCtrl* pSpinCtrl = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_FLASHTIME);
	pSpinCtrl->SetRange32(0, 255);
	pSpinCtrl->SetBuddy(GetDlgItem(IDC_EDIT_FLASHTIME));
	pSpinCtrl->SetBase(10);
	pSpinCtrl->SetPos32(10);

	pSpinCtrl = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_PREFLASHTIME);
	pSpinCtrl->SetRange32(0, 255);
	pSpinCtrl->SetBuddy(GetDlgItem(IDC_EDIT_PREFLASHTIME));
	pSpinCtrl->SetBase(10);
	pSpinCtrl->SetPos32(10);

	pSpinCtrl = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_DELAY_TIME);
	pSpinCtrl->SetRange32(0, 65535);
	pSpinCtrl->SetBuddy(GetDlgItem(IDC_EDIT_DELAY_TIME));
	pSpinCtrl->SetBase(10);
	pSpinCtrl->SetPos32(m_wDelayTime / 10);


	int i;
	CComboBox    *pComboBox = NULL;

	// 对控制板的触发模式
	pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_TRIGGER_MODE);
	pComboBox->ResetContent();

	for (i = 0; i < sizeof(g_szTriggerModeB) / sizeof(TCHAR*); i++)
	{
		pComboBox->AddString(g_szTriggerModeB[i]);
	}
	pComboBox->SetCurSel(m_nTriggerModeIndex);

	InterfaceUpdateTriggerMode();

	// 输入到控制板的信号源选择
	pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_INPUT_SOURCE);
	pComboBox->ResetContent();

	for (i = 0; i < sizeof(g_szInputSource) / sizeof(TCHAR*); i++)
	{
		pComboBox->AddString(g_szInputSource[i]);
	}
	pComboBox->SetCurSel(m_nInputSourceIndex);

	// 输入到控制板的信号源有效模式选择
	pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_TRIGGER_METHOD);
	pComboBox->ResetContent();

	for (i = 0; i < sizeof(g_szTriggerMethodB) / sizeof(TCHAR*); i++)
	{
		pComboBox->AddString(g_szTriggerMethodB[i]);
	}
	pComboBox->SetCurSel(m_nTriggerMethodIndex);

	pSpinCtrl = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_OUTPUT_FREQ);
	pSpinCtrl->SetRange32(1, 76000);
	pSpinCtrl->SetBuddy(GetDlgItem(IDC_EDIT_OUTPUT_FREQ));
	TCHAR szValue[32] = { '\0' };
	if (m_CtrlBoardType == KSJ_CONTROL_BOARD_UNO)
	{
		_stprintf_s(szValue, _T("%d"), m_wOutputFreq);
	}
	else
	{
		_stprintf_s(szValue, _T("%d"), 1000000 / m_wOutputFreq);
	}

	((CEdit*)GetDlgItem(IDC_EDIT_OUTPUT_FREQ))->SetWindowText(szValue);

	pSpinCtrl = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_OUTPUT_NUM);
	pSpinCtrl->SetRange32(0, 0xFFFF);
	pSpinCtrl->SetBuddy(GetDlgItem(IDC_EDIT_OUTPUT_NUM));
	_stprintf_s(szValue, _T("%d"), m_wOutputPulseNum);
	((CEdit*)GetDlgItem(IDC_EDIT_OUTPUT_NUM))->SetWindowText(szValue);

	((CButton*)GetDlgItem(IDC_CHECK_INFINITE))->SetCheck(m_bInfinite);


	// 模式1或模式2时，使用内部时钟计数还是外部编码器脉冲技术
	pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_DELAY_MODE);
	pComboBox->ResetContent();

	for (i = 0; i < sizeof(g_szDelayMode) / sizeof(TCHAR*); i++)
	{
		pComboBox->AddString(g_szDelayMode[i]);
	}
	pComboBox->SetCurSel(m_nDelayModeIndex);

	// Delay Count Method (是根据脉冲计数，还是通过指定距离计算脉冲个数）
	pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_DELAY_COUNT_MOTHED);
	pComboBox->ResetContent();

	for (i = 0; i < sizeof(g_szDelayCountMethod) / sizeof(TCHAR*); i++)
	{
		pComboBox->AddString(g_szDelayCountMethod[i]);
	}
	pComboBox->SetCurSel(m_nDelayCountMethodIndex);

	InterfaceUpdateDelayCountMethod();

	// Output Channel
	pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_OUTPUT_CHANNEL);
	pComboBox->ResetContent();

	for (i = 0; i < sizeof(g_szOutputChannel) / sizeof(TCHAR*); i++)
	{
		pComboBox->AddString(g_szOutputChannel[i]);
	}
	pComboBox->SetCurSel(m_nOutputChannelIndex);
	UpdateType();
	SetWindowText(m_szBuf);

	pSpinCtrl = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_TRIGGER);
	pSpinCtrl->SetRange32(0, 5000);
	pSpinCtrl->SetBuddy(GetDlgItem(IDC_EDIT_TRIGGER));
	pSpinCtrl->SetBase(10);
	pSpinCtrl->SetPos32(m_nLineTriggerPusles);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_TRIGGER))->SetRange(0, 5000);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_TRIGGER))->SetPos(m_nLineTriggerPusles);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_TRIGGER))->SetTicFreq(100);
	m_bInitial = true;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CKSJCtrlBoardDlg::InterfaceUpdateDelayCountMethod()
{
	CSpinButtonCtrl * pSpinCtrl = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_DELAY_COUNT);
	CEdit *pEditCtrl = ((CEdit*)GetDlgItem(IDC_EDIT_DELAY_COUNT));

	CString strValue;
	pSpinCtrl->SetBase(10);

	if (m_nDelayCountMethodIndex == 0)
	{
		((CStatic*)GetDlgItem(IDC_STATIC_DELAY_METHOD))->SetWindowText(_T("Pulse"));

		pSpinCtrl->SetRange32(DELAY_COUNT_PULSE_MIN, DELAY_COUNT_PULSE_MAX);
		pSpinCtrl->SetPos32(m_wDelayCount);

		strValue.Format(DELAY_COUNT_PULSE_FORMAT, pSpinCtrl->GetPos32());
		pEditCtrl->SetWindowText(strValue);
	}

	else if (m_nDelayCountMethodIndex == 1)
	{
		((CStatic*)GetDlgItem(IDC_STATIC_DELAY_METHOD))->SetWindowText(_T("mm"));

		pSpinCtrl->SetRange32(DELAY_DISTANCE_MIN, DELAY_DISTANCE_MAX);
		float fDelayDistanceMM = CalculateDelayDistance();
		pSpinCtrl->SetPos32(fDelayDistanceMM);

		strValue.Format(DELAY_DISTANCE_FORMAT, fDelayDistanceMM);
		pEditCtrl->SetWindowText(strValue);
	}
}


// 触发模式改变后需要更新界面
void CKSJCtrlBoardDlg::InterfaceUpdateTriggerMode()
{
	((CComboBox*)GetDlgItem(IDC_COMBO_OUTPUT_CHANNEL))->EnableWindow(TRUE);
	((CComboBox*)GetDlgItem(IDC_COMBO_TRIGGER_MODE))->EnableWindow(TRUE);
	((CComboBox*)GetDlgItem(IDC_COMBO_TRIGGER_METHOD))->EnableWindow(TRUE);

	CEdit *pEditCtrlOutputFreq = ((CEdit*)GetDlgItem(IDC_EDIT_OUTPUT_FREQ));
	CSpinButtonCtrl * pSpinCtrlOutputFreq = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_OUTPUT_FREQ);

	CButton *pButtonInfinite = ((CButton*)GetDlgItem(IDC_CHECK_INFINITE));

	CEdit *pEditCtrlOutputNum = ((CEdit*)GetDlgItem(IDC_EDIT_OUTPUT_NUM));
	CSpinButtonCtrl * pSpinCtrlOutputNum = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_OUTPUT_NUM);

	//////////////////////////////////////////////////////////////////////////////////////////////
	CComboBox *pComboBoxDelayMode = (CComboBox*)GetDlgItem(IDC_COMBO_DELAY_MODE);
	CComboBox *pComboBoxDelayCountMethod = (CComboBox*)GetDlgItem(IDC_COMBO_DELAY_COUNT_MOTHED);

	CSpinButtonCtrl * pSpinCtrlDelayCount = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_DELAY_COUNT);
	CEdit *pEditCtrlDelayCount = ((CEdit*)GetDlgItem(IDC_EDIT_DELAY_COUNT));

	//////////////////////////////////////////////////////////////////////////////////////////////
	CComboBox *pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_INPUT_SOURCE);

	if (m_nTriggerModeIndex == 0)
	{
		pEditCtrlOutputFreq->EnableWindow(TRUE);
		pSpinCtrlOutputFreq->EnableWindow(TRUE);
		pButtonInfinite->EnableWindow(TRUE);
		pEditCtrlOutputNum->EnableWindow(TRUE);
		pSpinCtrlOutputNum->EnableWindow(TRUE);

		pComboBoxDelayMode->EnableWindow(FALSE);
		pComboBoxDelayCountMethod->EnableWindow(FALSE);
		pSpinCtrlDelayCount->EnableWindow(FALSE);
		pEditCtrlDelayCount->EnableWindow(FALSE);

		pComboBox->EnableWindow(FALSE);
	}
	else if (m_nTriggerModeIndex == 1)
	{
		pEditCtrlOutputFreq->EnableWindow(FALSE);
		pSpinCtrlOutputFreq->EnableWindow(FALSE);
		pButtonInfinite->EnableWindow(FALSE);
		pEditCtrlOutputNum->EnableWindow(FALSE);
		pSpinCtrlOutputNum->EnableWindow(FALSE);

		pComboBoxDelayMode->EnableWindow(TRUE);
		pComboBoxDelayCountMethod->EnableWindow(TRUE);
		pSpinCtrlDelayCount->EnableWindow(TRUE);
		pEditCtrlDelayCount->EnableWindow(TRUE);

		pComboBox->EnableWindow(TRUE);
		// 输入到控制板的信号源选择

		pComboBox->ResetContent();
		for (int i = 0; i < sizeof(g_szInputSource) / sizeof(TCHAR*)-1; i++)
		{
			pComboBox->AddString(g_szInputSource[i]);
		}
		pComboBox->SetCurSel(m_nInputSourceIndex);

		if (0 == m_nDelayModeIndex)
		{
			((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_DELAY_TIME))->EnableWindow(TRUE);
			((CEdit*)GetDlgItem(IDC_EDIT_DELAY_TIME))->EnableWindow(TRUE);
			((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_DELAY_COUNT))->EnableWindow(FALSE);
			((CEdit*)GetDlgItem(IDC_EDIT_DELAY_COUNT))->EnableWindow(FALSE);
			((CComboBox*)GetDlgItem(IDC_COMBO_DELAY_COUNT_MOTHED))->EnableWindow(FALSE);
		}
		else
		{
			((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_DELAY_TIME))->EnableWindow(FALSE);
			((CEdit*)GetDlgItem(IDC_EDIT_DELAY_TIME))->EnableWindow(FALSE);
			((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_DELAY_COUNT))->EnableWindow(TRUE);
			((CEdit*)GetDlgItem(IDC_EDIT_DELAY_COUNT))->EnableWindow(TRUE);
			((CComboBox*)GetDlgItem(IDC_COMBO_DELAY_COUNT_MOTHED))->EnableWindow(TRUE);
		}
	}
	else if (m_nTriggerModeIndex == 2)
	{
		pEditCtrlOutputFreq->EnableWindow(FALSE);
		pSpinCtrlOutputFreq->EnableWindow(FALSE);
		pButtonInfinite->EnableWindow(FALSE);
		pEditCtrlOutputNum->EnableWindow(FALSE);
		pSpinCtrlOutputNum->EnableWindow(FALSE);

		pComboBoxDelayMode->EnableWindow(TRUE);
		pComboBoxDelayCountMethod->EnableWindow(TRUE);
		pSpinCtrlDelayCount->EnableWindow(TRUE);
		pEditCtrlDelayCount->EnableWindow(TRUE);

		pComboBox->EnableWindow(TRUE);

		// 输入到控制板的信号源选择
		CComboBox *pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_INPUT_SOURCE);
		pComboBox->ResetContent();
		for (int i = 0; i < sizeof(g_szInputSource) / sizeof(TCHAR*); i++)
		{
			pComboBox->AddString(g_szInputSource[i]);
		}
		pComboBox->SetCurSel(m_nInputSourceIndex);

		if (0 == m_nDelayModeIndex)
		{
			((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_DELAY_TIME))->EnableWindow(TRUE);
			((CEdit*)GetDlgItem(IDC_EDIT_DELAY_TIME))->EnableWindow(TRUE);
			((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_DELAY_COUNT))->EnableWindow(FALSE);
			((CEdit*)GetDlgItem(IDC_EDIT_DELAY_COUNT))->EnableWindow(FALSE);
			((CComboBox*)GetDlgItem(IDC_COMBO_DELAY_COUNT_MOTHED))->EnableWindow(FALSE);
		}
		else
		{
			((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_DELAY_TIME))->EnableWindow(FALSE);
			((CEdit*)GetDlgItem(IDC_EDIT_DELAY_TIME))->EnableWindow(FALSE);
			((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_DELAY_COUNT))->EnableWindow(TRUE);
			((CEdit*)GetDlgItem(IDC_EDIT_DELAY_COUNT))->EnableWindow(TRUE);
			((CComboBox*)GetDlgItem(IDC_COMBO_DELAY_COUNT_MOTHED))->EnableWindow(TRUE);
		}
	}
}

// 由脉冲个数计算距离mm
float CKSJCtrlBoardDlg::CalculateDelayDistance()
{
	float fCircle = PI * m_fCoderDiameter1;					           // 编码器同步周长(MM)
	float fStep = fCircle / m_nEncoderResolution1;                        // 编码器一个脉冲走多长
	return (float)m_wDelayCount * fStep;
}

// 由脉冲个数计算延时时间ms
float CKSJCtrlBoardDlg::CalculateDelayTime()
{
	return (float)m_wDelayCount / 10.0f;    // 转换为100uS的计数步长，因为FPGA是以100uS进行计数的
}


WORD CKSJCtrlBoardDlg::CMD_GetDeviceType()
{
	if (m_nComIndex == -1)    return KSJ_CONTROL_BOARD_UNKNOWN;

	int nRet = KSJCOM_RET_SUCCESS;

	CB_CMD_MEGA8_READ_INFO    CmdMega8ReadInfo;
	memset(&CmdMega8ReadInfo, 0, sizeof(CB_CMD_MEGA8_READ_INFO));

	// 获取设备型号
	memset(&CmdMega8ReadInfo, 0, sizeof(CB_CMD_MEGA8_READ_INFO));

	CmdMega8ReadInfo.ucPre = COMMON_PROTOCOL_PRE;
	CmdMega8ReadInfo.ucFunctionMode = FM_READ_MAGE8_INFO;
	CmdMega8ReadInfo.ucInfoIndex = MAGE8REG_DEVICE_TYPE;
	CmdMega8ReadInfo.ucEnd = COMMON_PROTOCOL_END;

	int nBytesSend = 0;
	nBytesSend = KSJCOM_SendData(m_nComIndex, (BYTE*)&CmdMega8ReadInfo, sizeof(CmdMega8ReadInfo));

	REP_CMD_MAGE8_READ_INFO    RepMega8ReadInfo;
	memset(&RepMega8ReadInfo, 0, sizeof(REP_CMD_MAGE8_READ_INFO));

	nRet = KSJCOM_ReadData(m_nComIndex, (BYTE*)&RepMega8ReadInfo, sizeof(REP_CMD_MAGE8_READ_INFO));
	if (nRet != sizeof(REP_CMD_MAGE8_READ_INFO))    return KSJ_CONTROL_BOARD_UNKNOWN;

	return (RepMega8ReadInfo.btMSB << 8) | RepMega8ReadInfo.btLSB;
}

WORD CKSJCtrlBoardDlg::CMD_GetFwVersion()
{
	if (m_nComIndex == -1)    return KSJ_CONTROL_BOARD_UNKNOWN;

	int nRet = KSJCOM_RET_SUCCESS;

	// 获取固件版本
	CB_CMD_MEGA8_READ_INFO    CmdMega8ReadInfo;
	memset(&CmdMega8ReadInfo, 0, sizeof(CB_CMD_MEGA8_READ_INFO));

	CmdMega8ReadInfo.ucPre = TAG_CMD;
	CmdMega8ReadInfo.ucFunctionMode = FM_READ_MAGE8_INFO;
	CmdMega8ReadInfo.ucInfoIndex = MAGE8REG_VERSION;// MAGE8REG_SPEED, MAGE8REG_DEVICE_TYPE
	CmdMega8ReadInfo.ucEnd = COMMON_PROTOCOL_END;

	int nBytesSend = 0;
	nBytesSend = KSJCOM_SendData(m_nComIndex, (BYTE*)&CmdMega8ReadInfo, sizeof(CmdMega8ReadInfo));

	REP_CMD_MAGE8_READ_INFO    RepMega8ReadInfo;
	memset(&RepMega8ReadInfo, 0, sizeof(REP_CMD_MAGE8_READ_INFO));
	nRet = KSJCOM_ReadData(m_nComIndex, (BYTE*)&RepMega8ReadInfo, sizeof(REP_CMD_MAGE8_READ_INFO));
	if (nRet != sizeof(REP_CMD_MAGE8_READ_INFO))    return KSJ_CONTROL_BOARD_UNKNOWN;

	return (RepMega8ReadInfo.btMSB << 8) | RepMega8ReadInfo.btLSB;

}


WORD CKSJCtrlBoardDlg::CMD_GetMega8Message(int type)
{
	if (m_nComIndex == -1)    return -1;

	int nRet = KSJCOM_RET_SUCCESS;

	CB_CMD_MEGA8_READ_INFO    CmdMega8ReadInfo;
	memset(&CmdMega8ReadInfo, 0, sizeof(CB_CMD_MEGA8_READ_INFO));

	// 获取设备型号
	CmdMega8ReadInfo.ucPre = COMMON_PROTOCOL_PRE;
	CmdMega8ReadInfo.ucFunctionMode = FM_READ_MAGE8_INFO;
	CmdMega8ReadInfo.ucInfoIndex = type;
	CmdMega8ReadInfo.ucEnd = COMMON_PROTOCOL_END;

	int nBytesSend = 0;
	nBytesSend = KSJCOM_SendData(m_nComIndex, (BYTE*)&CmdMega8ReadInfo, sizeof(CmdMega8ReadInfo));

	REP_CMD_MAGE8_READ_INFO    RepMega8ReadInfo;
	memset(&RepMega8ReadInfo, 0, sizeof(REP_CMD_MAGE8_READ_INFO));

	nRet = KSJCOM_ReadData(m_nComIndex, (BYTE*)&RepMega8ReadInfo, sizeof(REP_CMD_MAGE8_READ_INFO));
	if (nRet != sizeof(REP_CMD_MAGE8_READ_INFO))    return -1;

	return (RepMega8ReadInfo.btMSB << 8) | RepMega8ReadInfo.btLSB;
}

WORD CKSJCtrlBoardDlg::CMD_GetFpgaVersion()
{
	if (m_nComIndex == -1)    return -1;

	int nRet = KSJCOM_RET_SUCCESS;

	CB_CMD_FPGA_READ_REG    CmdFpgaReadInfo;
	memset(&CmdFpgaReadInfo, 0, sizeof(CB_CMD_FPGA_READ_REG));

	CmdFpgaReadInfo.ucPre = COMMON_PROTOCOL_PRE;
	CmdFpgaReadInfo.ucFunctionMode = FM_READ_FPGA;
	CmdFpgaReadInfo.ucRegAddress = FPGAREG_LED;
	CmdFpgaReadInfo.ucEnd = COMMON_PROTOCOL_END;

	int nBytesSend = 0;
	nBytesSend = KSJCOM_SendData(m_nComIndex, (BYTE*)&CmdFpgaReadInfo, sizeof(CmdFpgaReadInfo));

	REP_CMD_MAGE8_READ_INFO    RepMega8ReadInfo;
	memset(&RepMega8ReadInfo, 0, sizeof(REP_CMD_MAGE8_READ_INFO));

	nRet = KSJCOM_ReadData(m_nComIndex, (BYTE*)&RepMega8ReadInfo, sizeof(REP_CMD_MAGE8_READ_INFO));
	if (nRet != sizeof(REP_CMD_MAGE8_READ_INFO))    return -1;

	return (RepMega8ReadInfo.btMSB << 8) | RepMega8ReadInfo.btLSB;
}


//============================================================================
// 函数名：SetTriggerMode0
// 功能：设置外触发模式0的参数
// 参数：ucStart- 启，停，设置标志，当该值为非零时，后面的其他参数无效；
// ucOutputChannel- 输出通道；
// ucOutputTriggerMethod-脉冲触发方式，上升沿，下降沿，高低电平；
// usOutputFreq- 输出触发脉冲频率；现在已改为10^6/Freq / 100  = N* 100us
// usOutputPulseNum - 输出触发脉冲的个数
// 返回值：执行成功返回1
//============================================================================
int CKSJCtrlBoardDlg::SetTriggerMode0(
	int nCurCom,
	unsigned char ucStart,
	unsigned char ucOutputChannel,
	unsigned char ucOutputTriggerMethod,
	unsigned short usOutputFreq,
	unsigned short usOutputPulseNum
	)
{
	CB_CMD_TRIGGER CmdTrigger;
	memset(&CmdTrigger, 0, sizeof(CB_CMD_TRIGGER));

	CmdTrigger.ucPre = TAG_CMD;												// 8bit 命令开始标志，
	CmdTrigger.ucFunctionMode = FM_TRIGGER_MODE;						    // 设置的功能模式
	CmdTrigger.ucStart = ucStart;									        // ucStart作为启停命令，0-设置参数，1-启动，2-停止
	CmdTrigger.ucOutputChannel = ucOutputChannel;						    // 8bit 选择输出通道
	CmdTrigger.ucOutputTriggerMethod = ucOutputTriggerMethod;			    // 8bit 触发方式，上、下、高、低
	CmdTrigger.ucOutputTriggerMode = 0;

	// 内部自动触发脉冲
	CmdTrigger.TriggerMode.Mode0.usOutputFreq = usOutputFreq;			    // 脉冲频率
	CmdTrigger.TriggerMode.Mode0.usOutputPulseNum = usOutputPulseNum;	    // 输出脉冲的个数，0或者FFFF代表无限个

	CmdTrigger.ucCheckSum = (unsigned char)(ucStart + ucOutputChannel + ucOutputTriggerMethod + usOutputFreq + usOutputPulseNum);
	CmdTrigger.ucEnd = TAG_END;

	// 命令填充完成，此处添加命令发送函数
	unsigned char szBuf[NUM_BYTE_OF_CMD] = { 0 };
	int n = sizeof(CB_CMD_TRIGGER);
	memcpy(szBuf, (unsigned char*)&CmdTrigger, sizeof(CmdTrigger));
	int nRet = KSJCOM_SendData(nCurCom, szBuf, NUM_BYTE_OF_CMD);

	return nRet;
}


//============================================================================
// 函数名： SetTriggerMode1:
// 功能： 设置外触发模式1
// 参数：ucStart：		  启，停，设置标志，当该值为非零时，后面的其他参数无效；
// ucOutputChannel：		  脉冲输出通道
// ucOutputTriggerMethod：输出脉冲的触发方式；
// ucTriggerInputChannel：触发脉冲输入通道，
// ucDelayMode：			  延时模式
// usDelayCounter：		  延时计数
// 返回值：执行成功返回1
//============================================================================
int CKSJCtrlBoardDlg::SetTriggerMode1(
	int nCurCom,
	unsigned char ucStart,
	unsigned char ucOutputChannel,
	unsigned char ucOutputTriggerMethod,
	unsigned char ucTriggerInputChannel,
	unsigned char ucDelayMode,
	unsigned short usDelayCounter)
{
	CB_CMD_TRIGGER CmdTrigger;
	memset(&CmdTrigger, 0, sizeof(CB_CMD_TRIGGER));

	CmdTrigger.ucPre = TAG_CMD;													// 8bit 命令开始标志，
	CmdTrigger.ucFunctionMode = FM_TRIGGER_MODE;										// 0:外触发功能，1 步进电机功能；
	CmdTrigger.ucStart = ucStart;											// ucReserve作为启停命令，0-设置参数，1-启动，2-停止
	CmdTrigger.ucOutputChannel = ucOutputChannel;							// 8bit 选择输出通道
	CmdTrigger.ucOutputTriggerMethod = ucOutputTriggerMethod;				// 8bit 触发方式，上、下、高、低
	CmdTrigger.ucOutputTriggerMode = 1;

	CmdTrigger.TriggerMode.Mode1.ucTriggerInputChannel = ucTriggerInputChannel;
	CmdTrigger.TriggerMode.Mode1.ucDelayMode = ucDelayMode;
	CmdTrigger.TriggerMode.Mode1.usDelayCounter = usDelayCounter;

	CmdTrigger.ucCheckSum = (unsigned char)(ucStart + ucOutputChannel + ucOutputTriggerMethod + ucTriggerInputChannel + ucDelayMode + usDelayCounter);
	CmdTrigger.ucEnd = TAG_END;

	unsigned char szBuf[NUM_BYTE_OF_CMD] = { 0 };
	int n = sizeof(CB_CMD_TRIGGER);
	memcpy(szBuf, (unsigned char*)&CmdTrigger, sizeof(CmdTrigger));
	int nRet = KSJCOM_SendData(nCurCom, szBuf, NUM_BYTE_OF_CMD);
	return nRet;
}


int CKSJCtrlBoardDlg::SetTriggerMode2(
	int            nCurCom,
	unsigned char  ucStart,
	unsigned char  ucOutputChannel,
	unsigned char  ucOutputTriggerMethod,
	unsigned char  ucTriggerInputChannel,
	unsigned char  ucDelayMode,
	unsigned short usDelayCounter,
	unsigned short usTriggerNumPerCircleMode2,
	unsigned short usNumofBufferMode2
	)
{
	CB_CMD_TRIGGER CmdTrigger;
	memset(&CmdTrigger, 0, sizeof(CB_CMD_TRIGGER));

	CmdTrigger.ucPre = TAG_CMD;												// 8bit 命令开始标志，
	CmdTrigger.ucFunctionMode = FM_TRIGGER_MODE;						    // 0:外触发功能，1 步进电机功能；
	CmdTrigger.ucStart = ucStart;											// ucReserve作为启停命令，0-设置参数，1-启动，2-停止
	CmdTrigger.ucOutputChannel = ucOutputChannel;							// 8bit 选择输出通道
	CmdTrigger.ucOutputTriggerMethod = ucOutputTriggerMethod;				// 8bit 触发方式，上、下、高、低
	CmdTrigger.ucOutputTriggerMode = 2;

	CmdTrigger.TriggerMode.Mode2.ucTriggerInputChannel = ucTriggerInputChannel; // 触发输入源，共有3个触发源，0/1/2,0-触发输入源0；1-触发输入源1; 2-以编码器Z为输入源
	CmdTrigger.TriggerMode.Mode2.ucDelayMode = ucDelayMode;                     // 触发延时模式, 两种延时模式，0：自定义延时时间，1：根据编码器输入延时
	CmdTrigger.TriggerMode.Mode2.usDelayCounter = usDelayCounter;               // 延时计数：延时模式0时：自定义单位ms；延时模式1时：代表编码器输入脉冲个数
	CmdTrigger.TriggerMode.Mode2.usLineTriggerPusles = usTriggerNumPerCircleMode2;
	CmdTrigger.TriggerMode.Mode2.usLineTriggerPkt = usNumofBufferMode2;           // 相机软件设定采集一帧线扫数量

	CmdTrigger.ucCheckSum = (unsigned char)(ucStart + ucOutputChannel + ucOutputTriggerMethod + usTriggerNumPerCircleMode2 + usNumofBufferMode2);
	CmdTrigger.ucEnd = TAG_END;

	unsigned char szBuf[NUM_BYTE_OF_CMD] = { 0 };
	int n = sizeof(CB_CMD_TRIGGER);
	memcpy(szBuf, (unsigned char*)&CmdTrigger, sizeof(CmdTrigger));
	int nRet = KSJCOM_SendData(nCurCom, szBuf, NUM_BYTE_OF_CMD);
	return nRet;
}

void CKSJCtrlBoardDlg::CMD_SetFlashlight(unsigned char type, unsigned char param)
{
	if (m_nComIndex == -1)    return;

	CB_CMD_CTRL_LAMP    CmdCtrlLamp;
	memset(&CmdCtrlLamp, 0, sizeof(CB_CMD_CTRL_LAMP));

	CmdCtrlLamp.ucPre = COMMON_PROTOCOL_PRE;
	CmdCtrlLamp.ucFunctionMode = FM_WRITE_FPGA;
	CmdCtrlLamp.ucSetFlash = type;
	CmdCtrlLamp.ucFlashParam = param;
	CmdCtrlLamp.ucEnd = COMMON_PROTOCOL_END;

	int nBytesSend = 0;
	nBytesSend = KSJCOM_SendData(m_nComIndex, (BYTE*)&CmdCtrlLamp, sizeof(CB_CMD_CTRL_LAMP));

	return;
}


int CKSJCtrlBoardDlg::CMD_ReadUno(BYTE btChannel)
{
	// 首先读取参数信息
	int nRet;

	CB_UNO_CMD UNO_Command;

	memcpy(&UNO_Command, &m_UNO_Command[btChannel], sizeof(CB_UNO_CMD));

	UNO_Command.ucFuncMode = FM_GET_PARAM;
	UNO_Command.ucCheckSum = UNO_CHECKSUM(UNO_Command.ucChannel, UNO_Command.ucFuncMode, UNO_Command.usTriggerSpeed, UNO_Command.usPulseNum);
	nRet = KSJCOM_SendData(m_nComIndex, (unsigned char*)&UNO_Command, sizeof(UNO_Command));
	if (nRet != sizeof(CB_UNO_CMD))    return -1;

	memset(&UNO_Command, 0, sizeof(CB_UNO_CMD));

	nRet = KSJCOM_ReadData(m_nComIndex, (BYTE*)&UNO_Command, sizeof(CB_UNO_CMD));
	if (nRet != sizeof(CB_UNO_CMD))    return -1;

	memcpy(&m_UNO_Command[btChannel], &UNO_Command, sizeof(CB_UNO_CMD));

	return 0;
}

void CKSJCtrlBoardDlg::Start_Uno(BOOL bStart)
{
	CComboBox *pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_OUTPUT_CHANNEL);
	BOOL bCheck = ((CButton*)GetDlgItem(IDC_CHECK_INFINITE))->GetCheck();

	int nOutputChannelIndex = pComboBox->GetCurSel();
	int nOutputFreq = GetDlgItemInt(IDC_EDIT_OUTPUT_FREQ);
	int nOutputPulseNum = 0;

	if (bCheck)
	{
		nOutputPulseNum = 65535;
	}
	else
	{
		nOutputPulseNum = GetDlgItemInt(IDC_EDIT_OUTPUT_NUM);
	}

	int nRet = -1;

	if (bStart)
	{
		nRet = CMD_SetUno(nOutputChannelIndex, nOutputFreq, nOutputPulseNum);
		ShowResult(nRet);
		if (nRet == -1)    return;
	}

	nRet = CMD_StartUno(nOutputChannelIndex, bStart);
	ShowResult(nRet);
}

void CKSJCtrlBoardDlg::ShowResult(int nRet)
{
	if (-1 == nRet)
	{
		((CEdit*)GetDlgItem(IDC_STATIC_RESULT))->SetWindowText(_T("Failed"));
	}
	else
	{
		((CEdit*)GetDlgItem(IDC_STATIC_RESULT))->SetWindowText(_T("Successful"));
	}
}

int  CKSJCtrlBoardDlg::CMD_SetUno(BYTE btChannel, WORD wTriggerSpeed, WORD wPulseNum)
{
	int nRet = KSJCOM_RET_SUCCESS;

	CB_UNO_CMD UNO_Command;

	memcpy(&UNO_Command, &m_UNO_Command[btChannel], sizeof(CB_UNO_CMD));

	UNO_Command.ucFuncMode = FM_SET_PARAM;
	UNO_Command.usTriggerSpeed = wTriggerSpeed;
	UNO_Command.usPulseNum = wPulseNum;
	UNO_Command.ucCheckSum = UNO_CHECKSUM(UNO_Command.ucChannel, UNO_Command.ucFuncMode, UNO_Command.usTriggerSpeed, UNO_Command.usPulseNum);

	nRet = KSJCOM_SendData(m_nComIndex, (unsigned char*)&UNO_Command, sizeof(UNO_Command));
	if (nRet != sizeof(CB_UNO_CMD))    return -1;

	memcpy(&m_UNO_Command[btChannel], &UNO_Command, sizeof(CB_UNO_CMD));

	return 0;
}


int CKSJCtrlBoardDlg::CMD_StartUno(BYTE btChannel, BOOL bStart)
{
	int nRet = -1;

	CB_UNO_CMD UNO_Command;
	memcpy(&UNO_Command, &m_UNO_Command[btChannel], sizeof(CB_UNO_CMD));

	if (bStart)
	{
		UNO_Command.ucFuncMode = FM_START;
		UNO_Command.ucCheckSum = UNO_CHECKSUM(UNO_Command.ucChannel, UNO_Command.ucFuncMode, UNO_Command.usTriggerSpeed, UNO_Command.usPulseNum);
	}
	else
	{
		UNO_Command.ucFuncMode = FM_STOP;
		UNO_Command.ucCheckSum = UNO_CHECKSUM(UNO_Command.ucChannel, UNO_Command.ucFuncMode, UNO_Command.usTriggerSpeed, UNO_Command.usPulseNum);
		//nRet = KSJCOM_SendData(m_nComIndex, (unsigned char*)&UNO_Command, sizeof(UNO_Command));
	}

	nRet = KSJCOM_SendData(m_nComIndex, (unsigned char*)&UNO_Command, sizeof(UNO_Command));
	if (nRet != sizeof(CB_UNO_CMD))    return -1;

	memcpy(&m_UNO_Command[btChannel], &UNO_Command, sizeof(CB_UNO_CMD));

	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CKSJCtrlBoardDlg::InitialUnoInterface()
{
	int i;
	CComboBox    *pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_OUTPUT_CHANNEL);
	pComboBox->ResetContent();

	for (i = 0; i < sizeof(g_szOutputChannel) / sizeof(TCHAR*); i++)
	{
		pComboBox->AddString(g_szOutputChannel[i]);
	}
	pComboBox->SetCurSel(m_nOutputChannelIndex);

	// 触发模式选择
	CComboBox *pComboBoxTriggerMode = (CComboBox*)GetDlgItem(IDC_COMBO_TRIGGER_MODE);
	pComboBoxTriggerMode->SetCurSel(0);
	pComboBoxTriggerMode->EnableWindow(FALSE);
	// 输入源选择
	CComboBox *pComboBoxInputSource = (CComboBox*)GetDlgItem(IDC_COMBO_INPUT_SOURCE);
	pComboBoxInputSource->EnableWindow(FALSE);
	// 触发方式选择
	CComboBox *pComboTriggerMethod = (CComboBox*)GetDlgItem(IDC_COMBO_TRIGGER_METHOD);
	pComboTriggerMethod->EnableWindow(FALSE);

	// 输出固定触发频率
	CEdit *pEditCtrlOutputFreq = ((CEdit*)GetDlgItem(IDC_EDIT_OUTPUT_FREQ));
	pEditCtrlOutputFreq->EnableWindow(TRUE);
	CSpinButtonCtrl * pSpinCtrlOutputFreq = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_OUTPUT_FREQ);
	pSpinCtrlOutputFreq->EnableWindow(TRUE);

	pSpinCtrlOutputFreq->SetRange32(1, TRIGGERSPEED_HZ_MAX);
	pSpinCtrlOutputFreq->SetBuddy(GetDlgItem(IDC_EDIT_OUTPUT_FREQ));
	// pSpinCtrlOutputFreq->SetPos32(m_UNO_Command[m_nOutputChannelIndex].usTriggerSpeed);

	// 输出固定触发脉冲个数
	CEdit   *pEditCtrlOutputNum = ((CEdit*)GetDlgItem(IDC_EDIT_OUTPUT_NUM));
	pEditCtrlOutputNum->EnableWindow(m_UNO_Command[m_nOutputChannelIndex].usPulseNum == 0xFFFF ? FALSE : TRUE);
	CSpinButtonCtrl * pSpinCtrlOutputNum = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_OUTPUT_NUM);
	pSpinCtrlOutputNum->EnableWindow(m_UNO_Command[m_nOutputChannelIndex].usPulseNum == 0xFFFF ? FALSE : TRUE);

	pSpinCtrlOutputNum->SetRange32(1, 0xFFFF);
	pSpinCtrlOutputNum->SetBuddy(GetDlgItem(IDC_EDIT_OUTPUT_NUM));
	// pSpinCtrlOutputNum->SetPos32(m_UNO_Command[m_nOutputChannelIndex].usPulseNum);

	CButton *pButtonInfinite = ((CButton*)GetDlgItem(IDC_CHECK_INFINITE));
	pButtonInfinite->SetCheck(m_UNO_Command[m_nOutputChannelIndex].usPulseNum == 0xFFFF);
	pButtonInfinite->EnableWindow(TRUE);
	// 延时模式
	CComboBox *pComboBoxDelayMode = (CComboBox*)GetDlgItem(IDC_COMBO_DELAY_MODE);
	pComboBoxDelayMode->EnableWindow(FALSE);
	// 延时计数方式
	CComboBox *pComboBoxDelayCountMethod = (CComboBox*)GetDlgItem(IDC_COMBO_DELAY_COUNT_MOTHED);
	pComboBoxDelayCountMethod->EnableWindow(FALSE);
	// 延时计数个数
	CEdit *pEditCtrlDelayCount = ((CEdit*)GetDlgItem(IDC_EDIT_DELAY_COUNT));
	pEditCtrlDelayCount->EnableWindow(FALSE);
	CSpinButtonCtrl * pSpinCtrlDelayCount = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_DELAY_COUNT);
	pSpinCtrlDelayCount->EnableWindow(FALSE);


	((CCheckListBox*)GetDlgItem(IDC_CHECK_FLASHMODE))->EnableWindow(FALSE);
	((CEdit*)GetDlgItem(IDC_EDIT_FLASHTIME))->EnableWindow(FALSE);
	((CEdit*)GetDlgItem(IDC_EDIT_PREFLASHTIME))->EnableWindow(FALSE);

	((CButton*)GetDlgItem(IDC_BUTTON_SET_FLASHTIME))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_BUTTON_SET_PREFLASHTIME))->EnableWindow(FALSE);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_DELAY_TIME))->EnableWindow(FALSE);
	((CEdit*)GetDlgItem(IDC_EDIT_DELAY_TIME))->EnableWindow(FALSE);
}

void CKSJCtrlBoardDlg::UpdateUnoInterface()
{
	CComboBox    *pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_OUTPUT_CHANNEL);
	int nChannelIndex = pComboBox->GetCurSel();

	CSpinButtonCtrl * pSpinCtrlOutputFreq = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_OUTPUT_FREQ);
	pSpinCtrlOutputFreq->SetPos32(m_UNO_Command[nChannelIndex].usTriggerSpeed);

	CSpinButtonCtrl * pSpinCtrlOutputNum = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_OUTPUT_NUM);
	pSpinCtrlOutputNum->SetPos32(m_UNO_Command[nChannelIndex].usPulseNum);

	CButton *pButtonInfinite = ((CButton*)GetDlgItem(IDC_CHECK_INFINITE));
	pButtonInfinite->SetCheck(m_UNO_Command[nChannelIndex].usPulseNum == 0xFFFF);
	pButtonInfinite->EnableWindow(TRUE);

	CEdit   *pEditCtrlOutputNum = ((CEdit*)GetDlgItem(IDC_EDIT_OUTPUT_NUM));
	pEditCtrlOutputNum->EnableWindow(m_UNO_Command[m_nOutputChannelIndex].usPulseNum == 0xFFFF ? FALSE : TRUE);
	pSpinCtrlOutputNum->EnableWindow(m_UNO_Command[m_nOutputChannelIndex].usPulseNum == 0xFFFF ? FALSE : TRUE);


	((CButton*)GetDlgItem(IDC_CHECK_START))->SetCheck(m_UNO_Command[nChannelIndex].ucFuncMode == FM_START);
}

void CKSJCtrlBoardDlg::OnCbnSelchangeComboOutputChannel()
{
	CComboBox*    pComboBox;
	pComboBox = ((CComboBox*)GetDlgItem(IDC_COMBO_OUTPUT_CHANNEL));
	int nSel = pComboBox->GetCurSel();
	if (nSel == CB_ERR)    return;

	m_nOutputChannelIndex = nSel;

	if (m_CtrlBoardType == KSJ_CONTROL_BOARD_UNO)
	{
		UpdateUnoInterface();
	}
}


void CKSJCtrlBoardDlg::OnCbnSelchangeComboTriggerMode()
{
	CComboBox*    pComboBox;
	pComboBox = ((CComboBox*)GetDlgItem(IDC_COMBO_TRIGGER_MODE));
	int nSel = pComboBox->GetCurSel();
	if (nSel == CB_ERR)    return;

	m_nTriggerModeIndex = nSel;

	InterfaceUpdateTriggerMode();
}


void CKSJCtrlBoardDlg::OnCbnSelchangeComboInputSource()
{
	CComboBox*    pComboBox;
	pComboBox = ((CComboBox*)GetDlgItem(IDC_COMBO_INPUT_SOURCE));
	int nSel = pComboBox->GetCurSel();
	if (nSel == CB_ERR)    return;

	m_nInputSourceIndex = nSel;
}


void CKSJCtrlBoardDlg::OnCbnSelchangeComboTriggerMethod()
{
	CComboBox*    pComboBox;
	pComboBox = ((CComboBox*)GetDlgItem(IDC_COMBO_TRIGGER_METHOD));
	int nSel = pComboBox->GetCurSel();
	if (nSel == CB_ERR)    return;

	m_nTriggerMethodIndex = nSel;
}


void CKSJCtrlBoardDlg::OnEnChangeEditOutputFreq()
{
	if (!m_bInitial) return;

	m_nFreq = GetDlgItemInt(IDC_EDIT_OUTPUT_FREQ);
	if (m_nFreq > 100000)
	{
		m_nFreq = 100000;
		SetDlgItemInt(IDC_EDIT_OUTPUT_FREQ, m_nFreq);
	}

	if (m_nFreq < 16)
	{
		m_nFreq = 16;
	}

	if (m_CtrlBoardType == KSJ_CONTROL_BOARD_UNO)
	{
		m_wOutputFreq = m_nFreq;
	}
	else
	{
		m_wOutputFreq = 1000000 / m_nFreq;
	}
}


void CKSJCtrlBoardDlg::OnEnChangeEditOutputNum()
{
	if (!m_bInitial) return;

	m_wOutputPulseNum = GetDlgItemInt(IDC_EDIT_OUTPUT_NUM);
}


void CKSJCtrlBoardDlg::OnCbnSelchangeComboDelayMode()
{
	CComboBox*    pComboBox;
	pComboBox = ((CComboBox*)GetDlgItem(IDC_COMBO_DELAY_MODE));
	int nSel = pComboBox->GetCurSel();
	if (nSel == CB_ERR)    return;

	m_nDelayModeIndex = nSel;
	if (0 == nSel)
	{
		((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_DELAY_TIME))->EnableWindow(TRUE);
		((CEdit*)GetDlgItem(IDC_EDIT_DELAY_TIME))->EnableWindow(TRUE);
		((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_DELAY_COUNT))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_EDIT_DELAY_COUNT))->EnableWindow(FALSE);
		((CComboBox*)GetDlgItem(IDC_COMBO_DELAY_COUNT_MOTHED))->EnableWindow(FALSE);
	}
	else
	{
		((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_DELAY_TIME))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_EDIT_DELAY_TIME))->EnableWindow(FALSE);
		((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_DELAY_COUNT))->EnableWindow(TRUE);
		((CEdit*)GetDlgItem(IDC_EDIT_DELAY_COUNT))->EnableWindow(TRUE);
		((CComboBox*)GetDlgItem(IDC_COMBO_DELAY_COUNT_MOTHED))->EnableWindow(TRUE);
	}
}


void CKSJCtrlBoardDlg::OnEnChangeEditDelayTime()
{
	if (!m_bInitial) return;

	CString	 strValue;
	((CEdit*)GetDlgItem(IDC_EDIT_DELAY_TIME))->GetWindowText(strValue);
	int nValue = (int)(_tstoi(strValue));
	m_wDelayTime = nValue * 10;
}


void CKSJCtrlBoardDlg::OnCbnSelchangeComboDelayCountMothed()
{
	CComboBox*    pComboBox;
	pComboBox = ((CComboBox*)GetDlgItem(IDC_COMBO_DELAY_COUNT_MOTHED));
	int nSel = pComboBox->GetCurSel();
	if (nSel == CB_ERR)    return;

	m_nDelayCountMethodIndex = nSel;

	InterfaceUpdateDelayCountMethod();
}


void CKSJCtrlBoardDlg::OnEnChangeEditDelayCount()
{
	if (!m_bInitial) return;

	CString	 strValue;
	((CEdit*)GetDlgItem(IDC_EDIT_DELAY_COUNT))->GetWindowText(strValue);

	int nValue;

	// 以脉冲个数设置
	if (m_nDelayCountMethodIndex == 0)
	{
		nValue = (int)(_tstoi(strValue));
		m_wDelayCount = nValue;
	}

	// 以距离mm设置，转换为脉冲个数
	else if (m_nDelayCountMethodIndex == 1)
	{
		float fDistanceMM = _tstof(strValue);
		nValue = (int)(_tstoi(strValue));

		// 通过毫米换算出触发脉冲计数值
		float fCircle = PI * m_fCoderDiameter1;					           // 编码器同步周长(MM)
		float fStep = fCircle / m_nEncoderResolution1;                        // 编码器一个脉冲走多长
		m_wDelayCount = fDistanceMM / fStep;                               // 走fDistanceMM距离需要多少个编码器脉冲计数
	}

	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_DELAY_COUNT))->SetPos32(nValue);
}


void CKSJCtrlBoardDlg::OnBnClickedCheckStart(BOOL bStart)
{
	if (KSJ_CONTROL_BOARD_UNO == m_CtrlBoardType)
	{
		Start_Uno(bStart);
		UpdateUnoInterface();
	}
	else
	{
		if (bStart)
		{
			m_bStart = true;
			if (!m_bAdjust) UnenableMega128Interface();
		}
		else
		{
			m_bStart = false;
			if (!m_bAdjust) InterfaceUpdateTriggerMode();
		}

		Start_Mega128(m_nTriggerModeIndex, bStart);
	}
}


void CKSJCtrlBoardDlg::OnBnClickedButtonSetFlashtime()
{
	BYTE btParam = 0;

	btParam = GetDlgItemInt(IDC_EDIT_FLASHTIME);

	CMD_SetFlashlight(4, btParam);
	Sleep(100);
}


void CKSJCtrlBoardDlg::OnBnClickedButtonSetPreflashtime()
{
	BYTE btParam = 0;

	btParam = GetDlgItemInt(IDC_EDIT_PREFLASHTIME);

	CMD_SetFlashlight(5, btParam);
	Sleep(100);
}


void CKSJCtrlBoardDlg::UnenableMega128Interface()
{
	CEdit *pEditCtrlOutputFreq = ((CEdit*)GetDlgItem(IDC_EDIT_OUTPUT_FREQ));
	CSpinButtonCtrl * pSpinCtrlOutputFreq = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_OUTPUT_FREQ);

	CButton *pButtonInfinite = ((CButton*)GetDlgItem(IDC_CHECK_INFINITE));

	CEdit *pEditCtrlOutputNum = ((CEdit*)GetDlgItem(IDC_EDIT_OUTPUT_NUM));
	CSpinButtonCtrl * pSpinCtrlOutputNum = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_OUTPUT_NUM);

	//////////////////////////////////////////////////////////////////////////////////////////////
	CComboBox *pComboBoxDelayMode = (CComboBox*)GetDlgItem(IDC_COMBO_DELAY_MODE);
	CComboBox *pComboBoxDelayCountMethod = (CComboBox*)GetDlgItem(IDC_COMBO_DELAY_COUNT_MOTHED);

	CSpinButtonCtrl * pSpinCtrlDelayCount = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_DELAY_COUNT);
	CEdit *pEditCtrlDelayCount = ((CEdit*)GetDlgItem(IDC_EDIT_DELAY_COUNT));

	//////////////////////////////////////////////////////////////////////////////////////////////
	CComboBox *pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_INPUT_SOURCE);

	pEditCtrlOutputFreq->EnableWindow(FALSE);
	pSpinCtrlOutputFreq->EnableWindow(FALSE);
	pButtonInfinite->EnableWindow(FALSE);
	pEditCtrlOutputNum->EnableWindow(FALSE);
	pSpinCtrlOutputNum->EnableWindow(FALSE);

	pComboBoxDelayMode->EnableWindow(FALSE);
	pComboBoxDelayCountMethod->EnableWindow(FALSE);
	pSpinCtrlDelayCount->EnableWindow(FALSE);
	pEditCtrlDelayCount->EnableWindow(FALSE);

	pComboBox->EnableWindow(FALSE);

	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_DELAY_TIME))->EnableWindow(FALSE);
	((CEdit*)GetDlgItem(IDC_EDIT_DELAY_TIME))->EnableWindow(FALSE);
	((CComboBox*)GetDlgItem(IDC_COMBO_OUTPUT_CHANNEL))->EnableWindow(FALSE);
	((CComboBox*)GetDlgItem(IDC_COMBO_TRIGGER_MODE))->EnableWindow(FALSE);
	((CComboBox*)GetDlgItem(IDC_COMBO_TRIGGER_METHOD))->EnableWindow(FALSE);
}

void CKSJCtrlBoardDlg::Start_Mega128(WORD wMultiFrames, BOOL bStart)
{
	int nRet = 0;
	nRet = CMD_StartMega128(wMultiFrames, FALSE);
	ShowResult(nRet);

	if (bStart)
	{
		Sleep(100);
		nRet = CMD_SetMega128(wMultiFrames);
		ShowResult(nRet);
		Sleep(100);
		nRet = CMD_StartMega128(wMultiFrames, bStart);
		ShowResult(nRet);
	}

	return;
}


int  CKSJCtrlBoardDlg::CMD_SetMega128(WORD wMultiFrames)
{
	unsigned char  ucOutputChannel = m_nOutputChannelIndex;
	unsigned char  ucOutputTriggerMethod = m_nTriggerMethodIndex;
	int nRet = 0;

	if (m_nTriggerModeIndex == 0)
	{
		unsigned short usOutputFreq = m_wOutputFreq;
		unsigned short usOutputPulseNum = m_wOutputPulseNum;
		nRet = SetTriggerMode0(m_nComIndex, 0, ucOutputChannel, ucOutputTriggerMethod, usOutputFreq, usOutputPulseNum);
	}
	else if (m_nTriggerModeIndex == 1)
	{
		unsigned char ucTriggerInputChannel = m_nInputSourceIndex;
		unsigned char ucDelayMode = m_nDelayModeIndex;
		unsigned short usDelayCounter = 0;
		if (0 == m_nDelayModeIndex)
		{
			usDelayCounter = m_wDelayTime;
		}
		else
		{
			usDelayCounter = m_wDelayCount;
		}

		nRet = SetTriggerMode1(m_nComIndex, 0, ucOutputChannel, ucOutputTriggerMethod, ucTriggerInputChannel, ucDelayMode, usDelayCounter);
	}
	else if (m_nTriggerModeIndex == 2)
	{
		unsigned char ucTriggerInputChannel = m_nInputSourceIndex;
		unsigned char ucDelayMode = m_nDelayModeIndex;
		unsigned short usDelayCounter = 0;
		if (0 == m_nDelayModeIndex)
		{
			usDelayCounter = m_wDelayTime;
		}
		else
		{
			usDelayCounter = m_wDelayCount;
		}

		unsigned short usMultiFrames = g_nMultiFrames;
		unsigned short usLineTriggerPusles = ((CSliderCtrl*)GetDlgItem(IDC_SLIDER_TRIGGER))->GetPos();
		nRet = SetTriggerMode2(m_nComIndex, 0, ucOutputChannel, ucOutputTriggerMethod, ucTriggerInputChannel, ucDelayMode, usDelayCounter, usLineTriggerPusles, usMultiFrames);
	}

	if (nRet != sizeof(CB_CMD_TRIGGER))    return -1;
	return 0;
}

int  CKSJCtrlBoardDlg::CMD_StartMega128(WORD wMultiFrames, BOOL bStart)
{
	unsigned char ucStart = 0;
	int nRet = 0;

	if (bStart)
	{
		ucStart = 1;
	}
	else
	{
		ucStart = 2;
	}

	if (m_nTriggerModeIndex == 0)
	{
		nRet = SetTriggerMode0(m_nComIndex, ucStart, 0, 0, 0, 0);
	}
	else if (m_nTriggerModeIndex == 1)
	{
		nRet = SetTriggerMode1(m_nComIndex, ucStart, 0, 0, 0, 0, 0);
	}
	else if (m_nTriggerModeIndex == 2)
	{
		nRet = SetTriggerMode2(m_nComIndex, ucStart, 0, 0, 0, 0, 0, 0, 0);
	}

	if (nRet != sizeof(CB_CMD_TRIGGER))    return -1;
	return 0;
}

void CKSJCtrlBoardDlg::InitialMega128Interface()
{
	WORD wTemp = CMD_GetMega8Message(3);
	((CButton*)GetDlgItem(IDC_CHECK_FLASHMODE))->SetCheck(wTemp);
	wTemp = CMD_GetMega8Message(4);
	SetDlgItemInt(IDC_EDIT_FLASHTIME, wTemp);
	wTemp = CMD_GetMega8Message(5);
	SetDlgItemInt(IDC_EDIT_PREFLASHTIME, wTemp);
}

void CKSJCtrlBoardDlg::OnBnClickedCheckFlashmode()
{
	int nFlashmode = 0;
	nFlashmode = ((CButton*)GetDlgItem(IDC_CHECK_FLASHMODE))->GetCheck();
	CMD_SetFlashlight(3, nFlashmode);
}


void CKSJCtrlBoardDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	if (m_nTimer != 0)
	{
		KillTimer(TIMERID_SPEED);
	}

	WriteIni();
}



void CKSJCtrlBoardDlg::UpdateType()
{
	WORD   wVersion = CMD_GetFwVersion();
	m_btFwVersionMaj = wVersion >> 8;
	m_btFwVersionMin = wVersion & 0x00FF;


	if (KSJ_CONTROL_BOARD_UNO == m_CtrlBoardType)
	{
		sprintf_s(m_szBuf, _T("DeviceType: %s, Firmware Version( %d.%d)"), g_szDeviceTypeB[(int)m_CtrlBoardType], m_btFwVersionMaj, m_btFwVersionMin);
		for (int i = 0; i < UNO_OUTPUT_CHANNEL_NUM; i++)
		{
			CMD_ReadUno(i);
		}
		InitialUnoInterface();
		UpdateUnoInterface();
	}
	else if (KSJ_CONTROL_BOARD_MEGA128 == m_CtrlBoardType)
	{
		if (m_nTimer != 0)
		{
			KillTimer(TIMERID_SPEED);
		}

		WORD   wVersion = CMD_GetFpgaVersion();
		BYTE btFpgaVersionMaj = wVersion >> 8;
		BYTE btFpgaVersionMin = wVersion & 0x00FF;
		sprintf_s(m_szBuf, _T("DeviceType: %s, Firmware Version( %d.%d),FPGA Version(%d.%d)"),
			g_szDeviceTypeB[(int)m_CtrlBoardType], m_btFwVersionMaj, m_btFwVersionMin, btFpgaVersionMaj, btFpgaVersionMin);
		
		InitialMega128Interface();
		InterfaceUpdateTriggerMode();
		m_nTimer = SetTimer(TIMERID_SPEED, 1000, NULL);
	}
	else
	{
		sprintf_s(m_szBuf, _T("Nuknown Device"));

		if (m_nTimer != 0)
		{
			KillTimer(TIMERID_SPEED);
		}
	}
}


void CKSJCtrlBoardDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == TIMERID_SPEED)
	{
		WORD wPulse = 0;
		float fTemp = 0;
		wPulse = CMD_GetMega8Message(1);
		if (0 == m_nTriggerModeIndex)
		{
			fTemp = ((PI * m_fCoderDiameter2) / m_nEncoderResolution2);
		}
		else if (1 == m_nTriggerModeIndex)
		{
			fTemp = ((PI * m_fCoderDiameter1) / m_nEncoderResolution1);
		}
		else if (2 == m_nTriggerModeIndex)
		{
			fTemp = ((PI * m_fCoderDiameter2) / m_nEncoderResolution2);
		}

		WORD wSpeed = (unsigned  short)(wPulse * fTemp * 10);
		CString strSpeed;
		strSpeed.Format("%d", wSpeed);
		m_Speed->SetWindowText(strSpeed);
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CKSJCtrlBoardDlg::SetType()
{
	m_CtrlBoardType = (KSJ_CTRL_BOARD_TYPE)CMD_GetDeviceType();
}


void CKSJCtrlBoardDlg::OnNMCustomdrawSliderTrigger(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	if (!m_bSlider)
	{
		m_bSlider = true;
		return;
	}

	*pResult = 0;
	m_bEdit = false;
	m_nLineTriggerPusles = ((CSliderCtrl*)GetDlgItem(IDC_SLIDER_TRIGGER))->GetPos();
	SetDlgItemInt(IDC_EDIT_TRIGGER, m_nLineTriggerPusles);
	if (m_bStart)
	{
		m_bAdjust = true;
		OnBnClickedCheckStart(FALSE);
		OnBnClickedCheckStart(TRUE);
		m_bAdjust = false;
	}
}


BOOL CKSJCtrlBoardDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)//屏蔽esc、enter、空格
		{
		case VK_ESCAPE:
		case VK_RETURN:
		case VK_SPACE:
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CKSJCtrlBoardDlg::OnEnChangeEditTrigger()
{
	if (!m_bEdit)
	{
		m_bEdit = true;
		return;
	}

	m_nLineTriggerPusles = GetDlgItemInt(IDC_EDIT_TRIGGER);
	m_bSlider = false;
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_TRIGGER))->SetPos(m_nLineTriggerPusles);
	if (m_bStart)
	{
		m_bAdjust = true;
		OnBnClickedCheckStart(FALSE);
		OnBnClickedCheckStart(TRUE);
		m_bAdjust = false;
	}
}
