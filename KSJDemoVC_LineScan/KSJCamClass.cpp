#include "StdAfx.h"
#include "KSJCamClass.h"
#include "KSJDemoVC_LineScanDlg.h"

void CKSJCamClass::ReadIni()
{
	if (m_nIndex == -1)    return;

	DEVICEINFO    DeviceInfo;
	KSJ_DeviceGetInformation(m_nIndex, &(DeviceInfo.DeviceType), &(DeviceInfo.nIndex), &(DeviceInfo.wFirmwareVersion));
	TCHAR szSection[16] = { 0 };
	_stprintf_s(szSection, _T("%d_%d"), DeviceInfo.DeviceType, DeviceInfo.nIndex);
	
	int nSupport = 0;
	QueryFunction(KSJ_SUPPORT_MULTI_FRAMES, &nSupport);
	int nColStart = 0;//Normal
	int nRowStart = 0;
	int nColSize = 0;
	int nRowSize = 0;
	KSJ_ADDRESSMODE ColAddressMode;
	KSJ_ADDRESSMODE RowAddressMode;
	unsigned short wMultiFrameNum = 0;
	if (nSupport == 1)
	{
		PreviewGetFieldOfViewEx(&nColStart, &nRowStart, &nColSize, &nRowSize, &ColAddressMode, &RowAddressMode, &wMultiFrameNum);
	}
	else
	{
		PreviewGetFieldOfView(&nColStart, &nRowStart, &nColSize, &nRowSize, &ColAddressMode, &RowAddressMode);
	}
	
	KSJINI_GetDWORD(g_hIni, szSection, _T("ColStart"), nColStart, (DWORD*)&m_nColStart);
	KSJINI_GetDWORD(g_hIni, szSection, _T("RowStart"), nRowStart, (DWORD*)&m_nRowStart);
	KSJINI_GetDWORD(g_hIni, szSection, _T("ColSize"), nColSize, (DWORD*)&m_nColSize);
	KSJINI_GetDWORD(g_hIni, szSection, _T("RowSize"), nRowSize, (DWORD*)&m_nRowSize);
	KSJINI_GetDWORD(g_hIni, szSection, _T("MultiFrameNum"), wMultiFrameNum, (DWORD*)&m_wMultiFrameNum);

	bool bUsed = false;
	AWAIBA_IsUsed(&bUsed);
	int nDefault;
	if (bUsed)
	{
		TCHAR szGain[32] = { 0 };
		int nCount = 0;
		int nGain = 0;
		AWAIBA_GetSegmentNum(&nCount);
		for (int i = 0; i < nCount; i++)
		{
			AWAIBA_GetGain(i, &nDefault);
			_stprintf_s(szGain, _T("Gain%d"), i);
			KSJINI_GetDWORD(g_hIni, szSection, szGain, nDefault, (DWORD*)&nGain);
			AWAIBA_SetGain(i, nGain);
		}
	}
	else
	{
		GetParam(KSJ_RED, &nDefault);
		KSJINI_GetDWORD(g_hIni, szSection, _T("GainRed"), nDefault, (DWORD*)&m_nGainRed);
		GetParam(KSJ_GREEN, &nDefault);
		KSJINI_GetDWORD(g_hIni, szSection, _T("GainGreen"), nDefault, (DWORD*)&m_nGainGreen);
		GetParam(KSJ_BLUE, &nDefault);
		KSJINI_GetDWORD(g_hIni, szSection, _T("GainBlue"), nDefault, (DWORD*)&m_nGainBlue);
		SetParam(KSJ_RED, m_nGainRed);
		SetParam(KSJ_GREEN, m_nGainGreen);
		SetParam(KSJ_BLUE, m_nGainBlue);
	}

	GetParam(KSJ_EXPOSURE, &nDefault);
	KSJINI_GetDWORD(g_hIni, szSection, _T("ExposureTimeMs"), nDefault, (DWORD*)&m_nExposureTimeMs);
	GetParam(KSJ_EXPOSURE_LINES, &nDefault);
	KSJINI_GetDWORD(g_hIni, szSection, _T("ExposureLines"), nDefault, (DWORD*)&m_nExposureLines);
	if (nSupport == 1)
	{
		PreviewSetFieldOfViewEx(m_nColStart, m_nRowStart, m_nColSize, m_nRowSize, ColAddressMode, RowAddressMode, m_wMultiFrameNum);
		CaptureSetFieldOfViewEx(m_nColStart, m_nRowStart, m_nColSize, m_nRowSize, ColAddressMode, RowAddressMode, m_wMultiFrameNum);
	}
	else
	{
		PreviewSetFieldOfView(m_nColStart, m_nRowStart, m_nColSize, m_nRowSize, ColAddressMode, RowAddressMode);
		CaptureSetFieldOfView(m_nColStart, m_nRowStart, m_nColSize, m_nRowSize, ColAddressMode, RowAddressMode);
	}


	SetParam(KSJ_EXPOSURE, m_nExposureTimeMs);
	SetParam(KSJ_EXPOSURE_LINES, m_nExposureLines);

	unsigned long nTimeOut = 0;//Trigger
	TriggerModeSet(KSJ_TRIGGER_INTERNAL);
	CaptureGetTimeOut(&nTimeOut);
	KSJINI_GetDWORD(g_hIni, szSection, _T("TimeOut"), nTimeOut, (DWORD*)&m_dwTimeOut);
	bool bRecover = false;
	CaptureGetRecover(&bRecover);
	KSJINI_GetBOOL(g_hIni, szSection, _T("Recover"), false, (BOOL*)&m_bRecover);
	KSJ_TRIGGERMODE    TriggerMode;
	TriggerModeGet(&TriggerMode);
	KSJINI_GetDWORD(g_hIni, szSection, _T("TriggerMode"), TriggerMode, (DWORD*)&m_TriggerMode);
	KSJ_TRIGGERMETHOD    TriggerMethod;
	TriggerMethodGet(&TriggerMethod);
	KSJINI_GetDWORD(g_hIni, szSection, _T("TriggerMethod"), TriggerMethod, (DWORD*)&m_TriggerMethod);
	TriggerDelayGet((WORD*)&nDefault);
	KSJINI_GetDWORD(g_hIni, szSection, _T("Delay"), nDefault, (DWORD*)&m_wDelay);
	float fFixedFrameRate = 0.0f;
	GetFixedFrameRateEx(&fFixedFrameRate);
	TCHAR szfFrameRate[16] = { 0 };
	TCHAR szDefault[16] = { 0 };
	_stprintf_s(szDefault, _T("%f"), fFixedFrameRate);
	KSJINI_GetString(g_hIni, szSection, _T("FrameRate"), szDefault, szfFrameRate);
	m_fFrameRate = _tstof(szfFrameRate);
	int nMode;
	bool bEnable = false;
	bool bInvert = false;
	FlashControlGet(&bEnable, &bInvert, &nMode);
	KSJINI_GetBOOL(g_hIni, szSection, _T("FlashEnable"), bEnable, (BOOL*)&m_bEnable);
	KSJINI_GetBOOL(g_hIni, szSection, _T("FlashInvert"), bInvert, (BOOL*)&m_bInvert);

	CaptureSetTimeOut(m_dwTimeOut);
	CaptureSetRecover(m_bRecover);
	TriggerModeSet(m_TriggerMode);
	TriggerMethodSet(m_TriggerMethod);
	TriggerDelaySet(m_wDelay);
	SetFixedFrameRateEx(m_fFrameRate);
	int nRet = FlashControlSet(m_bEnable, m_bInvert, 0);
	BOOL bCheck;//Image
	GetParam(KSJ_FLIP, &bCheck);
	KSJINI_GetBOOL(g_hIni, szSection, _T("Flip"), bCheck, (BOOL*)&m_bFlip);
	GetParam(KSJ_MIRROR, &bCheck);
	KSJINI_GetBOOL(g_hIni, szSection, _T("Mirror"), bCheck, (BOOL*)&m_bMirror);
	ProcessContrastGet(&nDefault);
	KSJINI_GetDWORD(g_hIni, szSection, _T("Process_Contrast"), nDefault, (DWORD*)&m_nContrast);
	ProcessSaturationGet(&nDefault);
	KSJINI_GetDWORD(g_hIni, szSection, _T("Process_Saturation"), nDefault, (DWORD*)&m_nSaturation);
	ProcessBrightnessGet(&nDefault);
	KSJINI_GetDWORD(g_hIni, szSection, _T("Process_Brghtness"), nDefault, (DWORD*)&m_nBrightness);
	GammaGetValue(&nDefault);
	KSJINI_GetDWORD(g_hIni, szSection, _T("Process_Gamma"), nDefault, (DWORD*)&m_nGamma);
	KSJINI_GetBOOL(g_hIni, szSection, _T("HueEable"), false, (BOOL*)&m_HueEnable);
	TCHAR szKey[32] = { 0 };
	int i = 0;
	for (i = 0; i < g_nHueRange; i++)
	{
		_stprintf_s(szKey, _T("%s_Hue"), g_szHueRange[i]);
		KSJINI_GetDWORD(g_hIni, szSection, szKey, 0, (DWORD*)&m_Hue[i].nHue);
		_stprintf_s(szKey, _T("%s_Saturation"), g_szHueRange[i]);
		KSJINI_GetDWORD(g_hIni, szSection, szKey, 0, (DWORD*)&m_Hue[i].nSaturation);
		_stprintf_s(szKey, _T("%s_Lightness"), g_szHueRange[i]);
		KSJINI_GetDWORD(g_hIni, szSection, szKey, 0, (DWORD*)&m_Hue[i].nLightness);
		HueSaturationSet((KSJHueRange)i, m_Hue[i].nHue, m_Hue[i].nSaturation, m_Hue[i].nLightness);
	}

	SetParam(KSJ_FLIP, m_bFlip);
	SetParam(KSJ_MIRROR, m_bMirror);
	ProcessContrastSet(m_nContrast);
	ProcessSaturationSet(m_nSaturation);
	ProcessBrightnessSet(m_nBrightness);
	GammaSetValue(m_nGamma);
	HueSaturationSetEnable(m_HueEnable);

	KSJ_WB_MODE WbMode;//Matrix
	WhiteBalanceGet(&WbMode);
	KSJINI_GetDWORD(g_hIni, szSection, _T("WbMode"), WbMode, (DWORD*)&m_WbMode);
	KSJ_COLOR_TEMPRATURE ColorTemprature;
	ColorCorrectionPresettingGet(&ColorTemprature);
	KSJINI_GetDWORD(g_hIni, szSection, _T("WbPresetting"), ColorTemprature, (DWORD*)&m_WbPresetting);
	int nPhi = 0;
	WhiteBalanceAutoGet(&nPhi);
	KSJINI_GetDWORD(g_hIni, szSection, _T("Phi"), nPhi, (DWORD*)&m_nPhi);
	float fMatrix[3];
	WhiteBalanceMatrixGet(fMatrix);
	for (i = 0; i < 3; i++)
	{
		_stprintf_s(szKey, _T("WhiteMatrix_%d"), i);
		_stprintf_s(szDefault, _T("%f"), fMatrix[i]);
		KSJINI_GetString(g_hIni, szSection, szKey, szDefault, szfFrameRate);
		m_fWhiteMatrix[i] = _tstof(szfFrameRate);
	}

	KSJ_CCM_MODE CcmMode;
	ColorCorrectionGet(&CcmMode);
	KSJINI_GetDWORD(g_hIni, szSection, _T("CcmMode"), CcmMode, (DWORD*)&m_CcmMode);
	ColorCorrectionPresettingGet(&ColorTemprature);
	KSJINI_GetDWORD(g_hIni, szSection, _T("CcmPresetting"), ColorTemprature, (DWORD*)&m_CcmPresetting);
	float fCcmMatrix[3][3];
	ColorCorrectionMatrixGet(fCcmMatrix);
	int j = 0;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			_stprintf_s(szKey, _T("ColorMatrix_%d%d"), i, j);
			_stprintf_s(szDefault, _T("%f"), fCcmMatrix[i][j]);
			KSJINI_GetString(g_hIni, szSection, szKey, szDefault, szfFrameRate);
			m_fColorMatrix[i][j] = _tstof(szfFrameRate);
		}
	}

	WhiteBalanceSet(m_WbMode);
	WhiteBalancePresettingSet(m_WbPresetting);
	WhiteBalanceAutoSet(m_nPhi);
	WhiteBalanceMatrixSet(m_fWhiteMatrix);
	ColorCorrectionSet(m_CcmMode);
	ColorCorrectionPresettingSet(m_CcmPresetting);
	ColorCorrectionMatrixSet(m_fColorMatrix);
}


