
// KSJDemoVC_LineScanDlg.h : 头文件
//
#include "KSJCtrlBoardDlg.h"
#include "MyPropertySheet.h"
#include "PropertyPageNormal.h"
#include "PropertyPageTrigger.h"
#pragma once

#define WM_TRIGGER WM_USER + 200
// CKSJDemoVC_LineScanDlg 对话框
class CKSJDemoVC_LineScanDlg : public CDialogEx
{
// 构造
public:
	CKSJDemoVC_LineScanDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_KSJLINESCAN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
public:
	int m_nTriggerCount;
	void PreviewCallback();
// 实现
private:
	HICON m_hIcon;
	CKSJCtrlBoardDlg*	  m_pKSJCtrlBoardDlg;
	CMyPropertySheet	  m_SheetSettings;
	CPropertyPageNormal   m_PageNormal;
	CPropertyPageTrigger  m_PageTrigger;
	int m_nDeviceNum;
	int m_nDeviceCurSel;
	DEVICEINFO    m_DeviceInfo[MAX_DEVICE];
	int m_nComIndex;
	int m_nComBaud;
	int m_nComBytesSize;
	int m_nComStopBits;
	int m_nComParity;
	CKSJCamClass *m_pCam;
	
	void UpdateDeviceList();

protected:
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeComboType();
	afx_msg void OnCbnSelchangeComboComs();
	afx_msg void OnBnClickedButtonRefresh();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedCameraSet();
	afx_msg void OnBnClickedCtrlboardSet();
	afx_msg void OnDestroy();
	void UpdateUI();
	void ReadComParam();
	void WriteComParam();
	afx_msg void OnCbnSelchangeComboBaud();
	afx_msg void OnCbnSelchangeComboSize();
	afx_msg void OnCbnSelchangeComboParity();
	afx_msg void OnCbnSelchangeComboStop();
	afx_msg LRESULT OnMsgSetTrigger(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedCancel();
};
