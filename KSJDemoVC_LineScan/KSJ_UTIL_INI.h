#ifndef __KSJ_UTIL_INI_H__
#define __KSJ_UTIL_INI_H__

#ifdef __cplusplus
extern "C"{
#endif

// #define KSJINI_STATIC
#include "..\KSJIni.Inc\KSJIni.H"

#ifdef KSJINI_STATIC
#ifndef _WIN64
#ifdef _UNICODE
 #ifdef _DEBUG
  #pragma comment( lib, "..\\KSJIni.Lib\\KSJIniStaticud.Lib" )
  #define  INIFILENAME    _T("KSJCtrlBoard.ini")
 #else
#pragma comment( lib, "..\\KSJIni.Lib\\KSJIniStaticu.Lib" )
#define  INIFILENAME    _T("KSJCtrlBoard.ini")
#endif
#else
#ifdef _DEBUG
#pragma comment( lib, "..\\KSJIni.Lib\\KSJIniStaticd.Lib" )
#define  INIFILENAME    _T("KSJCtrlBoard.ini")
#else
#pragma comment( lib, "..\\KSJIni.Lib\\KSJIniStatic.Lib" )
#define  INIFILENAME    _T("KSJCtrlBoard.ini")
#endif
#endif

#else
#ifdef _UNICODE
#ifdef _DEBUG
#pragma comment( lib, "..\\KSJIni.Lib\\KSJIniStatic64ud.Lib" )
#define  INIFILENAME    _T("KSJCtrlBoard.ini")
#else
#pragma comment( lib, "..\\KSJIni.Lib\\KSJIniStatic64u.Lib" )
#define  INIFILENAME    _T("KSJCtrlBoard.ini")
#endif
#else
#ifdef _DEBUG
#pragma comment( lib, "..\\KSJIni.Lib\\KSJIniStatic64d.Lib" )
#define  INIFILENAME    _T("KSJCtrlBoard.ini")
#else
#pragma comment( lib, "..\\KSJIni.Lib\\KSJIniStatic64.Lib" )
#define  INIFILENAME    _T("KSJCtrlBoard.ini")
#endif
#endif
#endif

#else
#ifndef _WIN64
#ifdef _UNICODE
#ifdef _DEBUG
#pragma comment( lib, "..\\KSJIni.Lib\\MTd_KSJIni_x64.Lib" )
#define  INIFILENAME    _T("KSJCtrlBoard.ini")
#else
#pragma comment( lib, "..\\KSJIni.Lib\\MT_KSJIni_x64.Lib" )
#define  INIFILENAME    _T("KSJCtrlBoard.ini")
#endif
#else
#ifdef _DEBUG
#pragma comment( lib, "..\\KSJIni.Lib\\MTd_KSJIni_x86.Lib" )
#define  INIFILENAME    _T("KSJCtrlBoard.ini")
#else
#pragma comment( lib, "..\\KSJIni.Lib\\MT_KSJIni_x86.Lib" )
#define  INIFILENAME    _T("KSJCtrlBoard.ini")
#endif
#endif
#endif

extern HANDLE   g_hKSJIni;
extern HANDLE   g_hIni;
VOID InitialIni(HMODULE hModule);
VOID CloseIni();


#ifdef __cplusplus
}
#endif

#endif
#endif