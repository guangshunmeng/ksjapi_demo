#include "stdafx.h"
#include "KSJCamera.h"

#ifndef _WIN32
using namespace zbar;

typedef unsigned int        DWORD;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;


typedef struct tagBITMAPFILEHEADER {
	WORD    bfType;
	DWORD   bfSize;
	WORD    bfReserved1;
	WORD    bfReserved2;
	DWORD   bfOffBits;
}  BITMAPFILEHEADER, *LPBITMAPFILEHEADER, *PBITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER{
	DWORD      biSize;
	int       biWidth;
	int       biHeight;
	WORD       biPlanes;
	WORD       biBitCount;
	DWORD      biCompression;
	DWORD      biSizeImage;
	int       biXPelsPerMeter;
	int       biYPelsPerMeter;
	DWORD      biClrUsed;
	DWORD      biClrImportant;
}  BITMAPINFOHEADER, *LPBITMAPINFOHEADER, *PBITMAPINFOHEADER;

typedef struct tagRGBQUAD {
	BYTE    rgbBlue;
	BYTE    rgbGreen;
	BYTE    rgbRed;
	BYTE    rgbReserved;
} RGBQUAD;

typedef struct tagBITMAPINFO {
	BITMAPINFOHEADER    bmiHeader;
	RGBQUAD             bmiColors[1];
} BITMAPINFO, *LPBITMAPINFO, *PBITMAPINFO;
#endif

#define MAKEWIDTHBYTES( PIXELW, BITCOUNT )      (((( BITCOUNT * PIXELW ) + 31) / 32) * 4)     // 图像4Byte对齐

bool SaveToBmp(unsigned char *pData, int nWidth, int nHeight, int nBitCount, const char *pszFileName)
{
	if (pData == NULL || pszFileName == NULL)
	{
		return false;
	}

	if ((nBitCount != 8) && (nBitCount != 24) && (nBitCount != 32))
	{
		return false;
	}

	int    nColorTableSize = (nBitCount == 8 ? 256 * sizeof(RGBQUAD) : 0);
	int    nBmpInfoSize = sizeof(BITMAPINFOHEADER)+nColorTableSize;
	int    nWidthBytes = MAKEWIDTHBYTES(nWidth, nBitCount);
	int    nImageSize = nWidthBytes * nHeight;
	unsigned int nTotalSize = sizeof(BITMAPFILEHEADER)+nBmpInfoSize + nImageSize;

	FILE *pf = NULL;

	pf = fopen(pszFileName, "w+");

	if (NULL == pf)
	{
		//KSJLOG_OutputStringEx(hKSJLog, 1, "KSJERR_(KSJSCZ_HelperSaveToBmp create file %s failed)", pszFileName);
		return false;
	}

	BITMAPFILEHEADER *pBmpFileHeader = (BITMAPFILEHEADER*) new char[sizeof(BITMAPFILEHEADER)];
	if (pBmpFileHeader == NULL)
	{
		fclose(pf);
		//KSJLOG_OutputString(hKSJLog, "KSJERR_(KSJSCZ_HelperSaveToBmp allocate pBmpFileHeader failed!)", 1);
		return false;
	}

	pBmpFileHeader->bfType = 0x4d42; // "BM"
	pBmpFileHeader->bfSize = sizeof(BITMAPFILEHEADER)+nBmpInfoSize + nImageSize;
	pBmpFileHeader->bfReserved1 = 0;
	pBmpFileHeader->bfReserved2 = 0;
	pBmpFileHeader->bfOffBits = sizeof(BITMAPFILEHEADER)+nBmpInfoSize;

	BITMAPINFO *pBmpInfo = (BITMAPINFO*) new char[nBmpInfoSize];
	if (pBmpInfo == NULL)
	{
		delete[] pBmpFileHeader;
		fclose(pf);
		//KSJLOG_OutputString(hKSJLog, "KSJERR_(KSJSCZ_HelperSaveToBmp allocate pBmpInfo failed!)", 1);
		return false;
	}

	pBmpInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pBmpInfo->bmiHeader.biPlanes = 1;
	pBmpInfo->bmiHeader.biCompression = 0; //BI_RGB;
	pBmpInfo->bmiHeader.biSizeImage = 0;
	pBmpInfo->bmiHeader.biXPelsPerMeter = 0;
	pBmpInfo->bmiHeader.biYPelsPerMeter = 0;
	pBmpInfo->bmiHeader.biClrUsed = 0;
	pBmpInfo->bmiHeader.biClrImportant = 0;

	pBmpInfo->bmiHeader.biWidth = nWidth;
	pBmpInfo->bmiHeader.biHeight = -nHeight;      // top-down
	pBmpInfo->bmiHeader.biBitCount = nBitCount;
	pBmpInfo->bmiHeader.biSizeImage = nImageSize;

	if (nColorTableSize)
	{
		for (int i = 0; i<256; i++)
		{
			pBmpInfo->bmiColors[i].rgbBlue = (unsigned char)i;
			pBmpInfo->bmiColors[i].rgbGreen = (unsigned char)i;
			pBmpInfo->bmiColors[i].rgbRed = (unsigned char)i;
			pBmpInfo->bmiColors[i].rgbReserved = (unsigned char)i;
		}
	}

	unsigned int    dwNumberOfByteWritten;
	fwrite(pBmpFileHeader, 1, sizeof(BITMAPFILEHEADER), pf);
	fwrite(pBmpInfo, 1, nBmpInfoSize, pf);
	fwrite(pData, 1, nImageSize, pf);

	delete[] pBmpInfo;
	delete[] pBmpFileHeader;

	fflush(pf);
	fclose(pf);

	return true;
}

