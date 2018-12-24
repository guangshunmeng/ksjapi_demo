#pragma once
#include "afxwin.h"

#include "KSJCamera.h"

class CKSJDemoVCDlg : public CDialogEx
{
public:
	CKSJDemoVCDlg(CWnd* pParent = NULL);	// standard constructor

	enum { IDD = IDD_KSJDEMOVC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();


private:
	CStatic m_SnapStatic1;
	CStatic m_SnapStatic2;
	CStatic m_SnapStatic3;
	CStatic m_SnapStatic4;

	CKSJCamera  m_KSJCamera;
public:
	afx_msg void OnBnClickedButtonStartpreview();
	afx_msg void OnBnClickedButtonChangetriggermode();
};
