#ifndef _KSJCAMERA_H
#define _KSJCAMERA_H

#include "KSJApiBase.h"
#include "KSJApiCallback.h"
#include "KSJApiMultiProcess.h"
#include "KSJApiTriggerMode.h"
#include "KSJApiBayer.h"
#include "KSJCode.h"
#include "Image.h"



class CKSJCamera
{
public:
	CKSJCamera(KSJ_DEVICETYPE DeviceType, int nIndex, int nSerials);
	~CKSJCamera();

	void PreviewCallback(unsigned char *pImageData, int nWidth, int nHeight, int nBitCount);


	BOOL ConnectCamera();
	BOOL SetExposureTime(int nTime);
	BOOL CaptureImage();
	BOOL PauseCamera(BOOL bIsWorking);

private:
	KSJ_DEVICETYPE m_DeviceType;
	int m_nIndex;
	int m_nSerials;

	BOOL     m_pIsRGB;
	CMyImage m_pImage;
	int      m_nWidth;
	int      m_nHeight;
	int      m_nExposureTime;
	int      m_nCapturedImageNum;
	BOOL     m_bIsPaused;
	CWnd    *m_pConnectView;
	BOOL m_bIsConnected;


public:
	BOOL SetFreeMode();
	BOOL SetSoftTriggerMode();
	BOOL m_pIsTriggerMode;
	double m_pShowScale;
	BOOL SetPreviewPos(HWND hWnd, CRect sRect);


};

#endif