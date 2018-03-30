#ifndef __KSJ_API_PROGRAM_H__
#define __KSJ_API_PROGRAM_H__

// #pragma message("Include KSJApiProgram.h") 

#ifdef KSJAPI_EXPORTS
#define KSJ_API __declspec(dllexport)
#elif defined KSJAPI_STATIC
#define KSJ_API
#else
#define KSJ_API __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"{
#endif
	// �ο������Ӽѹ�ҵ����ڲ�API����˵���飨��ʼ�����̶�д����ƪ����
	// Program and Modify Serials
	KSJ_API  int __stdcall KSJ_SetSerials(int nChannel, unsigned char btSerials);
	KSJ_API  int __stdcall KSJ_GetSerials(int nChannel, unsigned char *pbtSerials);

	KSJ_API  int __stdcall KSJ_WorkingModeProgram(int nChannel, unsigned short wValue);
	KSJ_API  int __stdcall KSJ_WorkingModeReadout(int nChannel, unsigned short *pValue);

	KSJ_API  int __stdcall KSJ_WorkingModeExProgram(int nChannel, unsigned short wValue);
	KSJ_API  int __stdcall KSJ_WorkingModeExReadout(int nChannel, unsigned short *pValue);

	KSJ_API  int __stdcall KSJ_ColorModeProgram(int nChannel, unsigned short wValue);
	KSJ_API  int __stdcall KSJ_ColorModeReadout(int nChannel, unsigned short *pValue);

	KSJ_API  int __stdcall KSJ_SerialsDescProgram(int nChannel, unsigned char btDesc[16]);
	KSJ_API  int __stdcall KSJ_SerialsDescReadout(int nChannel, unsigned char btDesc[16]);

	KSJ_API  int __stdcall KSJ_LutInfoProgram(int nChannel, unsigned short wValue);
	KSJ_API  int __stdcall KSJ_LutInfoReadout(int nChannel, unsigned short *pValue);

	KSJ_API  int __stdcall KSJ_GammaLutInfoProgram(int nChannel, unsigned short wValue);
	KSJ_API  int __stdcall KSJ_GammaLutInfoReadout(int nChannel, unsigned short *pValue);

	KSJ_API  int __stdcall KSJ_HWBMatrixProgram(int nChannel, float fMatrix[3]);
	KSJ_API  int __stdcall KSJ_HWBMatrixReadout(int nChannel, float fMatrix[3]);
	KSJ_API  int __stdcall KSJ_HWBMatrixUpload(int nChannel, float fMatrix[3]);

	KSJ_API  int __stdcall KSJ_HCCMMatrixProgram(int nChannel, float fMatrix[3][3]);
	KSJ_API  int __stdcall KSJ_HCCMMatrixReadout(int nChannel, float fMatrix[3][3]);
	KSJ_API  int __stdcall KSJ_HCCMMatrixUpload(int nChannel, float fMatrix[3][3]);

	KSJ_API  int __stdcall KSJ_LutFileProgram(int nChannel, TCHAR *pszFile);
	KSJ_API  int __stdcall KSJ_LutDataProgram(int nChannel, unsigned char *pData, int nBytes);
	KSJ_API  int __stdcall KSJ_LutDataReadout(int nChannel, unsigned char *pData, int *pnBytes);

	KSJ_API  int __stdcall KSJ_GammaLutFileProgram(int nChannel, TCHAR *pszFile);
	KSJ_API  int __stdcall KSJ_GammaLutDataProgram(int nChannel, unsigned short *pData, int nWords);
	KSJ_API  int __stdcall KSJ_GammaLutDataReadout(int nChannel, unsigned short *pData, int *pnWords);


#ifdef __cplusplus
}
#endif

#endif