bool g_bHasSaveFirstImage = false;

VOID WINAPI PREVIEWCALLBACK0(unsigned char *pImageData, int nWidth, int nHeight, int nBitCount, void *lpContext)
{
	CKSJCamera *pCamera = (CKSJCamera *)lpContext;

	if (!g_bHasSaveFirstImage)
	{
		SaveToBmp(pImageData, nWidth, nHeight, nBitCount, "image.bmp");

		g_bHasSaveFirstImage = true;
	}

	if (pCamera->m_pIsPaused[0])
	{
		return;
	}
	if (pCamera->m_pIsTriggerMode[0])
	{
		return;
	}
	if (pCamera->m_pCapturedImageNum[0] < 1000)
	{
		pCamera->m_pCapturedImageNum[0]++;
	}
	else
	{
		pCamera->m_pCapturedImageNum[0] = 0;
	}
	if (pCamera->m_pImage[0].m_ImageWidth == 752)
	{
		if ((pCamera->m_pCapturedImageNum[0] % 2) != 0)
		{
			return;
		}
	}
	memcpy(pCamera->m_pImage[0].m_lpDibArray, pImageData, pCamera->m_pImage[0].m_ImageSize);

	int i = 0;
	for (i = 0; i<5; i++)
	{
		if (pCamera->m_ppConnectView[i][0] != NULL && pCamera->m_ppConnectView[i][0]->GetSafeHwnd() != NULL)
		{
			pCamera->m_ppConnectView[i][0]->Invalidate(FALSE);
		}
	}
}

