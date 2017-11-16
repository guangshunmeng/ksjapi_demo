#ifndef KSJ_UTIL_H__
#define KSJ_UTIL_H__

#ifdef __cplusplus
extern "C"{
#endif

BOOL CHAR2WCHAR( LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize );
BOOL WCHAR2CHAR( LPCWSTR lpcwszStr, LPSTR lpszStr, DWORD dwSize );

// 返回模块所在文件夹的路径 如： C:\360云盘\程序\Software\bin\，注意最后一个字符为'\'
int  GET_MODULE_PATH(HMODULE hModule, TCHAR szPath[MAX_PATH]);

#ifdef __cplusplus
}
#endif

#endif