void CKSJCamClass::WriteIni()
{
	if (m_nIndex == -1)    return;

	DEVICEINFO    DeviceInfo;
	KSJ_DeviceGetInformation(m_nIndex, &(DeviceInfo.DeviceType), &(DeviceInfo.nIndex), &(DeviceInfo.wFirmwareVersion));
	TCHAR szSection[16] = { 0 };
	_stprintf_s(szSection, _T("%d_%d"), DeviceInfo.DeviceType, DeviceInfo.nIndex);

	KSJINI_SetInt(g_hIni, szSection, _T("ColStart"), m_nColStart);//Normal
	KSJINI_SetInt(g_hIni, szSection, _T("RowStart"), m_nRowStart);
	KSJINI_SetInt(g_hIni, szSection, _T("ColSize"), m_nColSize);
	KSJINI_SetInt(g_hIni, szSection, _T("RowSize"), m_nRowSize);
	KSJINI_SetInt(g_hIni, szSection, _T("MultiFrameNum"), m_wMultiFrameNum);
	bool bUsed = false;
	AWAIBA_IsUsed(&bUsed);
	if (bUsed)
	{
		TCHAR szGain[32] = { 0 };
		int nCount = 0;
		int nGain = 0;
		AWAIBA_GetSegmentNum(&nCount);
		for (int i = 0; i < nCount;i++)
		{
			AWAIBA_GetGain(i, &nGain);
			_stprintf_s(szGain, _T("Gain%d"), i);
			KSJINI_SetInt(g_hIni, szSection, szGain, nGain);
		}
	}
	else
	{
		KSJINI_SetInt(g_hIni, szSection, _T("GainRed"), m_nGainRed);
		KSJINI_SetInt(g_hIni, szSection, _T("GainGreen"), m_nGainGreen);
		KSJINI_SetInt(g_hIni, szSection, _T("GainBlue"), m_nGainBlue);
	}

	KSJINI_SetInt(g_hIni, szSection, _T("ExposureTimeMs"), m_nExposureTimeMs);
	KSJINI_SetInt(g_hIni, szSection, _T("ExposureLines"), m_nExposureLines);

	KSJINI_SetInt(g_hIni, szSection,  _T("TimeOut"),	   m_dwTimeOut);//Trigger
	KSJINI_SetBOOL(g_hIni, szSection, _T("Recover"),	   m_bRecover);
	KSJINI_SetInt(g_hIni, szSection,  _T("TriggerMode"),   m_TriggerMode);
	KSJINI_SetInt(g_hIni, szSection,  _T("TriggerMethod"), m_TriggerMethod);
	KSJINI_SetInt(g_hIni, szSection,  _T("Delay"),		   m_wDelay);
	TCHAR szfFrameRate[16] = { 0 };
	_stprintf_s(szfFrameRate, _T("%f"), m_fFrameRate);
	KSJINI_SetString(g_hIni, szSection, _T("FrameRate"), szfFrameRate);
	KSJINI_SetBOOL(g_hIni, szSection, _T("FlashEnable"), m_bEnable);
	KSJINI_SetBOOL(g_hIni, szSection, _T("FlashInvert"), m_bInvert);

	KSJINI_SetBOOL(g_hIni, szSection, _T("Flip"), m_bFlip);//Image
	KSJINI_SetBOOL(g_hIni, szSection, _T("Mirror"), m_bMirror);
	KSJINI_SetInt(g_hIni, szSection,  _T("Process_Contrast"), m_nContrast);
	KSJINI_SetInt(g_hIni, szSection,  _T("Process_Brghtness"), m_nBrightness);
	KSJINI_SetInt(g_hIni, szSection,  _T("Process_Saturation"), m_nSaturation);
	KSJINI_SetInt(g_hIni, szSection,  _T("Process_Gamma"), m_nGamma);
	KSJINI_SetBOOL(g_hIni, szSection, _T("HueEable"), m_HueEnable);

	TCHAR szKey[32] = { 0 };
	int i = 0;
	for (i = 0; i < g_nHueRange;i++)
	{
		_stprintf_s(szKey, _T("%s_Hue"), g_szHueRange[i]);
		KSJINI_SetInt(g_hIni, szSection, szKey, m_Hue[i].nHue);
		_stprintf_s(szKey, _T("%s_Saturation"), g_szHueRange[i]);
		KSJINI_SetInt(g_hIni, szSection, szKey, m_Hue[i].nSaturation);
		_stprintf_s(szKey, _T("%s_Lightness"), g_szHueRange[i]);
		KSJINI_SetInt(g_hIni, szSection, szKey, m_Hue[i].nLightness);
	}

	KSJINI_SetInt(g_hIni, szSection, _T("WbMode"), m_WbMode);//Matrix
	KSJINI_SetInt(g_hIni, szSection, _T("WbPresetting"), m_WbPresetting);
	KSJINI_SetInt(g_hIni, szSection, _T("Phi"), m_nPhi);
	for (i = 0; i < 3;i++)
	{
		_stprintf_s(szKey, _T("WhiteMatrix_%d"), i);
		_stprintf_s(szfFrameRate, _T("%f"), m_fWhiteMatrix[i]);
		KSJINI_SetString(g_hIni, szSection, szKey, szfFrameRate);
	}

	KSJINI_SetInt(g_hIni, szSection, _T("CcmMode"), m_CcmMode);
	KSJINI_SetInt(g_hIni, szSection, _T("CcmPresetting"), m_CcmPresetting);
	int j = 0;
	for (i = 0; i < 3;i++)
	{
		for (j = 0; j < 3;j++)
		{
			_stprintf_s(szKey, _T("ColorMatrix_%d%d"), i,j);
			_stprintf_s(szfFrameRate, _T("%f"), m_fColorMatrix[i][j]);
			KSJINI_SetString(g_hIni, szSection, szKey, szfFrameRate);
		}
	}
}

