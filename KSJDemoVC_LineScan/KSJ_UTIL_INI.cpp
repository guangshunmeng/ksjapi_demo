#include "stdafx.h"
#include "KSJ_UTIL.H"
#include "KSJ_UTIL_INI.H"

HANDLE   g_hKSJIni = NULL;
HANDLE   g_hIni = NULL;
VOID InitialIni( HMODULE hModule )
{
	TCHAR   szPath[MAX_PATH] = { '\0' };
	GET_MODULE_PATH(hModule, szPath);
	lstrcat(szPath, INIFILENAME);
	OutputDebugString(szPath);
	KSJINI_Init(&g_hKSJIni, szPath); // ��ʼ���������ᴴ��ini�ļ���ֻ�ж�ini�ļ�����д���ʱ��Ż��Զ�������
	memset(szPath, 0, sizeof(szPath));
	GET_MODULE_PATH(hModule, szPath);
	lstrcat(szPath, "Param.ini");
	KSJINI_Init(&g_hIni, szPath);
}

VOID CloseIni()
{
	KSJINI_UnInit(&g_hKSJIni);
	KSJINI_UnInit(&g_hIni);
}