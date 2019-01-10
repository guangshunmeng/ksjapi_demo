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

// 设置预览视场
KSJ_API  int __stdcall KSJ_PreviewSetFieldOfView( int nChannel, int nColumnStart, int nRowStart, int nColumnSize, int nRowSize, KSJ_ADDRESSMODE ColumnAddressMode, KSJ_ADDRESSMODE RowAddressMode );
// 获取预览视场
KSJ_API  int __stdcall KSJ_PreviewGetFieldOfView( int nChannel, int *pnColumnStart, int *pnRowStart, int *pnColumnSize, int *pnRowSize, KSJ_ADDRESSMODE *pColumnAddressMode, KSJ_ADDRESSMODE *pRowAddressMode );
// 获取在用户设置的视场模式下，预览图像的宽度和高度（像素）
KSJ_API  int __stdcall KSJ_PreviewGetSize       ( int nChannel, int *pnWidth, int *pnHeight );

KSJ_API  int __stdcall KSJ_PreviewGetSizeEx     ( int nChannel, int *pnWidth, int *pnHeight, int *pnBitCount );

// 设置预览图像的显示位置
KSJ_API  int __stdcall KSJ_PreviewSetPos        ( int nChannel, HWND hWnd, int x, int y, int nWidth, int nHeight );
// 获取预览图像的显示位置
KSJ_API  int __stdcall KSJ_PreviewGetPos        ( int nChannel, int *px, int *py, int *pnWidth, int *pnHeight );
// 设置预览模式
enum KSJ_PREVIEWMODE { PM_RAWDATA, PM_RGBDATA };
KSJ_API  int __stdcall KSJ_PreviewSetMode       ( int nChannel, KSJ_PREVIEWMODE PreviewMode  );
// 获取预览模式
KSJ_API  int __stdcall KSJ_PreviewGetMode       ( int nChannel, KSJ_PREVIEWMODE *pPreviewMode  );
// 启动或停止预览
KSJ_API  int __stdcall KSJ_PreviewStart         ( int nChannel, bool bStart );
// 暂停或继续预览
KSJ_API  int __stdcall KSJ_PreviewPause         ( int nChannel, bool bPause );
// 获取暂停时的图像数据，用户必须调用了KSJ_PreviewPause( , true); 成功后调用。根据当前设置的预览模式，取得相应的数据。
KSJ_API  int __stdcall KSJ_PreviewGetPausedData ( int nChannel, unsigned char *pData );

KSJ_API  int __stdcall KSJ_PreviewGetPausedDataEx ( int nChannel, unsigned char *pData, int *pnWidth, int *pnHeight, int *pnBitCount );

// 获取预览帧速
KSJ_API  int __stdcall KSJ_PreviewGetFrameRate  ( int nChannel, float *fFrameRate );
// 设置预览回调
typedef VOID (WINAPI *KSJ_PREVIEWCALLBACK )( unsigned char *pImageData, int nWidth, int nHeight, int nBitCount,  void *lpContext );
KSJ_API  int __stdcall KSJ_PreviewSetCallback   ( int nChannel, KSJ_PREVIEWCALLBACK pfPreviewCallback, void *lpContext );


// KSJ_API  int __stdcall KSJ_RecordStart( IN int nChannel, bool bStart );


#ifdef __cplusplus
}
#endif

#endif