CKSJCamClass::CKSJCamClass(void)
{
	m_nIndex = -1;
	//Normal
	m_nColStart = 0;
	m_nRowStart = 0;
	m_nColSize = 400;
	m_nRowSize = 300;
	m_nGainRed = 0;
	m_nGainGreen = 0;
	m_nGainBlue = 0;
	m_nExposureTimeMs = 0;
	m_nExposureLines = 0;
	m_wMultiFrameNum = 0;

	//Trigger
	m_dwTimeOut = 5000;
	m_bRecover = false;
	m_TriggerMode = KSJ_TRIGGER_INTERNAL;
	m_TriggerMethod = KSJ_TRIGGER_FALLINGEDGE;
	m_wDelay = 0;
	m_fFrameRate = 0;
	m_bEnable = false;
	m_bInvert = false;
	//Image
	m_bFlip = false;
	m_bMirror = false;
	m_nContrast = 0;
	m_nBrightness = 0;
	m_nSaturation = 0;
	m_nGamma = 0;
	m_HueEnable = false;
	memset(m_Hue, 0, sizeof(m_Hue));

	//Matrix
	m_WbMode = KSJ_WB_DISABLE;
	m_WbPresetting = KSJ_CT_5000K;
	m_nPhi = 0;
	memset(m_fWhiteMatrix, 0, sizeof(m_fWhiteMatrix));
	m_CcmMode = KSJ_CCM_DISABLE;
	m_CcmPresetting = KSJ_CT_5000K;
	memset(m_fColorMatrix, 0, sizeof(m_fColorMatrix));
}

