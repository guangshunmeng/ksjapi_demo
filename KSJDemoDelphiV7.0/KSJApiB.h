/*=================================================================
	凯视佳工业高质高清工业相机API函数声明文件
	网址：    www.catchbest.com
	技术支持：catchbest.support@hotmail.com
  -----------------------------------------------------------------*/

#ifndef __KSJ_API_B_H__
#define __KSJ_API_B_H__


#ifdef KSJAPI_EXPORTS
    #define KSJ_API __declspec(dllexport)
#else
    #define KSJ_API __declspec(dllimport)
#endif

/*=================================================================
	以下函数为KSJApi.dll导出函数。
	在你的应用程序中，你应该包含KSJAPI.H并链接KSJApi.LIB。
	然后你就可以调用下面的导出函数。
  -----------------------------------------------------------------*/

#ifdef __cplusplus
extern "C"{
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef OPTIONAL
#define OPTIONAL
#endif

// 获得错误的详细信息，可以在任何时候调用
KSJ_API  int __stdcall KSJ_GetErrorInfo( int nErrorNo, char pszErrorInfo[256] );
// 初始化KSJApi动态库
KSJ_API  int __stdcall KSJ_Init( void );
// 反初始化KSJApi动态库
KSJ_API  int __stdcall KSJ_UnInit( void );
// 得到设备数目
KSJ_API  int __stdcall KSJ_DeviceGetCount( void );

// 凯视佳工业相机设备类型定义：M-Mircon Sensor, R-Rolling Shutter, N-No External Trigger, N-No Frame Buffer
enum KSJ_DEVICETYPE 
{ 
	KSJ_UC130C_MRNN = 0, 
	KSJ_UC130M_MRNN, 
	KSJ_UC200C_MRNN, 
	KSJ_UC320C_MRNN, 
	KSJ_UC130C_MRYN, 
	KSJ_UC130M_MRYN, 
	KSJ_UC200C_MRYN, 
	KSJ_UC320C_MRYN, 
	KSJ_UC500C_MRNN, 
	KSJ_UC500M_MRNN, 
	KSJ_UC500C_MRYN, 
	KSJ_UC500M_MRYN, 
	KSJ_UC320C_OCR, 
	KSJ_UC900C_MRNN, 
	KSJ_UC1000C_MRNN, 
	KSJ_UC900C_MRYN, 
	KSJ_UC1000C_MRYN, 
	KSJ_UC130C_MRYY, 
	KSJ_UC130M_MRYY, 
	KSJ_UD140C_SRNN, 
	KSJ_UD140M_SRNN, 
	KSJ_UC36C_MGNN, 
	KSJ_UC36M_MGNN 
};
// 得到设备信息（型号，序号，固件版本号）
KSJ_API  int __stdcall KSJ_DeviceGetInformation( IN int nChannel, OUT KSJ_DEVICETYPE *pDeviceType, OUT int *pnIndex, OUT unsigned short *pwFirmwareVersion );
// 抽点模式定义（分为列抽点和行抽点）：
enum KSJ_ADDRESSMODE { KSJ_SKIPNONE = 0, KSJ_SKIP2, KSJ_SKIP3, KSJ_SKIP4, KSJ_SKIP8 };
// 设置采集视场大小
KSJ_API  int __stdcall KSJ_CaptureSetFieldOfView( int nChannel, int nColumnStart, int nRowStart, int nColumnSize, int nRowSize, KSJ_ADDRESSMODE ColumnAddressMode, KSJ_ADDRESSMODE RowAddressMode );
// 获取采集视场的实际大小
KSJ_API  int __stdcall KSJ_CaptureGetFieldOfView( int nChannel, int *pnColumnStart, int *pnRowStart, int *pnColumnSize, int *pnRowSize, KSJ_ADDRESSMODE *pColumnAddressMode, KSJ_ADDRESSMODE *pRowAddressMode );
// 得到采集图像的宽度和高度（单位：像素）
KSJ_API  int __stdcall KSJ_CaptureGetSize( int nChannel, int *pnWidth, int *pnHeight );

KSJ_API  int __stdcall KSJ_CaptureGetSizeEx( int nChannel, int *pnWidth, int *pnHeight, int *pnBitCount );

// 采集一帧原始数据图像数据
KSJ_API  int __stdcall KSJ_CaptureRawData     ( int nChannel, unsigned char *pRawData );
// 采集一帧8灰度图像或24或32位彩色图像数据（与KSJ_BayerSetMode和KSJ_PreviewSetMode相关）
KSJ_API  int __stdcall KSJ_CaptureRgbData     ( int nChannel, unsigned char *pRgbData );

KSJ_API  int __stdcall KSJ_CaptureRgbDataEx   ( int nChannel, unsigned char *pRgbData, int *pnWidth, int *pnHeight, int *pnBitCount );

// 相机参数
enum KSJ_PARAM { 
	KSJ_EXPOSURE = 0, 
	KSJ_RED, 
	KSJ_GREEN, 
	KSJ_BLUE, 
	KSJ_GAMMA, 
	KSJ_PREVIEW_COLUMNSTART, 
	KSJ_PREVIEW_ROWSTART, 
	KSJ_CAPTURE_COLUMNSTART, 
	KSJ_CAPTURE_ROWSTART, 
	KSJ_HORIZONTALBLANK, 
	KSJ_VERTICALBLANK, 
	KSJ_FLIP, 
	KSJ_BIN, 
	KSJ_MIRROR, 
	KSJ_CONTRAST, 
	KSJ_BRIGHTNESS, 
	KSJ_VGAGAIN, 
	KSJ_CLAMPLEVEL, 
	KSJ_CDSGAIN,
	KSJ_RED_SHIFT,
	KSJ_GREEN_SHIFT,
	KSJ_BLUE_SHIFT,
    KSJ_COMPANDING
};
// 获得参数的设置范围
KSJ_API  int __stdcall KSJ_GetParamRange( IN int nChannel, IN KSJ_PARAM Param, OUT int *pnMinValue, OUT int *pnMaxValue );
// 设置参数
KSJ_API  int __stdcall KSJ_SetParam     ( IN int nChannel, IN KSJ_PARAM Param, IN  int nValue );
// 获取参数当前值
KSJ_API  int __stdcall KSJ_GetParam     ( IN int nChannel, IN KSJ_PARAM Param, OUT int *pnValue );

// 设置Gamma值，范围 -9 - +9
KSJ_API  int __stdcall KSJ_GammaSetValue( int nChannel, int nValue );
// 打开或关闭Gamma校正，即影响预览又影响采集
KSJ_API  int __stdcall KSJ_GammaOn( int nChannel, bool bOn );

// 枚举类型贝耶尔模式
enum KSJ_BAYERMODE { KSJ_BGGR_BGR24 = 0, KSJ_GRBG_BGR24, KSJ_RGGB_BGR24, KSJ_GBRG_BGR24, KSJ_BGGR_BGR24_FLIP, KSJ_GRBG_BGR24_FLIP,  KSJ_RGGB_BGR24_FLIP, KSJ_GBRG_BGR24_FLIP, 
                     KSJ_BGGR_BGR32,     KSJ_GRBG_BGR32, KSJ_RGGB_BGR32, KSJ_GBRG_BGR32, KSJ_BGGR_BGR32_FLIP, KSJ_GRBG_BGR32_FLIP,  KSJ_RGGB_BGR32_FLIP, KSJ_GBRG_BGR32_FLIP,
                     KSJ_BGGR_GRAY8,     KSJ_GRBG_GRAY8, KSJ_RGGB_GRAY8, KSJ_GBRG_GRAY8, KSJ_BGGR_GRAY8_FLIP, KSJ_GRBG_GRAY8_FLIP,  KSJ_RGGB_GRAY8_FLIP, KSJ_GBRG_GRAY8_FLIP };
// 设置Bayer模式，同时影响采集和预览，这个函数除特殊需要调用，否则用户不需调用此功能。
KSJ_API   int __stdcall KSJ_BayerSetMode( int nChannel, KSJ_BAYERMODE BayerMode );
// 获得当前Bayer模式
KSJ_API   int __stdcall KSJ_BayerGetMode( int nChannel, KSJ_BAYERMODE *pBayerMode );

// 设置自动曝光的区域，这个区域是相对预览图像的左上角像素位置
KSJ_API  int __stdcall KSJ_AESetRegion( int nChannel, int nX, int nY,  int nW, int nH );

// 自动曝光回调函数
typedef void (__stdcall *KSJ_AECALLBACK )( bool bSuccess, int nResult,  void *lpContext );
// 定义自动曝光操作结束后的回调函数，当自动曝光结束时，KSJ开发包会自动调用AECallback用户指定的回调函数
KSJ_API  int __stdcall KSJ_AESetCallback( int nChannel, KSJ_AECALLBACK pfAECallback, void *lpContext );
// 开始或终止自动曝光调节
KSJ_API  int __stdcall KSJ_AEStart( int nChannel, bool bStart, int nMaxCount, int nTarget );


// 设置自动白平衡区域
KSJ_API  int __stdcall KSJ_AWBSetRegion( int nChannel, int nX, int nY,  int nW, int nH );
// 自动白平衡回调函数
typedef void (__stdcall *KSJ_AWBCALLBACK )( bool bSuccess, int nRValue, int nGValue, int nBValue,  void *lpContext );
// 定义自动白平衡（操作硬件）操作结束后的回调函数，当自动曝光结束时，KSJ开发包会自动调用AECallback用户指定的回调函数
KSJ_API  int __stdcall KSJ_AWBSetCallback( int nChannel, KSJ_AWBCALLBACK fpAWBCallback, void *lpContext );
// 开始或终止自动白平衡调节
KSJ_API  int __stdcall KSJ_AWBStart( int nChannel, bool bStart, int nMaxCount, int nRTarget, int nGTarget, int nBTarget );

typedef void (__stdcall *KSJ_CCCALLBACK )( bool bSuccess, int nRShift, int nGShift, int nBShift,  void *lpContext );

// 如下函数为软件颜色校正
KSJ_API  int __stdcall KSJ_ColorCorrectSetCallback( int nChannel, KSJ_CCCALLBACK fpCCCallback, void *lpContext );

enum KSJ_COLORCORRECT { KSJ_CC_NONE, KSJ_CC_SHIFTRGB, KSJ_CC_EQRGB, KSJ_CC_EQALL };
KSJ_API  int __stdcall KSJ_ColorCorrectSet( int nChannel, KSJ_COLORCORRECT ColorCorrect, int nRTarget, int nGTarget, int nBTarget );


KSJ_API  int __stdcall KSJ_ColorCorrectGet( int nChannel, KSJ_COLORCORRECT *pColorCorrect );

// 设置对比度，设置值范围（-128~128）
KSJ_API  int __stdcall KSJ_ProcessContrastSet( int nChannel, int nContrast );

KSJ_API  int __stdcall KSJ_ProcessContrastGet( int nChannel, int *pnContrast );

KSJ_API  int __stdcall KSJ_ProcessContrastGetRange( int nChannel, int *pnMinContrast, int *pnMaxContrast );

// 设置亮度，设置值范围（-128~128）
KSJ_API  int __stdcall KSJ_ProcessBrightnessSet( int nChannel, int nBrightness );

KSJ_API  int __stdcall KSJ_ProcessBrightnessGet( int nChannel, int *pnBrightness );

KSJ_API  int __stdcall KSJ_ProcessBrightnessGetRange( int nChannel, int *pnMinBrightness, int *pnMaxBrightness );

KSJ_API  int __stdcall KSJ_RecordStart( int nChannel, bool bStart, float fRecordRate, const char *pFileName );

KSJ_API  int __stdcall KSJ_RecordStatusGet( int nChannel, bool *bStart );


// 保存为Bmp文件
KSJ_API  int __stdcall KSJ_HelperSaveToBmp( unsigned char *pData, int nWidth, int nHeight, int nBitCount, const char *pszFileName );
// 保存为Jpg文件
KSJ_API  int __stdcall KSJ_HelperSaveToJpg( unsigned char *pData, int nWidth, int nHeight, int nBitCount, int nQulity, const char *pszFileName );

// Trigger Mode
enum KSJ_TRIGGERMODE
{
	KSJ_TRIGGER_INTERNAL,
	KSJ_TRIGGER_EXTERNAL,
	KSJ_TRIGGER_SOFTWARE,
	KSJ_TRIGGER_FIXFRAMERATE
};

// Set Trigger Mode
KSJ_API  int __stdcall KSJ_TriggerModeSet(int nChannel, KSJ_TRIGGERMODE TriggerMode);
KSJ_API  int __stdcall KSJ_TriggerModeGet(int nChannel, KSJ_TRIGGERMODE *pTriggerMode);

// Fixed Frame Rate when in KSJ_TRIGGER_FIXFRAMERATE mode. Maybe Return RET_NOTSUPPORT.
KSJ_API  int __stdcall KSJ_SetFixedFrameRateEx(int nChannel, float fFrameRate);
KSJ_API  int __stdcall KSJ_GetFixedFrameRateEx(int nChannel, float *pfFrameRate);

enum KSJ_TRIGGERMETHOD
{
	KSJ_TRIGGER_FALLINGEDGE,
	KSJ_TRIGGER_RISINGEDGE,
	KSJ_TRIGGER_HIGHLEVEL,
	KSJ_TRIGGER_LOWLEVEL
};
// Set Trigger Method when in KSJ_TRIGGER_EXTERNAL mode.
KSJ_API  int __stdcall KSJ_TriggerMethodSet(int nChannel, KSJ_TRIGGERMETHOD  TriggerMethod);
KSJ_API  int __stdcall KSJ_TriggerMethodGet(int nChannel, KSJ_TRIGGERMETHOD *pTriggerMethod);

// Set Trigger Delay when in KSJ_TRIGGER_EXTERNAL. May be Return RET_NOTSUPPORT.
KSJ_API  int __stdcall KSJ_TriggerDelayGetRange(int nChannel, unsigned short *wMin, unsigned short *wMax);
KSJ_API  int __stdcall KSJ_TriggerDelaySet(int nChannel, unsigned short wDelay);
KSJ_API  int __stdcall KSJ_TriggerDelayGet(int nChannel, unsigned short *pwDelay);

// Set Read action timeout (ms). Influence capture and preview.
KSJ_API  int __stdcall KSJ_CaptureSetTimeOut(int nChannel, unsigned long dwTimeOut);
// Get Read action image timeout (ms).
KSJ_API  int __stdcall KSJ_CaptureGetTimeOut(int nChannel, unsigned long *pdwTimeOut);

// Set If recover device when Read Fail. It will Influence capture and preview.
KSJ_API  int __stdcall KSJ_CaptureSetRecover(int nChannel, bool bRecover);
// Get If recover device when Read Fail.
KSJ_API  int __stdcall KSJ_CaptureGetRecover(int nChannel, bool *pbRecover);


#ifdef __cplusplus
}
#endif

#endif


