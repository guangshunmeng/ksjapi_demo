#pragma once
#include "stdafx.h"

#include "..\KSJApi.Inc\KSJApi.h"
#include "..\Common\KSJ_GS.H"
#ifdef _WIN64
#ifdef _DEBUG
#pragma comment( lib, "..\\KSJApi.Lib\\KSJApi64d.lib" )
#else
#pragma comment( lib, "..\\KSJApi.Lib\\KSJApi64.lib" )
#endif
#else
#ifdef _DEBUG
#pragma comment( lib, "..\\KSJApi.Lib\\KSJApi.lib" )
#else
#pragma comment( lib, "..\\KSJApi.Lib\\KSJApi.lib" )
#endif
#endif
class CKSJCamClass
{
public:
	CKSJCamClass(void);
	virtual ~CKSJCamClass(void);
	void Initial(int nIndex);
	void SetWnd(CWnd* pPreviewWnd);
private:
	void ReadIni();
	void WriteIni();
	CWnd* m_pPreviewWnd;
	
public:
	// 是否已打开
	virtual bool IsOpen() const;

private:
	int    m_nIndex;
public:
	// 开始采集
	//virtual bool Capture( CPrImage* pImage, DWORD nDelay );


	void UpdatePreview();

	int GetDeviceIndex();
	void ConvertCKdataToKSJdata(unsigned char *pImageKSJData, unsigned char *pImageCKData, int nWidth, int nHeight, int nBitCount);
	//Normal
	int PreviewSetFieldOfView(int nColStart, int nRowStart, int nColSize, int nRowSize, KSJ_ADDRESSMODE ColAddressMode, KSJ_ADDRESSMODE RowAddressMode);
	int PreviewGetDefaultFieldOfView(int *pnColStart, int *pnRowStart, int *pnColSize, int *pnRowSize, KSJ_ADDRESSMODE *pColAddressMode, KSJ_ADDRESSMODE *pRowAddressMode);
	int PreviewGetFieldOfView(int *pnColStart, int *pnRowStart, int *pnColSize, int *pnRowSize, KSJ_ADDRESSMODE *pColAddressMode, KSJ_ADDRESSMODE *pRowAddressMode);
	int CaptureSetFieldOfView(int nColStart, int nRowStart, int nColSize, int nRowSize, KSJ_ADDRESSMODE ColAddressMode, KSJ_ADDRESSMODE RowAddressMode);
	int PreviewSetFieldOfViewEx(int nColStart, int nRowStart, int nColSize, int nRowSize, KSJ_ADDRESSMODE ColAddressMode, KSJ_ADDRESSMODE RowAddressMode, unsigned short wMultiFrameNum);
	int PreviewGetFieldOfViewEx(int *pnColStart, int *pnRowStart, int *pnColSize, int *pnRowSize, KSJ_ADDRESSMODE *pColAddressMode, KSJ_ADDRESSMODE *pRowAddressMode, unsigned short *pwMultiFrameNum);
	int CaptureSetFieldOfViewEx(int nColStart, int nRowStart, int nColSize, int nRowSize, KSJ_ADDRESSMODE ColAddressMode, KSJ_ADDRESSMODE RowAddressMode, unsigned short wMultiFrameNum);
	int CaptureGetDefaultFieldOfView(int *pnColStart, int *pnRowStart, int *pnColSize, int *pnRowSize, KSJ_ADDRESSMODE *pColAddressMode, KSJ_ADDRESSMODE *pRowAddressMode);
	int GetParamRange(KSJ_PARAM Param, int *pnMinValue, int *pnMaxValue);
	int SetParam(KSJ_PARAM Param, int nValue);
	int GetParam(KSJ_PARAM Param, int *pnValue);
	int QueryFunction(KSJ_FUNCTION Function, int *pInfo);
	int AWAIBA_IsUsed(bool *bUsed);
	int AWAIBA_GetSegmentNum(int *pnSegNum);
	int AWAIBA_GetGainRange(int nSegIndex, int *pnMin, int *pnMax);
	int AWAIBA_SetGain(int nSegIndex, int nGain);
	int AWAIBA_GetGain(int nSegIndex, int *pnGain);
	int PreviewStart(bool bStart);

private:
	int				m_nColStart;
	int				m_nRowStart;
	int				m_nColSize;
	int				m_nRowSize;
	int				m_nGainRed;
	int				m_nGainGreen;
	int				m_nGainBlue;
	int				m_nExposureTimeMs;
	int				m_nExposureLines;
	unsigned short  m_wMultiFrameNum;