CKSJCamClass::~CKSJCamClass(void)
{
	WriteIni();
}

void CKSJCamClass::Initial(int nIndex)
{
	m_nIndex = nIndex;
	ReadIni();
}

bool CKSJCamClass::IsOpen() const
{
	return ( m_nIndex != -1 ) ? TRUE : FALSE;
}
//
//bool CKSJCamClass::Capture(CPrImage* pImagey, DWORD nDelay)
//{
//	KSJDBG_OUTPUT(false, 11, _T("KSJCVS::++++CKSJCamClass::Capture++++"));
//	if (m_nIndex == -1)    return false;
//
//	if (pImagey == NULL)
//		pImagey = new CPrImage();
//
//	int    nCaptureWidth, nCaptureHeight, nCaptureBitCount;
//	KSJ_CaptureGetSizeEx(m_nIndex, &nCaptureWidth, &nCaptureHeight, &nCaptureBitCount);
//	BYTE    *pImageData = new BYTE[nCaptureWidth * nCaptureHeight * (nCaptureBitCount >> 3)];
//	int nRet = KSJ_CaptureRgbData(m_nIndex, pImageData);
//	if (nRet != RET_SUCCESS)
//	{
//		delete[] pImageData;
//		return false;
//	}
//		
//	BYTE    *pImageCKSData = new BYTE[nCaptureWidth * nCaptureHeight * (nCaptureBitCount >> 3)];
//	ConvertCKdataToKSJdata(pImageCKSData, pImageData, nCaptureWidth, nCaptureHeight, nCaptureBitCount);
//	pImagey->Create(nCaptureWidth, nCaptureHeight, nCaptureBitCount >> 3);
//	pImagey->SetBits(pImageCKSData, false);
//
//	delete[] pImageCKSData;
//	delete[] pImageData;
//	return true;
//}


void CKSJCamClass::Preview(HWND hWnd, RECT rtWndClient, bool bStart)
{
	if (-1 == m_nIndex) return;

	int    nPreviewWndWidth = 0;
	int    nPreviewWndHeight = 0;

	nPreviewWndWidth = rtWndClient.right - rtWndClient.left;
	nPreviewWndHeight = rtWndClient.bottom - rtWndClient.top;

	KSJ_PreviewSetPos(m_nIndex, hWnd, 0, 0, nPreviewWndWidth, nPreviewWndHeight);
	KSJ_PreviewStart(m_nIndex, bStart);
}

int CKSJCamClass::GetDeviceIndex()
{
	return m_nIndex;
}

void CKSJCamClass::ConvertCKdataToKSJdata(unsigned char *pImageKSJData, unsigned char *pImageCKData, int nWidth, int nHeight, int nBitCount)
{
	int            nWidthNum = nWidth * (nBitCount >> 3);
	unsigned char *pImageDataTmp = pImageCKData;

	for (int i = 0; i < nHeight; i++)
	{
		pImageDataTmp = pImageCKData + (nHeight - 1 - i) * nWidthNum;
		for (int j = 0; j < nWidthNum; j++)
		{
			*pImageKSJData = *pImageDataTmp;
			pImageKSJData++;
			pImageDataTmp++;
		}
	}

	return;
}

///////////////////////////////////////////////////////////////////Normal
int CKSJCamClass::PreviewSetFieldOfView(int nColStart, int nRowStart, int nColSize, int nRowSize, KSJ_ADDRESSMODE ColAddressMode, KSJ_ADDRESSMODE RowAddressMode)
{
	if (m_nIndex == -1)    return RET_FAIL;

	int nRet = KSJ_PreviewSetFieldOfView(m_nIndex, nColStart, nRowStart, nColSize, nRowSize, ColAddressMode, RowAddressMode);
	if (nRet != RET_SUCCESS)    return nRet;
	return KSJ_PreviewGetFieldOfView(m_nIndex, &m_nColStart, &m_nRowStart, &m_nColSize, &m_nRowSize, &ColAddressMode, &RowAddressMode);
}

int CKSJCamClass::PreviewGetDefaultFieldOfView(int *pnColStart, int *pnRowStart, int *pnColSize, int *pnRowSize, KSJ_ADDRESSMODE *pColAddressMode, KSJ_ADDRESSMODE *pRowAddressMode)
{
	if (m_nIndex == -1)    return RET_FAIL;

	int nRet = KSJ_PreviewGetDefaultFieldOfView(m_nIndex, pnColStart, pnRowStart, pnColSize, pnRowSize, pColAddressMode, pRowAddressMode);
	if (nRet != RET_SUCCESS)    return nRet;
	m_nColStart = *pnColStart;
	m_nRowStart = *pnRowStart;
	m_nColSize = *pnColSize;
	m_nRowSize = *pnRowSize;

	return nRet;
}

int CKSJCamClass::PreviewGetFieldOfView(int *pnColStart, int *pnRowStart, int *pnColSize, int *pnRowSize, KSJ_ADDRESSMODE *pColAddressMode, KSJ_ADDRESSMODE *pRowAddressMode)
{
	if (m_nIndex == -1)    return RET_FAIL;

	int nRet = KSJ_PreviewGetFieldOfView(m_nIndex, pnColStart, pnRowStart, pnColSize, pnRowSize, pColAddressMode, pRowAddressMode);
	if (nRet != RET_SUCCESS)    return nRet;
	m_nColStart = *pnColStart;
	m_nRowStart = *pnRowStart;
	m_nColSize = *pnColSize;
	m_nRowSize = *pnRowSize;

	return nRet;
}

int CKSJCamClass::CaptureSetFieldOfView(int nColStart, int nRowStart, int nColSize, int nRowSize, KSJ_ADDRESSMODE ColAddressMode, KSJ_ADDRESSMODE RowAddressMode)
{
	if (m_nIndex == -1)    return RET_FAIL;

	int nRet = KSJ_CaptureSetFieldOfView(m_nIndex, nColStart, nRowStart, nColSize, nRowSize, ColAddressMode, RowAddressMode);
	if (nRet != RET_SUCCESS)    return nRet;
	return KSJ_CaptureGetFieldOfView(m_nIndex, &m_nColStart, &m_nRowStart, &m_nColSize, &m_nRowSize, &ColAddressMode, &RowAddressMode);
}

