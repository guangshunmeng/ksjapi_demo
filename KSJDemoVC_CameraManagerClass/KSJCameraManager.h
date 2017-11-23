#pragma once
#include "KSJCamera.h"
#define MAX_DEVICE 5

#define IGNORE_TIMES            1 //为减少数据传输影像，张图显示一次

// 几个功能相机的固定序号（serials）
#define USE1                    1
#define USE2                    2
#define USE3                    3

struct DEVICEINFO
{
	KSJ_DEVICETYPE		DeviceType;
	int					nSerials;
	WORD				wFirmwareVersion;
	int					m_nStartCol;
	int					m_nStartRow;
	int					m_nWidth;
	int					m_nHeight;
};

class KSJCamera;

// 调用方法 CKSJCameraManager *pCameraManager = new CKSJCameraManager;
// nRet = pCameraManager->ConnectCamera(CALL_CAM_SERIALS);    // 判断返回值！！！

class CKSJCameraManager
{
public:
	CKSJCameraManager();
	~CKSJCameraManager();

	int ConnectCamera(int nSerials, BOOL bStart);
	int PauseCamera(int nSerials, BOOL bPause);
	int CaptureImage(int nSerials);
	int ConnectView(int nSerials, CWnd *pWnd);

	int SetTriggerMode(int nSerials, KSJ_TRIGGERMODE TriggerMode);
	int SetExposureTime(int nSerials, int nTime);
	int GetExposureTime(int nSerials, int* pnTime);
	int SetExposureLines(int nSerials, int nLines);
	int GetExposureLines(int nSerials, int* pnLines);
	int SetGain(int nSerials, int nGain);
	int GetGain(int nSerials, int* pnGain);

	// 其他函数类似添加。

protected:
	int           m_nCameraNum;
	DEVICEINFO    m_DeviceInfo[MAX_DEVICE];

	int           m_Serials2Index[MAX_DEVICE];     // 存放的是以Serials为索引的对应的nIndex。必须保证Serials小于MAX_DEVICE

	CKSJCamera    *m_pCameras[MAX_DEVICE];

	CWnd          *m_pConnectView[MAX_DEVICE];


public:
	int GetCameraInfo(int nSerials, DEVICEINFO* pDeviceInfo);
	int GetCameraCount();
};

