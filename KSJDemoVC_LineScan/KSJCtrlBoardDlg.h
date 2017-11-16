#pragma once

#include "Resource.h"
// CKSJCtrlBoardDlg 对话框

class CKSJCtrlBoardDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CKSJCtrlBoardDlg)

public:
	CKSJCtrlBoardDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CKSJCtrlBoardDlg();

// 对话框数据
	enum { IDD = IDD_KSJCTRLBOARD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

private:
	int SetTriggerMode0(
		int nCurCom,
		unsigned char ucStart,
		unsigned char ucOutputChannel,
		unsigned char ucOutputTriggerMethod,
		unsigned short usOutputFreq,
		unsigned short usOutputPulseNum);

	int SetTriggerMode1(
		int nCurCom,
		unsigned char ucStart,
		unsigned char ucOutputChannel,
		unsigned char ucOutputTriggerMethod,
		unsigned char ucTriggerInputChannel,
		unsigned char ucDelayMode,
		unsigned short usDelayCounter);


	int SetTriggerMode2(
		int nCurCom,
		unsigned char ucStart,
		unsigned char ucOutputChannel,
		unsigned char ucOutputTriggerMethod,
		unsigned char m_ucTriggerInputChannelMode2,
		unsigned char m_ucDelayModeMode2,
		unsigned short m_usDelayCounterMode2,
		unsigned short usTriggerNumPerCircleMode2,
		unsigned short usNumofBufferMode2);

public:
	int m_nComIndex;

	int m_nTriggerModeIndex;
	int m_nInputSourceIndex;
	int m_nTriggerMethodIndex;

	WORD   m_wOutputFreq;        // 触发模式0的时候，触发相机的频率
	WORD   m_wOutputPulseNum;    // 触发模式0的时候，触发相机的次数
	BOOL   m_bInfinite;          // 无限次触发相机

	int    m_nDelayModeIndex;
	int    m_nDelayCountMethodIndex;

	WORD m_wDelayCount;    // 接收到外触发信号后经过多少个计数脉冲之后开始触发相机
	WORD m_wDelayTime;
	int m_nOutputChannelIndex;

	BYTE  m_btFwVersionMaj;
	BYTE  m_btFwVersionMin;

	float m_fWidthOfViewMM;
	int m_nColSize;
	int m_nRowSize;
	int m_nMultiFrames;
	float m_fCoderDiameter1;
	int m_nEncoderResolution1;
	float m_fCoderDiameter2;
	int m_nEncoderResolution2;
	int m_nTimer;
	TCHAR   m_szBuf[128];
	CWnd *m_Speed;

private:
	void InterfaceUpdateDelayCountMethod();
	void InterfaceUpdateTriggerMode();
	float CalculateDelayDistance();
	float CalculateDelayTime();


private:
	void InitialUnoInterface();
	void UpdateUnoInterface();

private:
	CB_UNO_CMD m_UNO_Command[UNO_OUTPUT_CHANNEL_NUM];

public:
	KSJ_CTRL_BOARD_TYPE    m_CtrlBoardType;
	bool m_bInitial;

public:
	WORD CMD_GetDeviceType();
	WORD CMD_GetFwVersion();
	WORD CMD_GetMega8Message(int type);
	void Start_Uno(BOOL bStart);
	int  CMD_SetUno(BYTE btChannel, WORD wTriggerSpeed, WORD wPulseNum);
	int  CMD_StartUno(BYTE btChannel, BOOL bStart);
	int  CMD_ReadUno(BYTE btChannel);
	void Start_Mega128(WORD wMultiFrames, BOOL bStart);
	int  CMD_SetMega128(WORD wMultiFrames);
	int  CMD_StartMega128(WORD wMultiFrames, BOOL bStart);
	void InitialMega128Interface();
	WORD CMD_GetFpgaVersion();
	void CMD_SetFlashlight(unsigned char type, unsigned char param);
	void ShowResult(int nRet);
	void UnenableMega128Interface();
private:
	int m_nFreq;
public:
	afx_msg void OnCbnSelchangeComboOutputChannel();
	afx_msg void OnCbnSelchangeComboTriggerMode();
	afx_msg void OnCbnSelchangeComboInputSource();
	afx_msg void OnCbnSelchangeComboTriggerMethod();
	afx_msg void OnEnChangeEditOutputFreq();
	afx_msg void OnEnChangeEditOutputNum();
	afx_msg void OnCbnSelchangeComboDelayMode();
	afx_msg void OnEnChangeEditDelayTime();
	afx_msg void OnCbnSelchangeComboDelayCountMothed();
	afx_msg void OnEnChangeEditDelayCount();
	afx_msg void OnEnChangeEditColSize();
	afx_msg void OnEnChangeEditWidthMm();
	afx_msg void OnEnChangeEditRowSize();
	afx_msg void OnEnChangeEditMultiFrames();
	afx_msg void OnBnClickedButtonSetFlashtime();
	afx_msg void OnBnClickedButtonSetPreflashtime();
	afx_msg void OnBnClickedCheckFlashmode();
	afx_msg void OnDestroy();
	void OnBnClickedCheckStart(BOOL bStart);
	void ReadIni();
	void WriteIni();
	void UpdateType();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void SetType();
};
