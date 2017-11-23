#include "stdafx.h"
#include "KSJCamera.h"

void CKSJCamera::PreviewCallback(HDC hDC, unsigned char *pImageData, int nWidth, int nHeight, int nBitCount, int nNo)
{
	if (m_bIsPaused)		return;

	CString strTime;
	strTime.Format("%d", nNo);
	SaveDC(hDC);
	SetBkMode(hDC, TRANSPARENT);

	HFONT hf;
	hf = CreateFont(nHeight / 10, 0, 0, 0, FW_BLACK, FALSE, FALSE, FALSE,
		GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FIXED_PITCH | FF_MODERN, "宋体");
	::SelectObject(hDC, hf);
	TextOut(hDC, nWidth / 20, nHeight / 14, strTime, strTime.GetLength());
	::DeleteObject(hf);

	RestoreDC(hDC, -1);
}


VOID WINAPI PREVIEWCALLBACK0(HDC hDC, unsigned char *pImageData, int nWidth, int nHeight, int nBitCount, void *lpContext)
{
	CKSJCamera *pCamera = (CKSJCamera *)lpContext;

	return pCamera->PreviewCallback(hDC, pImageData, nWidth, nHeight, nBitCount, 0);
}

VOID WINAPI PREVIEWCALLBACK1(HDC hDC, unsigned char *pImageData, int nWidth, int nHeight, int nBitCount, void *lpContext)
{
	CKSJCamera *pCamera = (CKSJCamera *)lpContext;

	return pCamera->PreviewCallback(hDC, pImageData, nWidth, nHeight, nBitCount, 1);
}

VOID WINAPI PREVIEWCALLBACK2(HDC hDC, unsigned char *pImageData, int nWidth, int nHeight, int nBitCount, void *lpContext)
{
	CKSJCamera *pCamera = (CKSJCamera *)lpContext;

	return pCamera->PreviewCallback(hDC, pImageData, nWidth, nHeight, nBitCount, 2);
}

VOID WINAPI PREVIEWCALLBACK3(HDC hDC, unsigned char *pImageData, int nWidth, int nHeight, int nBitCount, void *lpContext)
{
	CKSJCamera *pCamera = (CKSJCamera *)lpContext;

	return pCamera->PreviewCallback(hDC, pImageData, nWidth, nHeight, nBitCount, 3);
}

VOID WINAPI PREVIEWCALLBACK4(HDC hDC, unsigned char *pImageData, int nWidth, int nHeight, int nBitCount, void *lpContext)
{
	CKSJCamera *pCamera = (CKSJCamera *)lpContext;

	return pCamera->PreviewCallback(hDC, pImageData, nWidth, nHeight, nBitCount, 4);
}

CKSJCamera::CKSJCamera(KSJ_DEVICETYPE DeviceType, int nIndex, int nSerials) : m_DeviceType(DeviceType), m_nIndex(nIndex), m_nSerials(nSerials)
{
	m_nExposureTime = 10;
	m_bIsConnected  = FALSE;
	m_bIsPaused     = FALSE;
	m_pConnectView = NULL;

	switch (m_DeviceType)
	{
	case KSJ_UC320C_MRNN:
		m_pIsRGB = TRUE;
		break;
	case KSJ_UC320C_MRYY:
		m_pIsRGB = TRUE;
		break;
	case KSJ_UC500C_MRYY:
		m_pIsRGB = TRUE;
		break;
	case KSJ_UC500C_MRNN:
		m_pIsRGB = TRUE;
		break;
	}

	//设置Bayer模式为灰度
	if (m_pIsRGB)
		KSJ_BayerSetMode(m_nIndex, KSJ_BGGR_GRAY8);

	if (m_DeviceType == KSJ_MUC36M_MGYYO)
	{
		KSJ_SetParam(m_nIndex, KSJ_FLIP, 0);
	}

	//获得最大分辨率
	int nColumnStart; int nRowStart; int nColumnSize; int nRowSize; KSJ_ADDRESSMODE ColumnAddressMode; KSJ_ADDRESSMODE RowAddressMode;
	KSJ_CaptureGetDefaultFieldOfView(m_nIndex, &nColumnStart, &nColumnStart, &m_nWidth, &m_nHeight, &ColumnAddressMode, &RowAddressMode);

	//设置采集分辨率
	KSJ_CaptureSetFieldOfView(m_nIndex, 0, 0, m_nWidth, m_nHeight, KSJ_SKIPNONE, KSJ_SKIPNONE);
	KSJ_PreviewSetFieldOfView(m_nIndex, 0, 0, m_nWidth, m_nHeight, KSJ_SKIPNONE, KSJ_SKIPNONE);
	//分配内存
	int    nCaptureWidth, nCaptureHeight, nCaptureBitCount;

	int nRet = KSJ_CaptureGetSizeEx(m_nIndex, &nCaptureWidth, &nCaptureHeight, &nCaptureBitCount);

	m_pImageData = new BYTE[nCaptureWidth * nCaptureHeight * (nCaptureBitCount >> 3)];

	switch (m_nSerials)   // 如果callback是针对特定相机的，这里是不是应该用serials呢？？？
	{
	case 0:
		KSJ_PreviewSetCallbackEx(m_nIndex, PREVIEWCALLBACK0, this);
		break;
	case 1:
		KSJ_PreviewSetCallbackEx(m_nIndex, PREVIEWCALLBACK1, this);
		break;
	case 2:
		KSJ_PreviewSetCallbackEx(m_nIndex, PREVIEWCALLBACK2, this);
		break;
	case 3:
		KSJ_PreviewSetCallbackEx(m_nIndex, PREVIEWCALLBACK3, this);
		break;
	case 4:
		KSJ_PreviewSetCallbackEx(m_nIndex, PREVIEWCALLBACK4, this);
		break;
	}
}


