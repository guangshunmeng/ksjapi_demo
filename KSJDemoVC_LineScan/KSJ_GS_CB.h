#ifndef _KSJSTRING_H__
#define _KSJSTRING_H__

#include "windows.h"
#include "tchar.h"

static const TCHAR* g_szDeviceTypeB[] =
{
	_T("CatchBEST UNO Control Board"),
	_T("CatchBEST Mega128 Control Board"),
	_T("Unknown Control Board")
};

static TCHAR *g_szTriggerModeB[] =
{
	_T("Trigger Mode 0 "),
	_T("Trigger Mode 1 "),
	_T("Trigger Mode 2 "),
	_T("Trigger Mode 3 "),
	_T("Trigger Mode 4 ")
};

static TCHAR *g_szOutputChannel[] =
{
	_T("Channel 0"),
	_T("Channel 1")
};

static TCHAR *g_szTriggerMethodB[] =
{
	_T("Rising Edge"),
	_T("Falling Edge"),
	_T("High Level"),
	_T("Low Level")
};

static TCHAR *g_szInputSource[] =
{
	_T("Source 0"),
	_T("Source 1"),
	_T("Encode Z")
};

static TCHAR *g_szDelayMode[] = 
{
	_T("Mode 0, Internal Timer Count"),
	_T("Mode 1, External Pluse Count")

};

static TCHAR *g_szDelayCountMethod[] =
{
	_T("Pluse Count"),
	_T("Distance(mm)"),
};

#endif