#pragma once

#define MAX_DEVICE 5

#define IGNORE_TIMES            1 //Ϊ�������ݴ���Ӱ����ͼ��ʾһ��

// ������������Ĺ̶���ţ�serials��
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

// ���÷��� CKSJCameraManager *pCameraManager = new CKSJCameraManager;
// nRet = pCameraManager->ConnectCamera(CALL_CAM_SERIALS);    // �жϷ���ֵ������

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

	// ��������������ӡ�

protected:
	int           m_nCameraNum;
	DEVICEINFO    m_DeviceInfo[MAX_DEVICE];

	int           m_Serials2Index[MAX_DEVICE];     // ��ŵ�����SerialsΪ�����Ķ�Ӧ��nIndex�����뱣֤SerialsС��MAX_DEVICE

	CKSJCamera    *m_pCameras[MAX_DEVICE];

	CWnd          *m_pConnectView[MAX_DEVICE];


};