int CKSJCamClass::PreviewSetFieldOfViewEx(int nColStart, int nRowStart, int nColSize, int nRowSize, KSJ_ADDRESSMODE ColAddressMode, KSJ_ADDRESSMODE RowAddressMode, unsigned short wMultiFrameNum)
{
	if (m_nIndex == -1)    return RET_FAIL;

	int nRet = KSJ_PreviewSetFieldOfViewEx(m_nIndex, nColStart, nRowStart, nColSize, nRowSize, ColAddressMode, RowAddressMode, wMultiFrameNum);
	if (nRet != RET_SUCCESS)    return nRet;
	return KSJ_PreviewGetFieldOfViewEx(m_nIndex, &m_nColStart, &m_nRowStart, &m_nColSize, &m_nRowSize, &ColAddressMode, &RowAddressMode, &wMultiFrameNum);
}

int CKSJCamClass::PreviewGetFieldOfViewEx(int *pnColStart, int *pnRowStart, int *pnColSize, int *pnRowSize, KSJ_ADDRESSMODE *pColAddressMode, KSJ_ADDRESSMODE *pRowAddressMode, unsigned short *pwMultiFrameNum)
{
	if (m_nIndex == -1)    return RET_FAIL;

	int nRet = KSJ_PreviewGetFieldOfViewEx(m_nIndex, pnColStart, pnRowStart, pnColSize, pnRowSize, pColAddressMode, pRowAddressMode, pwMultiFrameNum);
	if (nRet != RET_SUCCESS)    return nRet;
	m_nColStart		 = *pnColStart;
	m_nRowStart		 = *pnRowStart;
	m_nColSize		 = *pnColSize;
	m_nRowSize		 = *pnRowSize;
	m_wMultiFrameNum = *pwMultiFrameNum;

	return nRet;
}

int CKSJCamClass::CaptureSetFieldOfViewEx(int nColStart, int nRowStart, int nColSize, int nRowSize, KSJ_ADDRESSMODE ColAddressMode, KSJ_ADDRESSMODE RowAddressMode, unsigned short wMultiFrameNum)
{
	if (m_nIndex == -1)    return RET_FAIL;

	int nRet = KSJ_CaptureSetFieldOfViewEx(m_nIndex, nColStart, nRowStart, nColSize, nRowSize, ColAddressMode, RowAddressMode, wMultiFrameNum);
	if (nRet != RET_SUCCESS)    return nRet;
	return KSJ_CaptureGetFieldOfViewEx(m_nIndex, &m_nColStart, &m_nRowStart, &m_nColSize, &m_nRowSize, &ColAddressMode, &RowAddressMode, &wMultiFrameNum);
}

int CKSJCamClass::CaptureGetDefaultFieldOfView(int *pnColStart, int *pnRowStart, int *pnColSize, int *pnRowSize, KSJ_ADDRESSMODE *pColAddressMode, KSJ_ADDRESSMODE *pRowAddressMode)
{
	if (m_nIndex == -1)    return RET_FAIL;

	int nRet = KSJ_CaptureGetDefaultFieldOfView(m_nIndex, pnColStart, pnRowStart, pnColSize, pnRowSize, pColAddressMode, pRowAddressMode);
	if (nRet != RET_SUCCESS)    return nRet;
	m_nColStart = *pnColStart;
	m_nRowStart = *pnRowStart;
	m_nColSize = *pnColSize;
	m_nRowSize = *pnRowSize;
	return nRet;
}

int CKSJCamClass::GetParamRange(KSJ_PARAM Param, int *pnMinValue, int *pnMaxValue)
{
	if (m_nIndex == -1)    return RET_FAIL;

	return KSJ_GetParamRange(m_nIndex, Param, pnMinValue, pnMaxValue);
}

int CKSJCamClass::SetParam(KSJ_PARAM Param, int nValue)
{
	if (m_nIndex == -1)    return RET_FAIL;

	switch (Param)
	{
	case KSJ_EXPOSURE:
		m_nExposureTimeMs = nValue;
		break;
	case KSJ_RED:
		m_nGainRed = nValue;
		break;
	case KSJ_GREEN:
		m_nGainGreen = nValue;
		break;
	case KSJ_BLUE:
		m_nGainBlue = nValue;
		break;
	case KSJ_GAMMA:
		break;
	case KSJ_PREVIEW_COLUMNSTART:
		break;
	case KSJ_PREVIEW_ROWSTART:
		break;
	case KSJ_CAPTURE_COLUMNSTART:
		break;
	case KSJ_CAPTURE_ROWSTART:
		break;
	case KSJ_HORIZONTALBLANK:
		break;
	case KSJ_VERTICALBLANK:
		break;
	case KSJ_FLIP:
		m_bFlip = nValue ? TRUE : FALSE;
		break;
	case KSJ_BIN:
		break;
	case KSJ_MIRROR:
		m_bMirror = nValue ? TRUE : FALSE;
		break;
	case KSJ_CONTRAST:
		break;
	case KSJ_BRIGHTNESS:
		break;
	case KSJ_VGAGAIN:
		break;
	case KSJ_CLAMPLEVEL:
		break;
	case KSJ_CDSGAIN:
		break;
	case KSJ_RED_SHIFT:
		break;
	case KSJ_GREEN_SHIFT:
		break;
	case KSJ_BLUE_SHIFT:
		break;
	case KSJ_COMPANDING:
		break;
	case KSJ_EXPOSURE_LINES:
		m_nExposureLines = nValue;
		break;
	case KSJ_SATURATION:
		break;
	case KSJ_TRIGGERDELAY:
		break;
	case KSJ_STROBEDELAY:
		break;
	case KSJ_TRIGGER_MODE:
		break;
	case KSJ_TRIGGER_METHOD:
		break;
	case KSJ_BLACKLEVEL:
		break;
	case KSJ_BLACKLEVEL_THRESHOLD_AUTO:
		break;
	case KSJ_BLACKLEVEL_THRESHOLD_LO:
		break;
	case KSJ_BLACKLEVEL_THRESHOLD_HI:
		break;
	default:
		break;
	}

	return KSJ_SetParam(m_nIndex, Param, nValue);
}

