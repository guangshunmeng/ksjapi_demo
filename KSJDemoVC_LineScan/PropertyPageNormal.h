#pragma once

#include "Resource.h"
// CPropertyPageNormal �Ի���

class CPropertyPageNormal : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropertyPageNormal)

public:
	CPropertyPageNormal();
	virtual ~CPropertyPageNormal();

// �Ի�������
	enum { IDD = IDD_PAGENORMAL };
	CKSJCamClass *m_pCam;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
private:
	bool m_bInitial;
	bool m_bMultiFrame;
	bool m_bUsed;
	int  m_nSegIndex;
public:
	afx_msg void OnBnClickedButtonApply();
	afx_msg void OnEnChangeEditGainRed();
	afx_msg void OnEnChangeEditGainGreen();
	afx_msg void OnEnChangeEditGainBlue();
	afx_msg void OnEnChangeEditExposureTimeMs();
	afx_msg void OnEnChangeEditExposureLines();
};
