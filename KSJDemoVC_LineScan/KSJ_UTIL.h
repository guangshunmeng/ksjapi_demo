#ifndef KSJ_UTIL_H__
#define KSJ_UTIL_H__

#ifdef __cplusplus
extern "C"{
#endif

BOOL CHAR2WCHAR( LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize );
BOOL WCHAR2CHAR( LPCWSTR lpcwszStr, LPSTR lpszStr, DWORD dwSize );

// ����ģ�������ļ��е�·�� �磺 C:\360����\����\Software\bin\��ע�����һ���ַ�Ϊ'\'
int  GET_MODULE_PATH(HMODULE hModule, TCHAR szPath[MAX_PATH]);

#ifdef __cplusplus
}
#endif

#endif
