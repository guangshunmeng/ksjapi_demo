#ifndef __KSJ_API_CUSTOM_H__
#define __KSJ_API_CUSTOM_H__

// #pragma message("Include KSJApiCustom.h") 

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

	// ��pData(���ΪnWidth, �߶�ΪnHeight, ����λ��ΪnBitCount)��ͼ����������Ϊ���ΪnStretchWidh, �߶�ΪnStretchHeight�����ݲ���䵽�û������pStretchData������,����λ������
	KSJ_API  int __stdcall KSJ_HelperStretchBmp(unsigned char *pData, int nWidth, int nHeight, int nBitCount, unsigned char *pStretchData, int nStretchWidth, int nStretchHeight);
	// ����ͼ��ı�����ȵõ�BMPͼ����ļ�ͷ,��Ϣͷ,����ɫ���ܵ��ֽ���Ŀ
	KSJ_API  int __stdcall KSJ_HelperGetBmpFileHeaderSize(int nBitCount, int *pnTotalBytes);
	// �õ�BMPͼ����ļ�ͷ����Ϣͷ
	KSJ_API  int __stdcall KSJ_HelperGetBmpFileHeader(int nWidth, int nHeight, int nBitCount, void *pHeader);
	// �ɼ�һ֡ͼ��ϵͳ������
	KSJ_API  int __stdcall KSJ_CaptureRgbDataToClipboard(int nChannel);


#ifdef __cplusplus
}
#endif

#endif