VOID WINAPI PREVIEWCALLBACK1(unsigned char *pImageData, int nWidth, int nHeight, int nBitCount, void *lpContext)
{
	CKSJCamera *pCamera = (CKSJCamera *)lpContext;

	if (pCamera->m_pIsPaused[1])
	{
		return;
	}
	if (pCamera->m_pIsTriggerMode[1])
	{
		return;
	}
	if (pCamera->m_pCapturedImageNum[1] < 1000)
	{
		pCamera->m_pCapturedImageNum[1]++;
	}
	else
	{
		pCamera->m_pCapturedImageNum[1] = 0;
	}
	if (pCamera->m_pImage[1].m_ImageWidth == 752)
	{
		if ((pCamera->m_pCapturedImageNum[1] % 2) != 0)
		{
			return;
		}
	}
	memcpy(pCamera->m_pImage[1].m_lpDibArray, pImageData, pCamera->m_pImage[1].m_ImageSize);
	int i = 0;
	for (i = 0; i<5; i++)
	{
		if (pCamera->m_ppConnectView[i][1] != NULL && pCamera->m_ppConnectView[i][1]->GetSafeHwnd() != NULL)
		{
			pCamera->m_ppConnectView[i][1]->Invalidate(FALSE);
		}
	}

}

VOID WINAPI PREVIEWCALLBACK2(unsigned char *pImageData, int nWidth, int nHeight, int nBitCount, void *lpContext)
{
	CKSJCamera *pCamera = (CKSJCamera *)lpContext;
	if (pCamera->m_pIsPaused[2])
	{
		return;
	}
	if (pCamera->m_pIsTriggerMode[2])
	{
		return;
	}
	if (pCamera->m_pCapturedImageNum[2] < 1000)
	{
		pCamera->m_pCapturedImageNum[2]++;
	}
	else
	{
		pCamera->m_pCapturedImageNum[2] = 0;
	}
	if (pCamera->m_pImage[2].m_ImageWidth == 752)
	{
		if ((pCamera->m_pCapturedImageNum[2] % 2) != 0)
		{
			return;
		}
	}
	memcpy(pCamera->m_pImage[2].m_lpDibArray, pImageData, pCamera->m_pImage[2].m_ImageSize);


	int i = 0;
	for (i = 0; i<5; i++)
	{
		if (pCamera->m_ppConnectView[i][2] != NULL)
		{
			if (pCamera->m_ppConnectView[i][2]->GetSafeHwnd() != NULL)
			{
				pCamera->m_ppConnectView[i][2]->Invalidate(FALSE);
			}
		}
	}
}

VOID WINAPI PREVIEWCALLBACK3(unsigned char *pImageData, int nWidth, int nHeight, int nBitCount, void *lpContext)
{
	CKSJCamera *pCamera = (CKSJCamera *)lpContext;
	if (pCamera->m_pIsPaused[3])
	{
		return;
	}
	if (pCamera->m_pIsTriggerMode[3])
	{
		return;
	}
	if (pCamera->m_pCapturedImageNum[3] < 1000)
	{
		pCamera->m_pCapturedImageNum[3]++;
	}
	else
	{
		pCamera->m_pCapturedImageNum[3] = 0;
	}
	if (pCamera->m_pImage[3].m_ImageWidth == 752)
	{
		if ((pCamera->m_pCapturedImageNum[3] % 2) != 0)
		{
			return;
		}
	}
	memcpy(pCamera->m_pImage[3].m_lpDibArray, pImageData, pCamera->m_pImage[3].m_ImageSize);


	int i = 0;
	for (i = 0; i<5; i++)
	{
		if (pCamera->m_ppConnectView[i][3] != NULL && pCamera->m_ppConnectView[i][3]->GetSafeHwnd() != NULL)
		{
			pCamera->m_ppConnectView[i][3]->Invalidate(FALSE);
		}
	}
}

