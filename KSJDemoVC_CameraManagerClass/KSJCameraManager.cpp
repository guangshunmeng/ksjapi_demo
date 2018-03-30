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
			// �������в��Ϸ���Serials�������
			KSJ_DeviceClose(i);
			continue;
		}

		if (m_DeviceInfo[i].nSerials == AOI_NOT_USE)    // ����Ѳ���Ҫ�ڴ˽�����ʹ�õ�����رա�
		{
			KSJ_DeviceClose(i);
			m_DeviceInfo[i].nSerials = -1;
			continue;
		}

		if (m_Serials2Index[m_DeviceInfo[i].nSerials] != -1)     // �����ظ���nSerials�����ѡ��ر�
		{
			KSJ_DeviceClose(i);
			continue;
		}

		m_Serials2Index[m_DeviceInfo[i].nSerials] = i;            // ��ӵ�SerialsΪ������nIndexӳ�����

		// ���ﴴ��������Ҫ�򿪵��������
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

	return RET_FAIL;    // �������Ľ��̴��˻���û�д������
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