	//Trigger
public:
	int CaptureSetTimeOut(unsigned long dwTimeOut);
	int CaptureGetTimeOut(unsigned long *pdwTimeOut);
	int CaptureSetRecover( bool bRecover );
	int CaptureGetRecover( bool *pbRecover );
	int TriggerModeSet(KSJ_TRIGGERMODE TriggerMode);
	int TriggerModeGet(KSJ_TRIGGERMODE *pTriggerMode);
	int TriggerMethodSet(KSJ_TRIGGERMETHOD  TriggerMethod);
	int TriggerMethodGet(KSJ_TRIGGERMETHOD *pTriggerMethod);
	int TriggerDelayGetRange(unsigned short *wMin, unsigned short *wMax);
	int TriggerDelaySet(unsigned short wDelay);
	int TriggerDelayGet(unsigned short *pwDelay);
	int CaptureSetTimeOutEx(unsigned long dwTimeOut, bool bRecover);
	int CaptureGetTimeOutEx(unsigned long *pdwTimeOut, bool *pbRecover);
	int SetFixedFrameRateEx(float fFrameRate);
	int GetFixedFrameRateEx(float *pfFrameRate);
	int EmptyFrameBuffer();
	int FlashControlGet(bool *pbEnable, bool *pbInvert, int *pnMode);
	int FlashControlSet(bool bEnable, bool bInvert, int nMode);
private:
	unsigned long     m_dwTimeOut;
	bool		      m_bRecover;
	KSJ_TRIGGERMODE   m_TriggerMode;
	KSJ_TRIGGERMETHOD m_TriggerMethod;
	unsigned short	  m_wDelay;
	float			  m_fFrameRate;
	bool			  m_bEnable;
	bool			  m_bInvert;

	//Image
public:
	int ProcessContrastGetRange(int *pnMinContrast, int *pnMaxContrast);
	int ProcessContrastSet(int nContrast);
	int ProcessContrastGet(int *pnContrast);
	int ProcessBrightnessGetRange(int *pnMinBrightness, int *pnMaxBrightness);
	int ProcessBrightnessSet(int nBrightness);
	int ProcessBrightnessGet(int *pnBrightness);
	int ProcessSaturationGetRange(int *pnMinSaturation, int *pnMaxSaturation);
	int ProcessSaturationSet(int nSaturation);
	int ProcessSaturationGet(int *pnStaturation);
	int GammaGetRange(int *pnMinGamma, int *pnMaxGamm);
	int GammaGetValue(int *pnValue);
	int GammaSetValue(int nValue);
	int HueSaturationSet(KSJHueRange HueRange, int nHue, int nSaturation, int nLightness);
	int HueSaturationGet(KSJHueRange HueRange, int *pnHue, int *pnSaturation, int *pnLightness);
	int HueSaturationSetEnable(bool bEnable);
private:
	struct HUE
	{
		int nHue;
		int nSaturation;
		int nLightness;
	};

	bool m_bFlip;
	bool m_bMirror;
	int  m_nContrast;
	int  m_nBrightness;
	int  m_nSaturation;
	int  m_nGamma;
	bool m_HueEnable;
	HUE  m_Hue[7];

	//Matrix
public:
	int WhiteBalanceSet(KSJ_WB_MODE WbMode);
	int WhiteBalanceGet(KSJ_WB_MODE *pWbMode);
	int WhiteBalancePresettingSet(KSJ_COLOR_TEMPRATURE WbPresetting);
	int WhiteBalancePresettingGet(KSJ_COLOR_TEMPRATURE *pWbPresetting);
	int WhiteBalanceAutoSetCallBack(KSJ_WB_CALLBACK pfCallBack, void *lpContext);
	int WhiteBalanceAutoSet(int nPhi);
	int WhiteBalanceAutoGet(int *pnPhi);
	int WhiteBalanceMatrixSet(float fMatrix[3]);
	int WhiteBalanceMatrixGet(float fMatrix[3]);
	int ColorCorrectionSet(KSJ_CCM_MODE CcmMode);
	int ColorCorrectionGet(KSJ_CCM_MODE *pCcmMode);
	int ColorCorrectionPresettingSet(KSJ_COLOR_TEMPRATURE CcmPresetting);
	int ColorCorrectionPresettingGet(KSJ_COLOR_TEMPRATURE *pCcmPresetting);
	int ColorCorrectionMatrixSet(float fMatrix[3][3]);
	int ColorCorrectionMatrixGet(float fMatrix[3][3]);

	int SensitivitySetMode(KSJ_SENSITIVITYMODE SensitivityMode);
	int SensitivityGetMode(KSJ_SENSITIVITYMODE *pSensitivityMode);
private:
	KSJ_WB_MODE			 m_WbMode;
	KSJ_COLOR_TEMPRATURE m_WbPresetting;
	int					 m_nPhi;
	float				 m_fWhiteMatrix[3];
	KSJ_CCM_MODE		 m_CcmMode;
	KSJ_COLOR_TEMPRATURE m_CcmPresetting;
	float				 m_fColorMatrix[3][3];
	KSJ_SENSITIVITYMODE m_Mode;

};