// VOID WINAPI PREVIEWCALLBACK4( unsigned char *pImageData, int nWidth, int nHeight, int nBitCount,  void *lpContext )
// {
// 	CKSJCamera *pCamera = (CKSJCamera *)lpContext;	
// 	if (pCamera->m_pIsPaused[4])
// 	{
// 		return;
// 	}
// 	memcpy(pCamera->m_pImage[4].m_lpDibArray, pImageData, pCamera->m_pImage[4].m_ImageSize);
// 	if (pCamera->m_pCapturedImageNum[4] < 1000)
// 	{
// 		pCamera->m_pCapturedImageNum[4]++;
// 	}
// 	for (int i=0;i<5; i++)
// 	{
// 		if (pCamera->m_ppConnectView[i][4] != NULL && pCamera->m_ppConnectView[i][4]->GetSafeHwnd() != NULL) 
// 		{
// 			pCamera->m_ppConnectView[i][4]->Invalidate(FALSE);
// 		}
// 	}
// }
CKSJCamera::CKSJCamera()
{
	m_nChooseIndex = 0;
	m_nDeviceNum = 0;
	m_bIsConnected = FALSE;
	memset(m_pCapturedImageNum, 0, MAX_DEVICE*sizeof(int));
	for (int i = 0; i < MAX_DEVICE; i++)
	{
		m_pIsPaused[i] = FALSE;
		m_pExposureTime[i] = 0;
		m_pDeviceInfo[i].nIndex = -1;
		m_pIsRGB[i] = FALSE;
		m_pIsTriggerMode[i] = FALSE;
		m_nBrightnes[i] = 0;
		m_nContrast[i] = 0;
		for (int j = 0; j<5; j++)
		{
			m_ppConnectView[j][i] = NULL;
		}
		FrameRate[i] = 15;
		WorkFalg[i] = FALSE;
		IsPREVIEW[i] = FALSE;
		IsStop[i] = TRUE;
		m_pCapturedImageNum[i] = 0;
	}

	ExTriggerCamIndex = 0;
	ExTriggerImgCount = 0;
}

CKSJCamera::~CKSJCamera()
{

	CloseCamera();
}