int CKSJCamClass::GetParam(KSJ_PARAM Param, int *pnValue)
{
	if (m_nIndex == -1)    return RET_FAIL;

	int nRet = KSJ_GetParam(m_nIndex, Param, pnValue);
	if (nRet != RET_SUCCESS)    return nRet;

	switch (Param)
	{
	case KSJ_EXPOSURE:
		m_nExposureTimeMs = *pnValue;
		break;
	case KSJ_RED:
		m_nGainRed = *pnValue;
		break;
	case KSJ_GREEN:
		m_nGainGreen = *pnValue;
		break;
	case KSJ_BLUE:
		m_nGainBlue = *pnValue;
		break;
	case KSJ_GAMMA:
		break;
	case KSJ_PREVIEW_COLUMNSTART:
		break;
	case KSJ_PREVIEW_ROWSTART:
		break;
	case KSJ_CAPTURE_COLUMNSTART:
		break;
	case KSJ_CAPTURE_ROWSTART:
		break;
	case KSJ_HORIZONTALBLANK:
		break;
	case KSJ_VERTICALBLANK:
		break;
	case KSJ_FLIP:
		m_bFlip = *pnValue ? TRUE : FALSE;
		break;
	case KSJ_BIN:
		break;
	case KSJ_MIRROR:
		m_bMirror = *pnValue ? TRUE : FALSE;
		break;
	case KSJ_CONTRAST:
		break;
	case KSJ_BRIGHTNESS:
		break;
	case KSJ_VGAGAIN:
		break;
	case KSJ_CLAMPLEVEL:
		break;
	case KSJ_CDSGAIN:
		break;
	case KSJ_RED_SHIFT:
		break;
	case KSJ_GREEN_SHIFT:
		break;
	case KSJ_BLUE_SHIFT:
		break;
	case KSJ_COMPANDING:
		break;
	case KSJ_EXPOSURE_LINES:
		m_nExposureLines = *pnValue;
		break;
	case KSJ_SATURATION:
		break;
	case KSJ_TRIGGERDELAY:
		break;
	case KSJ_STROBEDELAY:
		break;
	case KSJ_TRIGGER_MODE:
		break;
	case KSJ_TRIGGER_METHOD:
		break;
	case KSJ_BLACKLEVEL:
		break;
	case KSJ_BLACKLEVEL_THRESHOLD_AUTO:
		break;
	case KSJ_BLACKLEVEL_THRESHOLD_LO:
		break;
	case KSJ_BLACKLEVEL_THRESHOLD_HI:
		break;
	default:
		break;
	}

	return nRet;
}

int CKSJCamClass::QueryFunction(KSJ_FUNCTION Function, int *pInfo)
{
	if (m_nIndex == -1)    return RET_FAIL;

	return KSJ_QueryFunction(m_nIndex, Function, pInfo);
}

int CKSJCamClass::AWAIBA_IsUsed(bool *bUsed)
{
	if (m_nIndex == -1)    return RET_FAIL;

	return KSJ_AWAIBA_IsUsed(m_nIndex, bUsed);
}

int CKSJCamClass::AWAIBA_GetSegmentNum(int *pnSegNum)
{
	if (m_nIndex == -1)    return RET_FAIL;

	return KSJ_AWAIBA_GetSegmentNum(m_nIndex, pnSegNum);
}

int CKSJCamClass::AWAIBA_GetGainRange(int nSegIndex, int *pnMin, int *pnMax)
{
	if (m_nIndex == -1)    return RET_FAIL;

	return KSJ_AWAIBA_GetGainRange(m_nIndex, nSegIndex, pnMin, pnMax);
}

int CKSJCamClass::AWAIBA_SetGain(int nSegIndex, int nGain)
{
	if (m_nIndex == -1)    return RET_FAIL;

	return KSJ_AWAIBA_SetGain(m_nIndex, nSegIndex, nGain);
}

int CKSJCamClass::AWAIBA_GetGain(int nSegIndex, int *pnGain)
{
	if (m_nIndex == -1)    return RET_FAIL;

	return KSJ_AWAIBA_GetGain(m_nIndex, nSegIndex, pnGain);
}

///////////////////////////////////////////////////////////////////////////////////////////Trigger
int CKSJCamClass::CaptureSetTimeOut(unsigned long dwTimeOut)
{
	if (m_nIndex == -1)    return RET_FAIL;

	int nRet = KSJ_CaptureSetTimeOut(m_nIndex, dwTimeOut);
	if (nRet != RET_SUCCESS)    return nRet;
	return KSJ_CaptureGetTimeOut(m_nIndex, &m_dwTimeOut);
}

int CKSJCamClass::CaptureGetTimeOut(unsigned long *pdwTimeOut)
{
	if (m_nIndex == -1)    return RET_FAIL;

	int nRet = KSJ_CaptureGetTimeOut(m_nIndex, pdwTimeOut);
	if (nRet != RET_SUCCESS)    return nRet;
	m_dwTimeOut = *pdwTimeOut;
	return nRet;
}

int CKSJCamClass::CaptureSetRecover(bool bRecover)
{
	if (m_nIndex == -1)    return RET_FAIL;

	m_bRecover = bRecover;
	return KSJ_CaptureSetRecover(m_nIndex,bRecover);
}

int CKSJCamClass::CaptureGetRecover(bool *pbRecover)
{
	if (m_nIndex == -1)    return RET_FAIL;

	int nRet = KSJ_CaptureGetRecover(m_nIndex, pbRecover);
	if (nRet != RET_SUCCESS)    return nRet;
	m_bRecover = *pbRecover;
	return nRet;
}

int CKSJCamClass::TriggerModeSet(KSJ_TRIGGERMODE TriggerMode)
{
	if (m_nIndex == -1)    return RET_FAIL;

	m_TriggerMode = TriggerMode;
	return KSJ_TriggerModeSet(m_nIndex, TriggerMode);
}

int CKSJCamClass::TriggerModeGet(KSJ_TRIGGERMODE *pTriggerMode)
{
	if (m_nIndex == -1)    return RET_FAIL;

	int nRet = KSJ_TriggerModeGet(m_nIndex, pTriggerMode);
	if (nRet != RET_SUCCESS)    return nRet;
	m_TriggerMode = *pTriggerMode;
	return nRet;
}

int CKSJCamClass::TriggerMethodSet(KSJ_TRIGGERMETHOD  TriggerMethod)
{
	if (m_nIndex == -1)    return RET_FAIL;

	m_TriggerMethod = TriggerMethod;
	return KSJ_TriggerMethodSet(m_nIndex, TriggerMethod);
}

int CKSJCamClass::TriggerMethodGet(KSJ_TRIGGERMETHOD *pTriggerMethod)
{
	if (m_nIndex == -1)    return RET_FAIL;

	int nRet = KSJ_TriggerMethodGet(m_nIndex, pTriggerMethod);
	if (nRet != RET_SUCCESS)    return nRet;
	m_TriggerMethod = *pTriggerMethod;
	return nRet;
}

int CKSJCamClass::TriggerDelayGetRange(unsigned short *wMin, unsigned short *wMax)
{
	if (m_nIndex == -1)    return RET_FAIL;

	return KSJ_TriggerDelayGetRange(m_nIndex, wMin, wMax);
}

int CKSJCamClass::TriggerDelaySet(unsigned short wDelay)
{
	if (m_nIndex == -1)    return RET_FAIL;

	m_wDelay = wDelay;
	return KSJ_TriggerDelaySet(m_nIndex, wDelay);
}

