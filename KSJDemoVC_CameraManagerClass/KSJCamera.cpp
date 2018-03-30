#include "stdafx.h"
#include "KSJCamera.h"

void CKSJCamera::PreviewCallback(unsigned char *pImageData, int nWidth, int nHeight, int nBitCount)
{
	if (m_bIsPaused)		return;

	memcpy(m_pImage.m_lpDibArray, pImageData, m_pImage.m_ImageSize);

	if (m_nCapturedImageNum < 1000)
	{
		m_nCapturedImageNum++;
	}
	else
	{
		m_nCapturedImageNum = 0;
	}

	if (m_pConnectView != NULL && m_pConnectView->GetSafeHwnd() != NULL)
	{
		m_pConnectView->Invalidate(FALSE);
	}
}


VOID WINAPI PREVIEWCALLBACK0( unsigned char *pImageData, int nWidth, int nHeight, int nBitCount,  void *lpContext )
{
	CKSJCamera *pCamera = (CKSJCamera *)lpContext;

	return pCamera->PreviewCallback(pImageData, nWidth, nHeight, nBitCount);
}

VOID WINAPI PREVIEWCALLBACK1( unsigned char *pImageData, int nWidth, int nHeight, int nBitCount,  void *lpContext )
{
	CKSJCamera *pCamera = (CKSJCamera *)lpContext;

	return pCamera->PreviewCallback(pImageData, nWidth, nHeight, nBitCount);

}

VOID WINAPI PREVIEWCALLBACK2( unsigned char *pImageData, int nWidth, int nHeight, int nBitCount,  void *lpContext )
{
	CKSJCamera *pCamera = (CKSJCamera *)lpContext;

	return pCamera->PreviewCallback(pImageData, nWidth, nHeight, nBitCount);

}

VOID WINAPI PREVIEWCALLBACK3( unsigned char *pImageData, int nWidth, int nHeight, int nBitCount,  void *lpContext )
{
	CKSJCamera *pCamera = (CKSJCamera *)lpContext;

	return pCamera->PreviewCallback(pImageData, nWidth, nHeight, nBitCount);

}

VOID WINAPI PREVIEWCALLBACK4( unsigned char *pImageData, int nWidth, int nHeight, int nBitCount,  void *lpContext )
{
	CKSJCamera *pCamera = (CKSJCamera *)lpContext;

	return pCamera->PreviewCallback(pImageData, nWidth, nHeight, nBitCount);

}

CKSJCamera::CKSJCamera(KSJ_DEVICETYPE DeviceType, int nIndex, int nSerials) : m_DeviceType(DeviceType), m_nIndex(nIndex), m_nSerials(nSerials)
{
	m_nExposureTime = 10;
	m_bIsConnected  = FALSE;
	m_bIsPaused     = FALSE;
	m_pConnectView = NULL;

	CameraParam GainParam;
	GainParam.readCameraParam();

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

	if (!SetExposureTime(m_nIndex, m_nExposureTime))
	{
		return;
	}
	//获得gain
	int gain_g;
	KSJ_GetParam(m_nIndex, KSJ_GREEN, &gain_g);
	KSJ_SetParam(m_nIndex, KSJ_GREEN, GainParam.m_dGainGreen[m_nSerials]);
	KSJ_SetParam(m_nIndex, KSJ_RED, GainParam.m_dGainRed[m_nSerials]);
	KSJ_SetParam(m_nIndex, KSJ_BLUE, GainParam.m_dGainBlue[m_nSerials]);
	KSJ_SetParam(m_nIndex, KSJ_CDSGAIN, 100);
	//获得最大分辨率
	int nColumnStart; int nRowStart; int nColumnSize; int nRowSize; KSJ_ADDRESSMODE ColumnAddressMode; KSJ_ADDRESSMODE RowAddressMode;
	KSJ_CaptureGetDefaultFieldOfView(m_nIndex, &nColumnStart, &nColumnStart, &m_nWidth, &m_nHeight, &ColumnAddressMode, &RowAddressMode);

	//设置采集分辨率
	KSJ_CaptureSetFieldOfView(m_nIndex, 0, 0, m_nWidth, m_nHeight, KSJ_SKIPNONE, KSJ_SKIPNONE);
	KSJ_PreviewSetFieldOfView(m_nIndex, 0, 0, m_nWidth, m_nHeight, KSJ_SKIPNONE, KSJ_SKIPNONE);
	//分配内存
	m_pImage.CreateEmpty(m_nWidth, m_nHeight, 8, 0);

	switch (m_nSerials)   // 如果callback是针对特定相机的，这里是不是应该用serials呢？？？
	{
	case 0:
		KSJ_PreviewSetCallback(m_nIndex, PREVIEWCALLBACK0, this);
		break;
	case 1:
		KSJ_PreviewSetCallback(m_nIndex, PREVIEWCALLBACK1, this);
		break;
	case 2:
		KSJ_PreviewSetCallback(m_nIndex, PREVIEWCALLBACK2, this);
		break;
	case 3:
		KSJ_PreviewSetCallback(m_nIndex, PREVIEWCALLBACK3, this);
		break;
	case 4:
		KSJ_PreviewSetCallback(m_nIndex, PREVIEWCALLBACK4, this);
		break;
	}
}