BOOL CKSJCamera::ConnectCamera()
{
	int nRet = KSJ_Init();
	// 获取连入主机的设备个数
	m_nDeviceNum = KSJ_DeviceGetCount();
	if (m_nDeviceNum == 0)
		return FALSE;
	if (m_nDeviceNum >= MAX_DEVICE)
		m_nDeviceNum = MAX_DEVICE;
	int i;
	// 获取每个设备信息（类型，序号，固件版本）
	for (i = 0; i < m_nDeviceNum; i++)
	{
		KSJ_DeviceGetInformation(i, &(m_pDeviceInfo[i].DeviceType), &(m_pDeviceInfo[i].nIndex), &(m_pDeviceInfo[i].wFirmwareVersion));

		BYTE btMajVersion = (m_pDeviceInfo[i].wFirmwareVersion & 0xFF00) >> 8;		// 得到主版本号
		BYTE btMinVersion = m_pDeviceInfo[i].wFirmwareVersion & 0x00FF;					// 得到副版本号
		switch (m_pDeviceInfo[i].DeviceType)
		{
		case KSJ_UC320C_MRNN:
			m_pIsRGB[i] = TRUE;
			break;
		case KSJ_UC500C_MRYY:
			m_pIsRGB[i] = TRUE;
			break;
		case KSJ_UC500C_MRNN:
			m_pIsRGB[i] = TRUE;
			break;
		}
		if (!SetExposureTime(i, m_pExposureTime[i]))
		{
			AfxMessageBox("相机设置错误! Code:Exposure");
			return FALSE;
		}
		//获得gain
		// 		int gain_g;
		// 		KSJ_GetParam(i, KSJ_GREEN, &gain_g);
		// 		KSJ_SetParam(i, KSJ_GREEN, 20);
		// 		KSJ_SetParam(i, KSJ_RED, 20);
		// 		KSJ_SetParam(i, KSJ_BLUE, 20);
		//设置Bayer模式为灰度
		if (m_pIsRGB[i])
			KSJ_BayerSetMode(i, KSJ_BGGR_GRAY8);
		//获得最大分辨率
		/*		KSJ_CaptureGetSize( i, &m_pDeviceInfo[i].m_nWidth, &m_pDeviceInfo[i].m_nHeight );*/
		int nColumnStart; int nRowStart; int nColumnSize; int nRowSize; KSJ_ADDRESSMODE ColumnAddressMode; KSJ_ADDRESSMODE RowAddressMode;
		KSJ_CaptureGetDefaultFieldOfView(i, &nColumnStart, &nColumnStart, &m_pDeviceInfo[i].m_nWidth, &m_pDeviceInfo[i].m_nHeight, &ColumnAddressMode, &RowAddressMode);
		{
			//设置采集分辨率
			KSJ_CaptureSetFieldOfView(i, 0, 0, m_pDeviceInfo[i].m_nWidth, m_pDeviceInfo[i].m_nHeight, KSJ_SKIPNONE, KSJ_SKIPNONE);
			KSJ_PreviewSetFieldOfView(i, 0, 0, m_pDeviceInfo[i].m_nWidth, m_pDeviceInfo[i].m_nHeight, KSJ_SKIPNONE, KSJ_SKIPNONE);

			//分配内存
			m_pImage[i].CreateEmpty(m_pDeviceInfo[i].m_nWidth, m_pDeviceInfo[i].m_nHeight, 8, 0);
		}

		switch (i)
		{
		case 0:
			KSJ_PreviewSetCallback(i, PREVIEWCALLBACK0, this);
			break;
		case 1:
			KSJ_PreviewSetCallback(i, PREVIEWCALLBACK1, this);
			break;
		case 2:
			KSJ_PreviewSetCallback(i, PREVIEWCALLBACK2, this);
			break;
		case 3:
			KSJ_PreviewSetCallback(i, PREVIEWCALLBACK3, this);
			break;
			// 		case 4:
			// 			KSJ_PreviewSetCallback( i, PREVIEWCALLBACK4, this );
			// 			break;
		default:
			AfxMessageBox("相机数量错误");
			break;
		}
	}
	for (i = 0; i < m_nDeviceNum; i++)
	{
		KSJ_PreviewSetPos(i, NULL, 0, 0, 0, 0);
		KSJ_PreviewStart(i, false);
		KSJ_CaptureSetTimeOut(i, 2000);
		KSJ_CaptureSetRecover(i, true);

		KSJ_TriggerModeSet(i, KSJ_TRIGGER_SOFTWARE);

		AfxMessageBox(_T("预览前，切换相机位置，看看采集图像是否正确！"));

		KSJ_PreviewStart(i, true);
	}
	m_bIsConnected = TRUE;
	return TRUE;
}
BOOL CKSJCamera::SetBrightnes(int nCamIndex, int nBrightnes)//设置相机亮度
{
#ifdef _DEBUG
	if (m_nDeviceNum == 0)
	{
		m_nBrightnes[nCamIndex] = nBrightnes;
		return TRUE;
	}
#endif
	if (nCamIndex < 0 || nCamIndex > m_nDeviceNum)
	{
		return FALSE;
	}
	if (m_nBrightnes[nCamIndex] == nBrightnes)
	{
		return TRUE;
	}
	int nRet = KSJ_ProcessBrightnessSet(nCamIndex, nBrightnes);
	if (nRet == RET_SUCCESS)
	{
		m_nBrightnes[nCamIndex] = nBrightnes;

	}
	return (nRet == RET_SUCCESS);
}
BOOL CKSJCamera::SetContrast(int nCamIndex, int nContrast)//设置相机对比度
{
#ifdef _DEBUG
	if (m_nDeviceNum == 0)
	{
		m_nContrast[nCamIndex] = nContrast;
		return TRUE;
	}
#endif
	if (nCamIndex < 0 || nCamIndex > m_nDeviceNum)
	{
		return FALSE;
	}
	if (m_nContrast[nCamIndex] == nContrast)
	{
		return TRUE;
	}
	int nRet = KSJ_ProcessContrastSet(nCamIndex, nContrast);
	if (nRet == RET_SUCCESS)
	{
		m_nContrast[nCamIndex] = nContrast;
	}
	return (nRet == RET_SUCCESS);
}
BOOL CKSJCamera::SetExposureTime(int nCamIndex, int nTime)
{
	/*#if _DEBUG*/
	if (m_nDeviceNum == 0)
	{
		m_pExposureTime[nCamIndex] = nTime;
		return TRUE;
	}
	/*#endif*/
	if (nCamIndex < 0 || nCamIndex >= m_nDeviceNum)
	{
		return FALSE;
	}
	if (m_pExposureTime[nCamIndex] == nTime)
	{
		return TRUE;
	}

	int ExposureMin, ExposureMax;
	KSJ_GetParamRange(nCamIndex, KSJ_EXPOSURE_LINES/*KSJ_EXPOSURE*/, &ExposureMin, &ExposureMax);
	if (nTime < ExposureMin)
	{
		nTime = ExposureMin;
	}
	if (nTime > ExposureMax)
	{
		nTime = ExposureMax;
	}
	int nRet = KSJ_SetParam(nCamIndex, KSJ_EXPOSURE_LINES/*KSJ_EXPOSURE*/, nTime);
	if (nRet == RET_SUCCESS)
	{
		m_pExposureTime[nCamIndex] = nTime;
	}
	return (nRet == RET_SUCCESS);
}
BOOL CKSJCamera::GetExposureTime(int nCamIndex, int *nTime)
{
#if _DEBUG
	if (m_nDeviceNum == 0)
	{
		*nTime = m_pExposureTime[nCamIndex];
		return TRUE;
	}
#endif
	if (nCamIndex < 0 || nCamIndex > m_nDeviceNum)
	{
		return FALSE;
	}
	int nRet = KSJ_GetParam(nCamIndex, KSJ_EXPOSURE_LINES/*KSJ_EXPOSURE*/, nTime);
	m_pExposureTime[nCamIndex] = *nTime;
	return TRUE;
}
BOOL CKSJCamera::CloseCamera()
{
	for (int i = 0; i < m_nDeviceNum; i++)
	{
		KSJ_PreviewStart(i, FALSE);
		KSJ_PreviewSetCallback(i, NULL, this);
	}
	int nRet = KSJ_UnInit();
	return (nRet == RET_SUCCESS);
}