int CKSJCamClass::TriggerDelayGet(unsigned short *pwDelay)
{
	if (m_nIndex == -1)    return RET_FAIL;

	int nRet = KSJ_TriggerDelayGet(m_nIndex, pwDelay);
	if (nRet != RET_SUCCESS)    return nRet;
	m_wDelay = *pwDelay;
	return nRet;
}

int CKSJCamClass::CaptureSetTimeOutEx(unsigned long dwTimeOut, bool bRecover)
{
	if (m_nIndex == -1)    return RET_FAIL;

	m_dwTimeOut = dwTimeOut;
	m_bRecover = bRecover;
	return KSJ_CaptureSetTimeOutEx(m_nIndex, dwTimeOut, bRecover);
}

int CKSJCamClass::CaptureGetTimeOutEx(unsigned long *pdwTimeOut, bool *pbRecover)
{
	if (m_nIndex == -1)    return RET_FAIL;

	int nRet = KSJ_CaptureGetTimeOutEx(m_nIndex, pdwTimeOut, pbRecover);
	if (nRet != RET_SUCCESS)    return nRet;
	m_dwTimeOut = *pdwTimeOut;
	m_bRecover = *pbRecover;
	return nRet;
}

int CKSJCamClass::SetFixedFrameRateEx(float fFrameRate)
{
	if (m_nIndex == -1)    return RET_FAIL;

	m_fFrameRate = fFrameRate;
	return KSJ_SetFixedFrameRateEx(m_nIndex, fFrameRate);
}

int CKSJCamClass::GetFixedFrameRateEx(float *pfFrameRate)
{
	if (m_nIndex == -1)    return RET_FAIL;

	int nRet = KSJ_GetFixedFrameRateEx(m_nIndex, pfFrameRate);
	if (nRet != RET_SUCCESS)    return nRet;
	m_fFrameRate = *pfFrameRate;
	return nRet;
}

int CKSJCamClass::EmptyFrameBuffer()
{
	if (m_nIndex == -1)    return RET_FAIL;

	return KSJ_EmptyFrameBuffer(m_nIndex);
}

int CKSJCamClass::FlashControlGet(bool *pbEnable, bool *pbInvert, int *pnMode)
{
	if (m_nIndex == -1)    return RET_FAIL;

	int nRet = KSJ_FlashControlGet(m_nIndex, pbEnable, pbInvert, pnMode);
	if (nRet != RET_SUCCESS)    return nRet;
	m_bEnable = *pbEnable;
	m_bInvert = *pbInvert;
	return nRet;
}

int CKSJCamClass::FlashControlSet(bool bEnable, bool bInvert, int nMode)
{
	if (m_nIndex == -1)    return RET_FAIL;

	m_bEnable = bEnable;
	m_bInvert = bInvert;
	return KSJ_FlashControlSet(m_nIndex, bEnable, bInvert, nMode);
}

///////////////////////////////////////////////////////////////////////////////////////Image
int CKSJCamClass::ProcessContrastGetRange(int *pnMinContrast, int *pnMaxContrast)
{
	if (m_nIndex == -1)    return RET_FAIL;

	return KSJ_ProcessContrastGetRange(m_nIndex, pnMinContrast, pnMaxContrast);
}

int CKSJCamClass::ProcessContrastSet(int nContrast)
{
	if (m_nIndex == -1)    return RET_FAIL;

	m_nContrast = nContrast;
	return KSJ_ProcessContrastSet(m_nIndex, nContrast);
}

int CKSJCamClass::ProcessContrastGet(int *pnContrast)
{
	if (m_nIndex == -1)    return RET_FAIL;

	int nRet = KSJ_ProcessContrastGet(m_nIndex, pnContrast);
	if (nRet != RET_SUCCESS)    return nRet;
	m_nContrast = *pnContrast;
	return nRet;
}

int CKSJCamClass::ProcessBrightnessGetRange(int *pnMinBrightness, int *pnMaxBrightness)
{
	if (m_nIndex == -1)    return RET_FAIL;

	return KSJ_ProcessBrightnessGetRange(m_nIndex, pnMinBrightness, pnMaxBrightness);
}

int CKSJCamClass::ProcessBrightnessSet(int nBrightness)
{
	if (m_nIndex == -1)    return RET_FAIL;

	m_nBrightness = nBrightness;
	return KSJ_ProcessBrightnessSet(m_nIndex, nBrightness);
}

int CKSJCamClass::ProcessBrightnessGet(int *pnBrightness)
{
	if (m_nIndex == -1)    return RET_FAIL;

	int nRet = KSJ_ProcessBrightnessGet(m_nIndex, pnBrightness);
	if (nRet != RET_SUCCESS)    return nRet;
	m_nBrightness = *pnBrightness;
	return nRet;
}

int CKSJCamClass::ProcessSaturationGetRange(int *pnMinSaturation, int *pnMaxSaturation)
{
	if (m_nIndex == -1)    return RET_FAIL;

	return KSJ_ProcessSaturationGetRange(m_nIndex, pnMinSaturation, pnMaxSaturation);
}

int CKSJCamClass::ProcessSaturationSet(int nSaturation)
{
	if (m_nIndex == -1)    return RET_FAIL;

	m_nSaturation = nSaturation;
	return KSJ_ProcessSaturationSet(m_nIndex, nSaturation);
}

int CKSJCamClass::ProcessSaturationGet(int *pnStaturation)
{
	if (m_nIndex == -1)    return RET_FAIL;

	int nRet = KSJ_ProcessSaturationGet(m_nIndex, pnStaturation);
	if (nRet != RET_SUCCESS)    return nRet;
	m_nSaturation = *pnStaturation;
	return nRet;
}

int CKSJCamClass::GammaGetRange(int *pnMinGamma, int *pnMaxGamm)
{
	if (m_nIndex == -1)    return RET_FAIL;

	return KSJ_GammaGetRange(m_nIndex, pnMinGamma, pnMaxGamm);
}

int CKSJCamClass::GammaGetValue(int *pnValue)
{
	if (m_nIndex == -1)    return RET_FAIL;

	int nRet = KSJ_GammaGetValue(m_nIndex, pnValue);
	if (nRet != RET_SUCCESS)    return nRet;
	m_nGamma = *pnValue;
	return nRet;
}

int CKSJCamClass::GammaSetValue(int nValue)
{
	if (m_nIndex == -1)    return RET_FAIL;

	m_nGamma = nValue;
	return KSJ_GammaSetValue(m_nIndex, nValue);
}

int CKSJCamClass::HueSaturationSet(KSJHueRange HueRange, int nHue, int nSaturation, int nLightness)
{
	if (m_nIndex == -1)    return RET_FAIL;

	m_Hue[HueRange].nHue		= nHue;
	m_Hue[HueRange].nSaturation = nSaturation;
	m_Hue[HueRange].nLightness  = nLightness;

	return KSJ_HueSaturationSet(m_nIndex, HueRange, nHue, nSaturation, nLightness);
}