CKSJCamera::~CKSJCamera()
{
	KSJ_PreviewStart(m_nIndex, false);
}

BOOL CKSJCamera::ConnectCamera()
{
	KSJ_PreviewSetPos(m_nIndex, NULL, 0, 0, 0, 0);
	KSJ_PreviewStart(m_nIndex, true);

	m_bIsConnected = TRUE;

	return TRUE;
}

BOOL CKSJCamera::CaptureImage()
{
	int nRet = RET_SUCCESS;

	CTimeCount cct;
	cct.Start();
	if (m_pIsRGB)
		nRet = KSJ_CaptureRgbData/*AfterEmptyFrameBuffer*/(m_nIndex, m_pImage.m_lpDibArray);  //@whq 2016-6-25  不等待清除buffer
	else
		nRet = KSJ_CaptureRawData/*AfterEmptyFrameBuffer*/(m_nIndex, m_pImage.m_lpDibArray);
	cct.End();
	TRACE("KSJ_CaptureRawData Time = %lf\n", cct.GetUseTime());

	if (m_pConnectView != NULL)
		m_pConnectView->Invalidate(FALSE);

	return (nRet == RET_SUCCESS);
}

BOOL CKSJCamera::SetExposureTime(int nTime)
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

BOOL CKSJCamera::PauseCamera(BOOL bIsWorking)
{
	int nRet = RET_SUCCESS;

	m_bIsPaused = !bIsWorking;  //WHQ
	return (nRet == RET_SUCCESS);

	if (!bIsWorking)
	{
		nRet = KSJ_PreviewPause(m_nIndex, TRUE);  //@whq 2016-6-28 
	}
	else
	{
		nRet = KSJ_PreviewPause(m_nIndex, FALSE);
		//nRet = KSJ_PreviewStart(m_nIndex, TRUE);
		m_nCapturedImageNum = 0;
	}

	return (nRet == RET_SUCCESS);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 以下的函数我没有改，请按照我的模式进行修改。


BOOL CKSJCamera::SetPreviewPos(int nCamIndex, HWND hWnd, CRect sRect)
{
	int nRet;
	double tmpscalex = sRect.Width()/(double)m_pDeviceInfo[nCamIndex].m_nWidth;
	double tmpscaley = sRect.Height()/(double)m_pDeviceInfo[nCamIndex].m_nHeight;
	if(tmpscalex<tmpscaley)
	{
		m_pShowScale[nCamIndex] = tmpscalex;
		sRect.bottom = sRect.top  + int(m_pShowScale[nCamIndex]*m_pDeviceInfo[nCamIndex].m_nHeight + 0.5);
	}
	else
	{
		m_pShowScale[nCamIndex] = tmpscaley;
		sRect.right  = sRect.left + int(m_pShowScale[nCamIndex]*m_pDeviceInfo[nCamIndex].m_nWidth  + 0.5);
	}
	nRet = KSJ_PreviewSetPos(nCamIndex, hWnd, sRect.left, sRect.right, sRect.Width(), sRect.Height());
	return (nRet==RET_SUCCESS);
}


BOOL CKSJCamera::SetSoftTriggerMode(int nCamIndex)
{
	//return PauseCamera(nCamIndex,FALSE);  //@whq 2016-6-28 
	if(m_pIsTriggerMode[nCamIndex])  //@whq 2016-6-25 
		return TRUE;
	int nRet = KSJ_TriggerModeSet(nCamIndex, KSJ_TRIGGER_SOFTWARE);
	nRet &= KSJ_PreviewSetCallback(nCamIndex, NULL, NULL);
	m_pIsTriggerMode[nCamIndex] = TRUE;
	return (nRet==RET_SUCCESS);
//	return TRUE;
}

BOOL CKSJCamera::SetFreeMode(int nCamIndex)
{
	int nRet = KSJ_TriggerModeSet(nCamIndex, KSJ_TRIGGER_INTERNAL);
	switch(nCamIndex)
	{
	case 0:
		nRet &= KSJ_PreviewSetCallback( nCamIndex, PREVIEWCALLBACK0, this );
		break;
	case 1:
		nRet &= KSJ_PreviewSetCallback( nCamIndex, PREVIEWCALLBACK1, this );
		break;
	case 2:
		nRet &= KSJ_PreviewSetCallback( nCamIndex, PREVIEWCALLBACK2, this );
		break;
	case 3:
		nRet &= KSJ_PreviewSetCallback( nCamIndex, PREVIEWCALLBACK3, this );
		break;
// 	case 4:
// 		nRet &= KSJ_PreviewSetCallback( nCamIndex, PREVIEWCALLBACK4, this );
// 		break;
	}
	m_pIsTriggerMode[nCamIndex] = FALSE;
	return (nRet==RET_SUCCESS);
//	return TRUE;

}

