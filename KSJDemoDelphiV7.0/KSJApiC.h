#ifndef __KSJ_API_C_H__
#define __KSJ_API_C_H__

#ifdef KSJAPI_EXPORTS
    #define KSJ_API __declspec(dllexport)
#else
    #define KSJ_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"{
#endif

// ����Ԥ���ӳ�
KSJ_API  int __stdcall KSJ_PreviewSetFieldOfView( int nChannel, int nColumnStart, int nRowStart, int nColumnSize, int nRowSize, KSJ_ADDRESSMODE ColumnAddressMode, KSJ_ADDRESSMODE RowAddressMode );
// ��ȡԤ���ӳ�
KSJ_API  int __stdcall KSJ_PreviewGetFieldOfView( int nChannel, int *pnColumnStart, int *pnRowStart, int *pnColumnSize, int *pnRowSize, KSJ_ADDRESSMODE *pColumnAddressMode, KSJ_ADDRESSMODE *pRowAddressMode );
// ��ȡ���û����õ��ӳ�ģʽ�£�Ԥ��ͼ��Ŀ�Ⱥ͸߶ȣ����أ�
KSJ_API  int __stdcall KSJ_PreviewGetSize       ( int nChannel, int *pnWidth, int *pnHeight );

KSJ_API  int __stdcall KSJ_PreviewGetSizeEx     ( int nChannel, int *pnWidth, int *pnHeight, int *pnBitCount );

// ����Ԥ��ͼ�����ʾλ��
KSJ_API  int __stdcall KSJ_PreviewSetPos        ( int nChannel, HWND hWnd, int x, int y, int nWidth, int nHeight );
// ��ȡԤ��ͼ�����ʾλ��
KSJ_API  int __stdcall KSJ_PreviewGetPos        ( int nChannel, int *px, int *py, int *pnWidth, int *pnHeight );
// ����Ԥ��ģʽ
enum KSJ_PREVIEWMODE { PM_RAWDATA, PM_RGBDATA };
KSJ_API  int __stdcall KSJ_PreviewSetMode       ( int nChannel, KSJ_PREVIEWMODE PreviewMode  );
// ��ȡԤ��ģʽ
KSJ_API  int __stdcall KSJ_PreviewGetMode       ( int nChannel, KSJ_PREVIEWMODE *pPreviewMode  );
// ������ֹͣԤ��
KSJ_API  int __stdcall KSJ_PreviewStart         ( int nChannel, bool bStart );
// ��ͣ�����Ԥ��
KSJ_API  int __stdcall KSJ_PreviewPause         ( int nChannel, bool bPause );
// ��ȡ��ͣʱ��ͼ�����ݣ��û����������KSJ_PreviewPause( , true); �ɹ�����á����ݵ�ǰ���õ�Ԥ��ģʽ��ȡ����Ӧ�����ݡ�
KSJ_API  int __stdcall KSJ_PreviewGetPausedData ( int nChannel, unsigned char *pData );

KSJ_API  int __stdcall KSJ_PreviewGetPausedDataEx ( int nChannel, unsigned char *pData, int *pnWidth, int *pnHeight, int *pnBitCount );

// ��ȡԤ��֡��
KSJ_API  int __stdcall KSJ_PreviewGetFrameRate  ( int nChannel, float *fFrameRate );
// ����Ԥ���ص�
typedef VOID (WINAPI *KSJ_PREVIEWCALLBACK )( unsigned char *pImageData, int nWidth, int nHeight, int nBitCount,  void *lpContext );
KSJ_API  int __stdcall KSJ_PreviewSetCallback   ( int nChannel, KSJ_PREVIEWCALLBACK pfPreviewCallback, void *lpContext );


// KSJ_API  int __stdcall KSJ_RecordStart( IN int nChannel, bool bStart );


#ifdef __cplusplus
}
#endif

#endif