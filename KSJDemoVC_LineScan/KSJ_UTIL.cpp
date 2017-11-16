#include "stdafx.h"
#include "KSJ_UTIL.h"

//////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------------------  
//Description:  
// This function maps a character string to a wide-character (Unicode) string  
//  
//Parameters:  
// lpcszStr: [in] Pointer to the character string to be converted   
// lpwszStr: [out] Pointer to a buffer that receives the translated string.   
// dwSize: [in] Size of the buffer  
//  
//Return Values:  
// TRUE: Succeed  
// FALSE: Failed  
//   
//Example:  

// MByteToWChar(szA,szW,sizeof(szW)/sizeof(szW[0]));  

//---------------------------------------------------------------------------------------  
BOOL CHAR2WCHAR( LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize )  
{  
	// Get the required size of the buffer that receives the Unicode   
	// string.   
	DWORD dwMinSize;  
	dwMinSize = MultiByteToWideChar (CP_ACP, 0, lpcszStr, -1, NULL, 0);  
	if(dwSize < dwMinSize)  
	{  
		return FALSE;  
	}  
	// Convert headers from ASCII to Unicode.  
	MultiByteToWideChar (CP_ACP, 0, lpcszStr, -1, lpwszStr, dwMinSize);    
	return TRUE;  
}  

//-------------------------------------------------------------------------------------  
//Description:  
// This function maps a wide-character string to a new character string  
//  
//Parameters:  
// lpcwszStr: [in] Pointer to the character string to be converted   
// lpszStr:   [out] Pointer to a buffer that receives the translated string.   
// dwSize:    [in] Size of the buffer  
//  
//Return Values:  
// TRUE: Succeed  
// FALSE: Failed  
//   
//Example:  
// WCHAR2CHAR( szW, szA, sizeof(szA)/sizeof(szA[0]) );  
//---------------------------------------------------------------------------------------  
BOOL WCHAR2CHAR( LPCWSTR lpcwszStr, LPSTR lpszStr, DWORD dwSize )  
{  
	DWORD dwMinSize;  
	dwMinSize = WideCharToMultiByte( CP_OEMCP, NULL, lpcwszStr, -1, NULL, 0, NULL, FALSE ); 

	if( dwSize < dwMinSize )  
	{  
		return FALSE;  
	}  
	
	WideCharToMultiByte( CP_OEMCP, NULL, lpcwszStr, -1, lpszStr, dwSize, NULL, FALSE ); 

	return TRUE;  
}  

int GET_MODULE_PATH(HMODULE hModule, TCHAR szPath[MAX_PATH])
{
	TCHAR sDrive[MAX_PATH];
	TCHAR sDir[MAX_PATH];
	TCHAR sFilename[MAX_PATH];
	TCHAR sExt[MAX_PATH];

	TCHAR sFilePathAndName[MAX_PATH];
	GetModuleFileName(hModule, sFilePathAndName, MAX_PATH);        // KSJApi.dll的全路径，包括文件名C:\360云盘\程序\Software\bin\KSJApid.dll

	_tsplitpath(sFilePathAndName, sDrive, sDir, sFilename, sExt);  // sDrive = C: 
	                                                               // sDir = \360云盘\程序\Software\bin\

	memcpy(szPath, sDrive, _tcslen(sDrive)* sizeof(TCHAR));
	memcpy(szPath + _tcslen(sDrive), sDir, _tcslen(sDir)* sizeof(TCHAR));		// KSJApi.dll所在文件夹的目录C:\360云盘\程序\Software\bin\

	return _tcslen(szPath) * sizeof(TCHAR);			                            // 返回字节个数，不包括终止标志NULL
}