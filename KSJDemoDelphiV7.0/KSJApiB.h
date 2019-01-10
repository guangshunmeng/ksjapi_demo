/*=================================================================
	���Ӽѹ�ҵ���ʸ��幤ҵ���API���������ļ�
	��ַ��    www.catchbest.com
	����֧�֣�catchbest.support@hotmail.com
  -----------------------------------------------------------------*/

#ifndef __KSJ_API_B_H__
#define __KSJ_API_B_H__


#ifdef KSJAPI_EXPORTS
    #define KSJ_API __declspec(dllexport)
#else
    #define KSJ_API __declspec(dllimport)
#endif

/*=================================================================
	���º���ΪKSJApi.dll����������
	�����Ӧ�ó����У���Ӧ�ð���KSJAPI.H������KSJApi.LIB��
	Ȼ����Ϳ��Ե�������ĵ���������
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

// ��ô������ϸ��Ϣ���������κ�ʱ�����
KSJ_API  int __stdcall KSJ_GetErrorInfo( int nErrorNo, char pszErrorInfo[256] );
// ��ʼ��KSJApi��̬��
KSJ_API  int __stdcall KSJ_Init( void );
// ����ʼ��KSJApi��̬��
KSJ_API  int __stdcall KSJ_UnInit( void );
// �õ��豸��Ŀ
KSJ_API  int __stdcall KSJ_DeviceGetCount( void );

// ���Ӽѹ�ҵ����豸���Ͷ��壺M-Mircon Sensor, R-Rolling Shutter, N-No External Trigger, N-No Frame Buffer
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
// �õ��豸��Ϣ���ͺţ���ţ��̼��汾�ţ�
KSJ_API  int __stdcall KSJ_DeviceGetInformation( IN int nChannel, OUT KSJ_DEVICETYPE *pDeviceType, OUT int *pnIndex, OUT unsigned short *pwFirmwareVersion );
// ���ģʽ���壨��Ϊ�г����г�㣩��
enum KSJ_ADDRESSMODE { KSJ_SKIPNONE = 0, KSJ_SKIP2, KSJ_SKIP3, KSJ_SKIP4, KSJ_SKIP8 };
// ���òɼ��ӳ���С
KSJ_API  int __stdcall KSJ_CaptureSetFieldOfView( int nChannel, int nColumnStart, int nRowStart, int nColumnSize, int nRowSize, KSJ_ADDRESSMODE ColumnAddressMode, KSJ_ADDRESSMODE RowAddressMode );
// ��ȡ�ɼ��ӳ���ʵ�ʴ�С
KSJ_API  int __stdcall KSJ_CaptureGetFieldOfView( int nChannel, int *pnColumnStart, int *pnRowStart, int *pnColumnSize, int *pnRowSize, KSJ_ADDRESSMODE *pColumnAddressMode, KSJ_ADDRESSMODE *pRowAddressMode );
// �õ��ɼ�ͼ��Ŀ�Ⱥ͸߶ȣ���λ�����أ�
KSJ_API  int __stdcall KSJ_CaptureGetSize( int nChannel, int *pnWidth, int *pnHeight );

KSJ_API  int __stdcall KSJ_CaptureGetSizeEx( int nChannel, int *pnWidth, int *pnHeight, int *pnBitCount );

// �ɼ�һ֡ԭʼ����ͼ������
KSJ_API  int __stdcall KSJ_CaptureRawData     ( int nChannel, unsigned char *pRawData );
// �ɼ�һ֡8�Ҷ�ͼ���24��32λ��ɫͼ�����ݣ���KSJ_BayerSetMode��KSJ_PreviewSetMode��أ�
KSJ_API  int __stdcall KSJ_CaptureRgbData     ( int nChannel, unsigned char *pRgbData );

KSJ_API  int __stdcall KSJ_CaptureRgbDataEx   ( int nChannel, unsigned char *pRgbData, int *pnWidth, int *pnHeight, int *pnBitCount );

// �������
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
// ��ò��������÷�Χ
KSJ_API  int __stdcall KSJ_GetParamRange( IN int nChannel, IN KSJ_PARAM Param, OUT int *pnMinValue, OUT int *pnMaxValue );
// ���ò���
KSJ_API  int __stdcall KSJ_SetParam     ( IN int nChannel, IN KSJ_PARAM Param, IN  int nValue );
// ��ȡ������ǰֵ
KSJ_API  int __stdcall KSJ_GetParam     ( IN int nChannel, IN KSJ_PARAM Param, OUT int *pnValue );

// ����Gammaֵ����Χ -9 - +9
KSJ_API  int __stdcall KSJ_GammaSetValue( int nChannel, int nValue );
// �򿪻�ر�GammaУ������Ӱ��Ԥ����Ӱ��ɼ�
KSJ_API  int __stdcall KSJ_GammaOn( int nChannel, bool bOn );

// ö�����ͱ�Ү��ģʽ
enum KSJ_BAYERMODE { KSJ_BGGR_BGR24 = 0, KSJ_GRBG_BGR24, KSJ_RGGB_BGR24, KSJ_GBRG_BGR24, KSJ_BGGR_BGR24_FLIP, KSJ_GRBG_BGR24_FLIP,  KSJ_RGGB_BGR24_FLIP, KSJ_GBRG_BGR24_FLIP, 
                     KSJ_BGGR_BGR32,     KSJ_GRBG_BGR32, KSJ_RGGB_BGR32, KSJ_GBRG_BGR32, KSJ_BGGR_BGR32_FLIP, KSJ_GRBG_BGR32_FLIP,  KSJ_RGGB_BGR32_FLIP, KSJ_GBRG_BGR32_FLIP,
                     KSJ_BGGR_GRAY8,     KSJ_GRBG_GRAY8, KSJ_RGGB_GRAY8, KSJ_GBRG_GRAY8, KSJ_BGGR_GRAY8_FLIP, KSJ_GRBG_GRAY8_FLIP,  KSJ_RGGB_GRAY8_FLIP, KSJ_GBRG_GRAY8_FLIP };
// ����Bayerģʽ��ͬʱӰ��ɼ���Ԥ�������������������Ҫ���ã������û�������ô˹��ܡ�
KSJ_API   int __stdcall KSJ_BayerSetMode( int nChannel, KSJ_BAYERMODE BayerMode );
// ��õ�ǰBayerģʽ
KSJ_API   int __stdcall KSJ_BayerGetMode( int nChannel, KSJ_BAYERMODE *pBayerMode );

// �����Զ��ع������������������Ԥ��ͼ������Ͻ�����λ��
KSJ_API  int __stdcall KSJ_AESetRegion( int nChannel, int nX, int nY,  int nW, int nH );

// �Զ��ع�ص�����
typedef void (__stdcall *KSJ_AECALLBACK )( bool bSuccess, int nResult,  void *lpContext );
// �����Զ��ع����������Ļص����������Զ��ع����ʱ��KSJ���������Զ�����AECallback�û�ָ���Ļص�����
KSJ_API  int __stdcall KSJ_AESetCallback( int nChannel, KSJ_AECALLBACK pfAECallback, void *lpContext );
// ��ʼ����ֹ�Զ��ع����
KSJ_API  int __stdcall KSJ_AEStart( int nChannel, bool bStart, int nMaxCount, int nTarget );


// �����Զ���ƽ������
KSJ_API  int __stdcall KSJ_AWBSetRegion( int nChannel, int nX, int nY,  int nW, int nH );
// �Զ���ƽ��ص�����
typedef void (__stdcall *KSJ_AWBCALLBACK )( bool bSuccess, int nRValue, int nGValue, int nBValue,  void *lpContext );
// �����Զ���ƽ�⣨����Ӳ��������������Ļص����������Զ��ع����ʱ��KSJ���������Զ�����AECallback�û�ָ���Ļص�����
KSJ_API  int __stdcall KSJ_AWBSetCallback( int nChannel, KSJ_AWBCALLBACK fpAWBCallback, void *lpContext );
// ��ʼ����ֹ�Զ���ƽ�����
KSJ_API  int __stdcall KSJ_AWBStart( int nChannel, bool bStart, int nMaxCount, int nRTarget, int nGTarget, int nBTarget );

typedef void (__stdcall *KSJ_CCCALLBACK )( bool bSuccess, int nRShift, int nGShift, int nBShift,  void *lpContext );

// ���º���Ϊ�����ɫУ��
KSJ_API  int __stdcall KSJ_ColorCorrectSetCallback( int nChannel, KSJ_CCCALLBACK fpCCCallback, void *lpContext );

enum KSJ_COLORCORRECT { KSJ_CC_NONE, KSJ_CC_SHIFTRGB, KSJ_CC_EQRGB, KSJ_CC_EQALL };
KSJ_API  int __stdcall KSJ_ColorCorrectSet( int nChannel, KSJ_COLORCORRECT ColorCorrect, int nRTarget, int nGTarget, int nBTarget );


KSJ_API  int __stdcall KSJ_ColorCorrectGet( int nChannel, KSJ_COLORCORRECT *pColorCorrect );

// ���öԱȶȣ�����ֵ��Χ��-128~128��
KSJ_API  int __stdcall KSJ_ProcessContrastSet( int nChannel, int nContrast );

KSJ_API  int __stdcall KSJ_ProcessContrastGet( int nChannel, int *pnContrast );

KSJ_API  int __stdcall KSJ_ProcessContrastGetRange( int nChannel, int *pnMinContrast, int *pnMaxContrast );

// �������ȣ�����ֵ��Χ��-128~128��
KSJ_API  int __stdcall KSJ_ProcessBrightnessSet( int nChannel, int nBrightness );

KSJ_API  int __stdcall KSJ_ProcessBrightnessGet( int nChannel, int *pnBrightness );

KSJ_API  int __stdcall KSJ_ProcessBrightnessGetRange( int nChannel, int *pnMinBrightness, int *pnMaxBrightness );

KSJ_API  int __stdcall KSJ_RecordStart( int nChannel, bool bStart, float fRecordRate, const char *pFileName );

KSJ_API  int __stdcall KSJ_RecordStatusGet( int nChannel, bool *bStart );


// ����ΪBmp�ļ�
KSJ_API  int __stdcall KSJ_HelperSaveToBmp( unsigned char *pData, int nWidth, int nHeight, int nBitCount, const char *pszFileName );
// ����ΪJpg�ļ�
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


