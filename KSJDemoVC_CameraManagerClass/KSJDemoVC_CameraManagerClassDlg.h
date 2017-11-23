
// KSJDemoVC_CameraManagerClassDlg.h : ͷ�ļ�
//
#include "KSJCameraManager.h"
#pragma once


// CKSJDemoVC_CameraManagerClassDlg �Ի���
class CKSJDemoVC_CameraManagerClassDlg : public CDialogEx
{
// ����
public:
	CKSJDemoVC_CameraManagerClassDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CKSJDemoVC_CameraManagerClassDlg();

// �Ի�������
	enum { IDD = IDD_KSJDEMOVC_CAMERAMANAGERCLASS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	CKSJCameraManager *m_CameraManager;
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void UpdateUI();
	afx_msg void OnEnChangeEditExtime1();
	afx_msg void OnEnChangeEditExlines1();
	afx_msg void OnEnChangeEditGain1();
	afx_msg void OnBnClickedCheckPreviewstart1();
	afx_msg void OnBnClickedCheckPause1();
	afx_msg void OnEnChangeEditExtime2();
	afx_msg void OnEnChangeEditExlines2();
	afx_msg void OnEnChangeEditGain2();
	afx_msg void OnBnClickedCheckPreviewstart2();
	afx_msg void OnBnClickedCheckPause2();
	afx_msg void OnEnChangeEditExtime3();
	afx_msg void OnEnChangeEditExlines3();
	afx_msg void OnEnChangeEditGain3();
	afx_msg void OnBnClickedCheckPreviewstart3();
	afx_msg void OnBnClickedCheckPause3();
};
