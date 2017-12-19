
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��
#include <afxdlgs.h>


#define ENCODER_DIAMETER    400   // �����������ӵĹ���ֱ��PHi��fai��
#define ENCODER_RESOLUTION  2000  // ������תһȦ���͵�������
#define PI                  3.1415926f
#define COL_WIDTH_PRESION   100
#define COL_FORMAT          _T("%.2f")

#define COL_SIZE_MIN        1
#define COL_SIZE_MAX        4096
#define COL_SIZE_DEF        1280

#define COL_WIDTH_MIN        0       // ��λMM
#define COL_WIDTH_MAX        100     // ��λMM
#define COL_WIDTH_DEF        24      // ��λMM

#define ROW_SIZE_MIN        1
#define ROW_SIZE_MAX        1024
#define ROW_SIZE_DEF        4

#define MULTI_FRAMES_MIN    1
#define MULTI_FRAMES_MAX    32767
#define MULTI_FRAMES_DEF    255

#define DELAY_COUNT_PULSE_MIN 0
#define DELAY_COUNT_PULSE_MAX 32767
#define DELAY_COUNT_PULSE_DEF 0
#define DELAY_COUNT_PULSE_FORMAT          _T("%d")


#define DELAY_DISTANCE_MIN   0
#define DELAY_DISTANCE_MAX   32767    // mm
#define DELAY_DISTANCE_DEF   0
#define DELAY_DISTANCE_FORMAT          _T("%.2f")
#define DELAY_DISTANCE_PRESION   100

#define DELAY_TIME_MIN   0
#define DELAY_TIME_MAX   5000    // ms
#define DELAY_TIME_DEF   0
#define DELAY_TIME_FORMAT          _T("%.1f")


//// #pragma warning(disable : 4996)
#include "COMMON_PROTOCOL.h"
#include "UNO_PROTOCOL.h"
#include "MEGA128_PROTOCOL.h"
#include "KSJ_GS_CB.h"
#include "KSJ_UTIL.h"
#include "KSJ_UTIL_INI.h"

#include "KSJCamClass.h"

#include "..\KSJApi.Inc\KSJApi.h"
#include "..\Common\KSJ_GS.H"
#ifdef _WIN64
#ifdef _DEBUG
#pragma comment( lib, "..\\KSJApi.Lib\\KSJApi64d.lib" )
#else
#pragma comment( lib, "..\\KSJApi.Lib\\KSJApi64.lib" )
#endif
#else
#ifdef _DEBUG
#pragma comment( lib, "..\\KSJApi.Lib\\KSJApi.lib" )
#else
#pragma comment( lib, "..\\KSJApi.Lib\\KSJApi.lib" )
#endif
#endif

#include "..\KSJCom.Inc\KSJCom.h"
#ifdef _WIN64
#ifdef _DEBUG
#pragma comment( lib, "..\\KSJCom.Lib\\win32\\MTd_KSJCom_x64.lib" )
#else
#pragma comment( lib, "..\\KSJCom.Lib\\win32\\MT_KSJCom_x64.lib" )
#endif
#else
#ifdef _DEBUG
#pragma comment( lib, "..\\KSJCom.Lib\\win32\\MTd_KSJCom_x86.lib" )
#else
#pragma comment( lib, "..\\KSJCom.Lib\\win32\\MT_KSJCom_x86.lib" )
#endif
#endif
#define MAX_DEVICE    64

struct DEVICEINFO
{
	int                 nIndex;
	KSJ_DEVICETYPE		DeviceType;
	int					nSerials;
	WORD				wFirmwareVersion;
	WORD                wFpgaVersion;
};

static TCHAR* g_szHueRange[] =
{
	_T("ALL"),
	_T("RED"),
	_T("YELLOW"),
	_T("GREEN"),
	_T("CYAN"),
	_T("BLUE"),
	_T("MAGENTA")
};

static TCHAR* g_szTimeOut[] =
{
	_T("Default 5S"),
	_T("Infinite"),
	_T("500mS"),
	_T("1S"),
	_T("2S"),
};

static int    g_nTimeOut[] =
{
	5000, 0xFFFFFFFF, 500, 1000, 2000
};
static int g_nHueRange = sizeof(g_szHueRange) / sizeof(TCHAR*);;


extern int g_nMultiFrames;
#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


