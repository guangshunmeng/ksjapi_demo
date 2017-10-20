// KSJDemoVC6_BaseDlg.h : header file
//

#if !defined(AFX_KSJDEMOVC6_BASEDLG_H__F806BE1E_E638_448E_A1BC_B3C98C7310B7__INCLUDED_)
#define AFX_KSJDEMOVC6_BASEDLG_H__F806BE1E_E638_448E_A1BC_B3C98C7310B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "SnapStatic.h"

#define MAX_DEVICE    64

struct DEVICEINFO
{
	int                 nIndex;
	KSJ_DEVICETYPE		DeviceType;
	int					nSerials;
	WORD				wFirmwareVersion;
	WORD                wFpgaVersion;
};


struct MSG_UPDATE_SNAP_STATIC_CONTEXT
{
	BYTE *pImageData;
	int  nCaptureWidth;
	int  nCaptureHeight;
	int  nCaptureBitCount;
	float fElapse;
};


#define WM_UPDATE_SNAP_STATIC    WM_USER + 2
#define WM_CAPTURE_START         WM_USER + 1
#define TIMERID_GET_FRAME_RATE   2
/////////////////////////////////////////////////////////////////////////////
// CKSJDemoVC6_BaseDlg dialog

class CKSJDemoVC6_BaseDlg : public CDialog
{
// Construction
public:
	void UpdateInterfaceFunction();
	CKSJDemoVC6_BaseDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CKSJDemoVC6_BaseDlg)
	enum { IDD = IDD_KSJDEMOVC6_BASE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKSJDemoVC6_BaseDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
private:
	void UpdateDeviceList();
	void UpdateInterface();
	void GetRealExposureTime();
	int m_nDeviceNum;
	int m_nDeviceCurSel;
	DEVICEINFO    m_DeviceInfo[MAX_DEVICE];
	CSnapStatic m_SnapStatic;
	
	BOOL        m_bInitial;

	afx_msg LRESULT MsgUpdateSnapStatic(WPARAM wParam, LPARAM lParam);
	void ShowErrorInfo(int nRet);
	// Generated message map functions
	//{{AFX_MSG(CKSJDemoVC6_BaseDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnSelchangeComboDeviceList();
	afx_msg void OnChangeEditExposureTimeMs();
	afx_msg void OnChangeEditExposureLines();
	afx_msg void OnChangeEditGain();
	afx_msg void OnButtonPreviewFovSet();
	afx_msg void OnCheckPreviewstart();
	afx_msg void OnButtonCaptureFovSet();
	afx_msg void OnCapture();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KSJDEMOVC6_BASEDLG_H__F806BE1E_E638_448E_A1BC_B3C98C7310B7__INCLUDED_)