BOOL CKSJCamera::PauseCamera(int nCamIndex, BOOL bIsWorking)
{
	if (nCamIndex < 0 || nCamIndex >= m_nDeviceNum)
	{
		return FALSE;
	}
	if (m_pIsPaused[nCamIndex] == !bIsWorking)
	{
		return TRUE;
	}
	int nRet = RET_SUCCESS;
	JudgeCameraIndex(nCamIndex);
	if (!bIsWorking)
	{
		//	nRet = KSJ_PreviewPause(nCamIndex, TRUE);
		KSJ_PREVIEWSTATUS m_Status;
		KSJ_PreviewGetStatus(nCamIndex, &m_Status);
		if (m_Status != PS_STOP)
		{
			KSJ_PreviewStart(nCamIndex, false);
		}
		for (int i = 0; i<5; i++)
		{
			if (m_ppConnectView[i][nCamIndex] != NULL && m_ppConnectView[i][nCamIndex]->GetSafeHwnd() != NULL)
			{
				m_ppConnectView[i][nCamIndex]->Invalidate(FALSE);
			}
		}
		m_pIsPaused[nCamIndex] = TRUE;
	}
	else
	{

		//	nRet = KSJ_PreviewPause(nCamIndex, FALSE);
		/*		m_pCapturedImageNum[nCamIndex] = 0;*/
		KSJ_PREVIEWSTATUS m_Status;
		KSJ_PreviewGetStatus(nCamIndex, &m_Status);
		if (m_Status != PS_START)
		{
			KSJ_PreviewStart(nCamIndex, true);
		}
		m_pIsPaused[nCamIndex] = FALSE;
	}
	/*	Sleep(100);*/
	return (nRet == RET_SUCCESS);
}

