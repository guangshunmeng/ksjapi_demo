#ifndef _KSJCAMERA_H
#define _KSJCAMERA_H


class CKSJCamera
{
public:
	CKSJCamera(KSJ_DEVICETYPE DeviceType, int nIndex, int nSerials);
	~CKSJCamera();

	void PreviewCallback(HDC hDC, unsigned char *pImageData, int nWidth, int nHeight, int nBitCount, int nNo);

private:
	KSJ_DEVICETYPE m_DeviceType;
	int m_nIndex;
	int m_nSerials;

	BOOL     m_pIsRGB;
	int      m_nWidth;
	int      m_nHeight;
	int      m_nExposureTime;
	int      m_nExposureLines;
	int		 m_nGain;
	BOOL     m_bIsPaused;
	CWnd    *m_pConnectView;
	BOOL	 m_bIsConnected;
	BYTE     *m_pImageData;

public:
	int SetTriggerMode(KSJ_TRIGGERMODE TriggerMode);
	BOOL SetPreviewPos(int nCamIndex, HWND hWnd, CRect sRect);
	int ConnectView(CWnd* pConnectView);
	BOOL ConnectCamera(BOOL bStart);
	BOOL CaptureImage();
	BOOL PauseCamera(BOOL bIsWorking);
	int SetExposureTime(int nTime);
	int GetExposureTime(int* pnTime);
	int SetExposureLines(int nLines);
	int GetExposureLines(int* pnLines);
	int SetGain(int nGain);
	int GetGain(int* pnGain);
};

#endif