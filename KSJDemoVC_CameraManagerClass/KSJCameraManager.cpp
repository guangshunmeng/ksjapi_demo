#include "stdafx.h"
#include "KSJCameraManager.h"
#include "KSJCamera.h"


CKSJCameraManager::CKSJCameraManager()
{
	memset(m_DeviceInfo, -1, sizeof(DEVICEINFO) * MAX_DEVICE);
	memset(m_Serials2Index, -1, sizeof(int)* MAX_DEVICE);
	memset(m_pCameras, NULL, MAX_DEVICE * sizeof(CKSJCamera*));

	memset(m_pConnectView, NULL, sizeof(CWnd*) * MAX_DEVICE);

	KSJ_Init();

	m_nCameraNum = KSJ_DeviceGetCount();

	for (int i = 0; i < m_nCameraNum; i++)
	{
		if (i >= MAX_DEVICE)
			break;

		if (RET_SUCCESS != KSJ_DeviceGetInformation(i, &(m_DeviceInfo[i].DeviceType), &(m_DeviceInfo[i].nSerials), &(m_DeviceInfo[i].wFirmwareVersion)))
		{
			// This Camera Maybe Opened by other process.
			continue;
		}

		if (m_DeviceInfo[i].nSerials >= MAX_DEVICE)
		{
			// 忽略所有不合法的Serials的相机。
			KSJ_DeviceClose(i);
			continue;
		}

		if (m_DeviceInfo[i].nSerials == AOI_NOT_USE)    // 这里把不需要在此进程中使用的相机关闭。
		{
			KSJ_DeviceClose(i);
			m_DeviceInfo[i].nSerials = -1;
			continue;
		}

		if (m_Serials2Index[m_DeviceInfo[i].nSerials] != -1)     // 对于重复的nSerials相机，选择关闭
		{
			KSJ_DeviceClose(i);
			continue;
		}

		m_Serials2Index[m_DeviceInfo[i].nSerials] = i;            // 添加到Serials为索引的nIndex映射表中

		// 这里创建本进程要打开的所有相机
		if (m_pCameras[m_DeviceInfo[i].nSerials] == NULL)
			m_pCameras[m_DeviceInfo[i].nSerials] = new CKSJCamera(m_DeviceInfo[i].DeviceType, i, m_DeviceInfo[i].nSerials);

	}


}


CKSJCameraManager::~CKSJCameraManager()
{
	for (int i = 0; i < MAX_DEVICE; i++)
	{
		if (m_pCameras[m_DeviceInfo[i].nSerials] != NULL)
		{
			delete m_pCameras[m_DeviceInfo[i].nSerials];
			m_pCameras[m_DeviceInfo[i].nSerials] = NULL;
		}
	}

	KSJ_UnInit();
}


int CKSJCameraManager::ConnectCamera(int nSerials)
{
	if (m_pCameras[nSerials] != NULL)
	{
		return m_pCameras[nSerials]->ConnectCamera();
	}

	return RET_FAIL;    // 相机被别的进程打开了或者没有此相机。
}

int CKSJCameraManager::CaptureImage(int nSerials)
{
	if (m_pCameras[nSerials] != NULL)
	{
		return m_pCameras[nSerials]->CaptureImage();
	}

	return RET_FAIL;
}


int CKSJCameraManager::SetExposureTime(int nSerials, int nTime)
{
	if (m_pCameras[nSerials] != NULL)
	{
		return m_pCameras[nSerials]->SetExposureTime(nTime);
	}

	return RET_FAIL;
}



int CKSJCameraManager::ConnectView(int nSerials, CWnd *pWnd)
{
	if (m_pCameras[nSerials] != NULL)
	{
		return m_pCameras[nSerials]->ConnectView(pWnd);
	}
	return RET_FAIL;

}

int CKSJCameraManager::PauseCamera(int nSerials)
{
	if (m_pCameras[nSerials] != NULL)
	{
		return m_pCameras[nSerials]->PauseCamera();
	}

	return RET_FAIL;
}