BOOL CKSJCamera::SetPreviewPos(int nCamIndex, HWND hWnd, CRect sRect)
{
	if (nCamIndex < 0 || nCamIndex > m_nDeviceNum)
	{
		return FALSE;
	}
	int nRet;
	double tmpscalex = sRect.Width() / (double)m_pDeviceInfo[nCamIndex].m_nWidth;
	double tmpscaley = sRect.Height() / (double)m_pDeviceInfo[nCamIndex].m_nHeight;
	if (tmpscalex<tmpscaley)
	{
		m_pShowScale[nCamIndex] = tmpscalex;
		sRect.bottom = sRect.top + int(m_pShowScale[nCamIndex] * m_pDeviceInfo[nCamIndex].m_nHeight + 0.5);
	}
	else
	{
		m_pShowScale[nCamIndex] = tmpscaley;
		sRect.right = sRect.left + int(m_pShowScale[nCamIndex] * m_pDeviceInfo[nCamIndex].m_nWidth + 0.5);
	}
	nRet = KSJ_PreviewSetPos(nCamIndex, hWnd, sRect.left, sRect.top, sRect.Width(), sRect.Height());
	return (nRet == RET_SUCCESS);
}

BOOL CKSJCamera::CaptureImage(int nCamIndex)
{
	if (nCamIndex < 0 || nCamIndex >= m_nDeviceNum)
	{
		return FALSE;
	}
	//	WaitForSingleObject(m_Event[nCamIndex],2000000000);

	KSJ_PREVIEWSTATUS m_Status;
	KSJ_PreviewGetStatus(nCamIndex, &m_Status);
	if (m_Status != PS_STOP)
	{
		KSJ_PreviewStart(nCamIndex, false);
	}

	int nRet = RET_SUCCESS;
	JudgeCameraIndex(nCamIndex);
	CTimeCount m_Times;
	m_Times.Start();
	if (m_pIsRGB[nCamIndex])
	{
		nRet = KSJ_CaptureRgbData(nCamIndex, m_pImage[nCamIndex].m_lpDibArray);
	}
	else
	{
		nRet = KSJ_CaptureRawData(nCamIndex, m_pImage[nCamIndex].m_lpDibArray);
	}
	m_Times.End();
	if (m_Times.GetUseTime()>2.1)
	{
		CString str;
		str.Format("错误 图片采集超时，相机序号%d", nCamIndex);
		AfxMessageBox(str);
		return FALSE;
	}
	for (int i = 0; i<5; i++)
	{
		if (m_ppConnectView[i][nCamIndex] != NULL && m_ppConnectView[i][nCamIndex]->GetSafeHwnd() != NULL)
		{
			m_ppConnectView[i][nCamIndex]->Invalidate(FALSE);
		}
	}

#ifdef RECORD_CAMARA_ERR
	if (nRet != RET_SUCCESS)
	{
		CString strInfo;
		CString strTime;
		CTime now_t = CTime::GetCurrentTime();
		strTime = now_t.Format("时间:%H:%M:%S");
		strInfo.Format("错误编号:%d  相机编号:%d,", nRet, nCamIndex);
		strInfo += strTime;
		strInfo += "\r\n";
		CStdioFile file(strLogPath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);
		file.SeekToEnd();//先定位到文件尾部
		file.WriteString(strInfo);
		file.Close();
	}
#endif

	return (nRet == RET_SUCCESS);
}
BOOL CKSJCamera::SetExternalTriggerMode(int nCamIndex)//设置外部触发模式
{
	if (nCamIndex < 0 || nCamIndex > m_nDeviceNum)
	{
		return FALSE;
	}

	JudgeCameraIndex(nCamIndex);
	int nRet = KSJ_TriggerModeSet(nCamIndex, KSJ_TRIGGER_EXTERNAL);
	nRet &= KSJ_TriggerMethodSet(nCamIndex, KSJ_TRIGGER_RISINGEDGE);
	ExTriggerCamIndex = nCamIndex;
	m_pIsTriggerMode[nCamIndex] = TRUE;
	/*	Sleep(100);*/
	return (nRet == RET_SUCCESS);
}
BOOL CKSJCamera::SetSoftTriggerMode(int nCamIndex)
{
	if (nCamIndex < 0 || nCamIndex >= m_nDeviceNum)
	{
		return FALSE;
	}
	if (m_pIsTriggerMode[nCamIndex] == TRUE)
	{
		return TRUE;
	}
	int nRet = RET_SUCCESS;
	/*
	nRet = KSJ_TriggerModeSet(nCamIndex, KSJ_TRIGGER_SOFTWARE);*/
	// 	nRet = KSJ_PreviewSetCallback(nCamIndex, NULL, NULL);
	// 	JudgeCameraIndex(nCamIndex);
	KSJ_PREVIEWSTATUS m_Status;
	KSJ_PreviewGetStatus(nCamIndex, &m_Status);
	if (m_Status != PS_STOP)
	{
		KSJ_PreviewStart(nCamIndex, false);
	}
	m_pIsTriggerMode[nCamIndex] = TRUE;

	return (nRet == RET_SUCCESS);
}

