
// KSJDemoVC_LineScan.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CKSJDemoVC_LineScanApp: 
// �йش����ʵ�֣������ KSJDemoVC_LineScan.cpp
//

class CKSJDemoVC_LineScanApp : public CWinApp
{
public:
	CKSJDemoVC_LineScanApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CKSJDemoVC_LineScanApp theApp;