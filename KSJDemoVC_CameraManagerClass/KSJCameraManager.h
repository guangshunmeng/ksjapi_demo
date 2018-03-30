#pragma once

#define MAX_DEVICE 5

#define IGNORE_TIMES            1 //为减少数据传输影像，张图显示一次

// 几个功能相机的固定序号（serials）
#define USE1                    AOI_CAM_SERIALS
#define USE2                    CALL_CAM_SERIALS
#define USE3                    CALR_CAM_SERIALS
#define USESOMECAM

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

	int ConnectCamera(int nSerials);
	int PauseCamera(int nSerials);
	int CaptureImage(int nSerials);
	int ConnectView(int nSerials, CWnd *pWnd);

	int SetExposureTime(int nSerials, int nTime);

	// 其他函数类似添加。

protected:
	int           m_nCameraNum;
	DEVICEINFO    m_DeviceInfo[MAX_DEVICE];

	int           m_Serials2Index[MAX_DEVICE];     // 存放的是以Serials为索引的对应的nIndex。必须保证Serials小于MAX_DEVICE

	CKSJCamera    *m_pCameras[MAX_DEVICE];

	CWnd          *m_pConnectView[MAX_DEVICE];


};