BOOL CKSJCamera::SetFreeMode(int nCamIndex)
{
	if (nCamIndex < 0 || nCamIndex >= m_nDeviceNum)
	{
		return FALSE;
	}

	// 	if (m_pIsTriggerMode[nCamIndex] == FALSE)
	// 	{
	// 		return FALSE;
	// 	}

	int nRet = RET_SUCCESS;
	/*
	nRet = KSJ_TriggerModeSet(nCamIndex, KSJ_TRIGGER_INTERNAL);*/
	// 	switch(nCamIndex)
	// 	{
	// 	case 0:
	// 		nRet &= KSJ_PreviewSetCallback( nCamIndex, PREVIEWCALLBACK0, this );
	// 		break;
	// 	case 1:
	// 		nRet &= KSJ_PreviewSetCallback( nCamIndex, PREVIEWCALLBACK1, this );
	// 		break;
	// 	case 2:
	// 		nRet &= KSJ_PreviewSetCallback( nCamIndex, PREVIEWCALLBACK2, this );
	// 		break;
	// 	case 3:
	// 		nRet &= KSJ_PreviewSetCallback( nCamIndex, PREVIEWCALLBACK3, this );
	// 		break;
	// // 	case 4:
	// // 		nRet &= KSJ_PreviewSetCallback( nCamIndex, PREVIEWCALLBACK4, this );
	// // 		break;
	// 	default:
	// 		AfxMessageBox("相机数量错误");
	// 		break;
	// 	}
	// 	nRet &= KSJ_PreviewStart(nCamIndex,true);
	KSJ_PREVIEWSTATUS m_Status;
	KSJ_PreviewGetStatus(nCamIndex, &m_Status);
	if (m_Status != PS_START)
	{
		KSJ_PreviewStart(nCamIndex, true);
	}
	m_pIsTriggerMode[nCamIndex] = FALSE;
	return (nRet == RET_SUCCESS);
}

void CKSJCamera::JudgeCameraIndex(int nCamIndex)
{
	// #if _DEBUG
	// 	return;
	// #endif
	// 	KSJ_DEVICETYPE DeviceType;
	// 	int nIndex;
	// 	unsigned short wFirmwareVersion;
	// 	KSJ_DeviceGetInformation( nCamIndex, &DeviceType, &nIndex, &wFirmwareVersion );
	// 	if (m_pDeviceInfo[nCamIndex].nIndex != nIndex)
	// 	{
	// 		CloseCamera();
	// 		ConnectCamera();
	// 	}
}