int CKSJCamClass::HueSaturationGet(KSJHueRange HueRange, int *pnHue, int *pnSaturation, int *pnLightness)
{
	if (m_nIndex == -1)    return RET_FAIL;

	int nRet = KSJ_HueSaturationGet(m_nIndex, HueRange, pnHue, pnSaturation, pnLightness);
	if (nRet != RET_SUCCESS)    return nRet;
	m_Hue[HueRange].nHue = *pnHue;
	m_Hue[HueRange].nSaturation = *pnSaturation;
	m_Hue[HueRange].nLightness = *pnLightness;
	return nRet;
}

int CKSJCamClass::HueSaturationSetEnable(bool bEnable)
{
	if (m_nIndex == -1)    return RET_FAIL;

	m_HueEnable = bEnable;
	return KSJ_HueSaturationSetEnable(m_nIndex, bEnable);
}

///////////////////////////////////////////////////////////////////Matrix
int CKSJCamClass::WhiteBalanceSet(KSJ_WB_MODE WbMode)
{
	if (m_nIndex == -1)    return RET_FAIL;

	m_WbMode = WbMode;
	return KSJ_WhiteBalanceSet(m_nIndex, WbMode);
}

int CKSJCamClass::WhiteBalanceGet(KSJ_WB_MODE *pWbMode)
{
	if (m_nIndex == -1)    return RET_FAIL;

	int nRet = KSJ_WhiteBalanceGet(m_nIndex, pWbMode);
	if (nRet != RET_SUCCESS)    return nRet;
	m_WbMode = *pWbMode;
	return nRet;
}

int CKSJCamClass::WhiteBalancePresettingSet(KSJ_COLOR_TEMPRATURE WbPresetting)
{
	if (m_nIndex == -1)    return RET_FAIL;

	m_WbPresetting = WbPresetting;
	return KSJ_WhiteBalancePresettingSet(m_nIndex, WbPresetting);
}

int CKSJCamClass::WhiteBalancePresettingGet(KSJ_COLOR_TEMPRATURE *pWbPresetting)
{
	if (m_nIndex == -1)    return RET_FAIL;

	int nRet = KSJ_WhiteBalancePresettingGet(m_nIndex, pWbPresetting);
	if (nRet != RET_SUCCESS)    return nRet;
	m_WbPresetting = *pWbPresetting;
	return nRet;
}

int CKSJCamClass::WhiteBalanceAutoSetCallBack(KSJ_WB_CALLBACK pfCallBack, void *lpContext)
{
	if (m_nIndex == -1)    return RET_FAIL;

	return KSJ_WhiteBalanceAutoSetCallBack(m_nIndex, pfCallBack, lpContext);
}

int CKSJCamClass::WhiteBalanceAutoSet(int nPhi)
{
	if (m_nIndex == -1)    return RET_FAIL;

	m_nPhi = nPhi;
	return KSJ_WhiteBalanceAutoSet(m_nIndex, nPhi);
}

int CKSJCamClass::WhiteBalanceAutoGet(int *pnPhi)
{
	if (m_nIndex == -1)    return RET_FAIL;

	int nRet = KSJ_WhiteBalanceAutoGet(m_nIndex, pnPhi);
	if (nRet != RET_SUCCESS)    return nRet;
	m_nPhi = *pnPhi;
	return nRet;
}

int CKSJCamClass::WhiteBalanceMatrixSet(float fMatrix[3])
{
	if (m_nIndex == -1)    return RET_FAIL;

	m_fWhiteMatrix[0] = fMatrix[0];
	m_fWhiteMatrix[1] = fMatrix[1];
	m_fWhiteMatrix[2] = fMatrix[2];
	return KSJ_WhiteBalanceMatrixSet(m_nIndex, fMatrix);
}

int CKSJCamClass::WhiteBalanceMatrixGet(float fMatrix[3])
{
	if (m_nIndex == -1)    return RET_FAIL;

	int nRet = KSJ_WhiteBalanceMatrixGet(m_nIndex, fMatrix);
	if (nRet != RET_SUCCESS)    return nRet;
	m_fWhiteMatrix[0] = fMatrix[0];
	m_fWhiteMatrix[1] = fMatrix[1];
	m_fWhiteMatrix[2] = fMatrix[2];
	return nRet;
}

int CKSJCamClass::ColorCorrectionSet(KSJ_CCM_MODE CcmMode)
{
	if (m_nIndex == -1)    return RET_FAIL;

	m_CcmMode = CcmMode;
	return KSJ_ColorCorrectionSet(m_nIndex, CcmMode);
}

int CKSJCamClass::ColorCorrectionGet(KSJ_CCM_MODE *pCcmMode)
{
	if (m_nIndex == -1)    return RET_FAIL;

	int nRet = KSJ_ColorCorrectionGet(m_nIndex, pCcmMode);
	if (nRet != RET_SUCCESS)    return nRet;
	m_CcmMode = *pCcmMode;
	return nRet;
}

int CKSJCamClass::ColorCorrectionPresettingSet(KSJ_COLOR_TEMPRATURE CcmPresetting)
{
	if (m_nIndex == -1)    return RET_FAIL;

	m_CcmPresetting = CcmPresetting;
	return KSJ_ColorCorrectionPresettingSet(m_nIndex, CcmPresetting);
}

int CKSJCamClass::ColorCorrectionPresettingGet(KSJ_COLOR_TEMPRATURE *pCcmPresetting)
{
	if (m_nIndex == -1)    return RET_FAIL;

	int nRet = KSJ_ColorCorrectionPresettingGet(m_nIndex, pCcmPresetting);
	if (nRet != RET_SUCCESS)    return nRet;
	m_CcmPresetting = *pCcmPresetting;
	return nRet;
}

int CKSJCamClass::ColorCorrectionMatrixSet(float fMatrix[3][3])
{
	if (m_nIndex == -1)    return RET_FAIL;

	memcpy(m_fColorMatrix, fMatrix, sizeof(m_fColorMatrix));
	return KSJ_ColorCorrectionMatrixSet(m_nIndex, fMatrix);
}

int CKSJCamClass::ColorCorrectionMatrixGet(float fMatrix[3][3])
{
	if (m_nIndex == -1)    return RET_FAIL;

	int nRet = KSJ_ColorCorrectionMatrixGet(m_nIndex, fMatrix);
	if (nRet != RET_SUCCESS)    return nRet;
	memcpy(m_fColorMatrix, fMatrix, sizeof(m_fColorMatrix));
	return nRet;
}