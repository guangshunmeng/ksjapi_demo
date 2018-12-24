#ifndef _KSJCAMERA_H
#define _KSJCAMERA_H


#include <WinDef.h>
#include "../KSJApi.Inc/KSJApi.h"

#define MAX_DEVICE 4

struct DEVICEINFO
{
	KSJ_DEVICETYPE		DeviceType;
	int					nIndex;
	WORD				wFirmwareVersion;
	int					m_nStartCol;
	int					m_nStartRow;
	int					m_nWidth;
	int					m_nHeight;
	DEVICEINFO()
	{
		DeviceType = KSJ_UC130C_MRNN;
		nIndex  = -1;
		wFirmwareVersion = 0;
		m_nStartCol = 0;
		m_nStartRow = 0;
		m_nWidth = 0;
		m_nHeight = 0;
	}
};

class CMyImage
{
public:
	CMyImage() { m_lpDibArray = NULL; m_ImageWidth = 0; m_ImageHeight = 0; m_ImageBitCount = 0; m_ImageSize = 0; }
	virtual ~CMyImage() { if (m_lpDibArray != NULL) { delete[] m_lpDibArray; m_lpDibArray = NULL; } }

public:
	unsigned int m_ImageWidth;
	unsigned int m_ImageHeight;
	unsigned int m_ImageBitCount;
	unsigned int m_ImageSize;
	unsigned char* m_lpDibArray;

public:
	bool CreateEmpty(unsigned int width, unsigned int height, unsigned int bitcount, unsigned char initv)
	{
		if (width % 4 != 0) return false;

		if (m_lpDibArray != NULL)
		{
			delete[] m_lpDibArray;
			m_lpDibArray = NULL;
		}

		m_ImageWidth = width;
		m_ImageHeight = height;
		m_ImageBitCount = bitcount;
		m_ImageSize = m_ImageWidth*m_ImageHeight*m_ImageBitCount / 8;

		m_lpDibArray = new unsigned char[m_ImageSize];

		memset(m_lpDibArray, initv, m_ImageSize);

		return true;
	}
};

class CTimeCount
{
public:
	CTimeCount(){ m_dStart = 0; m_dEnd = 0; }
	virtual ~CTimeCount(){ ; }

public:
	double m_dStart;
	double m_dEnd;

public:
	void Start()
	{
		LARGE_INTEGER lifrqc, litmp;
		QueryPerformanceFrequency(&lifrqc);
		QueryPerformanceCounter(&litmp);
		m_dStart = litmp.QuadPart * 1000. / lifrqc.QuadPart;
	}

	void End()
	{
		LARGE_INTEGER lifrqc, litmp;
		QueryPerformanceFrequency(&lifrqc);
		QueryPerformanceCounter(&litmp);
		m_dEnd = litmp.QuadPart * 1000. / lifrqc.QuadPart;
	}

	double GetUseTime() { return m_dEnd - m_dStart; }
};

class CKSJCamera
{
public:
	
	double FrameRate[MAX_DEVICE];
	BOOL WorkFalg[MAX_DEVICE];
	BOOL IsPREVIEW[MAX_DEVICE];
	BOOL IsStop[MAX_DEVICE];

	int m_nChooseIndex;//0:螺丝定位相机 1:晶片定位相机  (螺丝定位相机ID为1，晶片定位相机ID为2)
	void JudgeCameraIndex(int nCamIndex);
	BOOL SetFreeMode(int nCamIndex);
	BOOL SetSoftTriggerMode(int nCamIndex);

	BOOL SetExternalTriggerMode(int nCamIndex);//设置外部触发模式
	int  ExTriggerCamIndex;
	int ExTriggerImgCount;

	BOOL CaptureImage(int nCamIndex);
	BOOL m_pIsRGB[MAX_DEVICE];
	BOOL m_pIsPaused[MAX_DEVICE];
	BOOL m_pIsTriggerMode[MAX_DEVICE];
	int m_pCapturedImageNum[MAX_DEVICE];
	int m_nBrightnes[MAX_DEVICE];
	int m_nContrast[MAX_DEVICE];
	BOOL m_bIsConnected;
/*	CWnd  *m_pConnectView[MAX_DEVICE];*/
	CWnd  *m_ppConnectView[5][MAX_DEVICE];
	BOOL SetPreviewPos(int nCamIndex, HWND hWnd, CRect sRect);

	BOOL PauseCamera(int nCamIndex, BOOL bIsWorking);
	BOOL CloseCamera();

	BOOL SetBrightnes(int nCamIndex, int nBrightnes);//设置相机亮度

	BOOL SetContrast(int nCamIndex, int nContrast);//设置相机对比度

	BOOL SetExposureTime(int nCamIndex, int nTime);
	BOOL GetExposureTime(int nCamIndex, int *nTime);
	int    m_pExposureTime[MAX_DEVICE];
	CMyImage m_pImage[MAX_DEVICE];
	double m_pShowScale[MAX_DEVICE];
	int m_nDeviceNum;
	DEVICEINFO    m_pDeviceInfo[MAX_DEVICE];
	BOOL ConnectCamera();
	CKSJCamera();
	~CKSJCamera();
};

#endif