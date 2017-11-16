#pragma once


// CPropertyPageTrigger �Ի���

class CPropertyPageTrigger : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropertyPageTrigger)

public:
	CPropertyPageTrigger();
	virtual ~CPropertyPageTrigger();

// �Ի�������
	enum { IDD = IDD_PAGETRIGGER };
	CKSJCamClass *m_pCam;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
private:
	bool m_bInitial;
	void SetFlash();
public:
	afx_msg void OnCbnSelchangeComboTimeout();
	afx_msg void OnBnClickedCheckRecover();
	afx_msg void OnCbnSelchangeComboMode();
	afx_msg void OnCbnSelchangeComboMethod();
	afx_msg void OnEnChangeEditDelay();
	afx_msg void OnEnChangeEditFixedFrameRateHw();
	afx_msg void OnBnClickedButtonEmptyFrameBuffer();
	afx_msg void OnBnClickedCheckInvert();
	afx_msg void OnBnClickedCheckFlashEnable();
};