CKSJCamera::~CKSJCamera()
{
	delete[] m_pImageData;
}

BOOL CKSJCamera::ConnectCamera(BOOL bStart)
{
	CRect Rect;
	m_pConnectView->GetWindowRect(&Rect);
	SetPreviewPos(m_nIndex, m_pConnectView->m_hWnd, Rect);
	KSJ_PreviewStart(m_nIndex, (bStart ? true : false));
	m_bIsConnected = TRUE;
	return TRUE;
}

BOOL CKSJCamera::CaptureImage()
{
	int nRet = RET_SUCCESS;
	nRet = KSJ_CaptureRgbData(m_nIndex, m_pImageData);
	return (nRet == RET_SUCCESS);
}


BOOL CKSJCamera::PauseCamera(BOOL bIsWorking)
{
	int nRet = RET_SUCCESS;

	m_bIsPaused = !bIsWorking;  //WHQ
	return (nRet == RET_SUCCESS);

	nRet = KSJ_PreviewPause(m_nIndex, (bIsWorking ? true : false));

	return (nRet == RET_SUCCESS);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 以下的函数我没有改，请按照我的模式进行修改。


BOOL CKSJCamera::SetPreviewPos(int nCamIndex, HWND hWnd, CRect sRect)
{
	int nRet;
	int    nPreviewWndWidth = 0;
	int    nPreviewWndHeight = 0;

	nPreviewWndWidth = sRect.right - sRect.left;
	nPreviewWndHeight = sRect.bottom - sRect.top;

	// You should assign window for preview once
	nRet = KSJ_PreviewSetPos(nCamIndex, hWnd, 0, 0, nPreviewWndWidth, nPreviewWndHeight);

	return nRet;
}


int CKSJCamera::SetTriggerMode(KSJ_TRIGGERMODE TriggerMode)
{
	int nRet = KSJ_TriggerModeSet(m_nIndex, TriggerMode);

	return nRet;
}


int CKSJCamera::ConnectView(CWnd* pConnectView)
{
	m_pConnectView = pConnectView;
	return RET_SUCCESS;
}


int CKSJCamera::SetExposureTime(int nTime)
{
	int ExposureMin, ExposureMax;
	KSJ_GetParamRange(m_nIndex, KSJ_EXPOSURE, &ExposureMin, &ExposureMax);
	if (nTime < ExposureMin)
	{
		nTime = ExposureMin;
	}
	if (nTime > ExposureMax)
	{
		nTime = ExposureMax;
	}
	int nRet = KSJ_SetParam(m_nIndex, KSJ_EXPOSURE, nTime);
	if (nRet == RET_SUCCESS)
	{
		m_nExposureTime = nTime;
	}
	return (nRet == RET_SUCCESS);
}

int CKSJCamera::GetExposureTime(int* pnTime)
{
	return KSJ_GetParam(m_nIndex, KSJ_EXPOSURE, pnTime);
}

int CKSJCamera::SetExposureLines(int nLines)
{
	int ExposureMin, ExposureMax;
	KSJ_GetParamRange(m_nIndex, KSJ_EXPOSURE_LINES, &ExposureMin, &ExposureMax);
	if (nLines < ExposureMin)
	{
		nLines = ExposureMin;
	}
	if (nLines > ExposureMax)
	{
		nLines = ExposureMax;
	}
	int nRet = KSJ_SetParam(m_nIndex, KSJ_EXPOSURE_LINES, nLines);
	if (nRet == RET_SUCCESS)
	{
		m_nExposureTime = nLines;
	}
	return (nRet == RET_SUCCESS);
}

int CKSJCamera::GetExposureLines(int* pnLines)
{
	return KSJ_GetParam(m_nIndex, KSJ_EXPOSURE_LINES, pnLines);
}

int CKSJCamera::SetGain(int nGain)
{
	int nMin, nMax;
	KSJ_GetParamRange(m_nIndex, KSJ_RED, &nMin, &nMax);
	if (nGain < nMin)
	{
		nGain = nMin;
	}
	if (nGain > nMax)
	{
		nGain = nMax;
	}
	int nRet = KSJ_SetParam(m_nIndex, KSJ_RED, nGain);
	if (nRet == RET_SUCCESS)
	{
		m_nGain = nGain;
	}
	return (nRet == RET_SUCCESS);
}

int CKSJCamera::GetGain(int* pnGain)
{
	return KSJ_GetParam(m_nIndex, KSJ_RED, pnGain);
}