#include "stdafx.h"
#include "CKSJToOpencv.h"

void KSJDBG_OPENCVMAT(Mat cvImg)
{
	TCHAR szBuf[128] = { 0 };
	_stprintf_s(szBuf, 128, _T("һ�к��е��ֽ���:"), cvImg.step);
	OutputDebugString(szBuf);
	_stprintf_s(szBuf, 128, _T("һ�����������е��ֽ�:"), cvImg.elemSize());
	OutputDebugString(szBuf);
	_stprintf_s(szBuf, 128, _T("ͨ����:"), cvImg.channels());
	OutputDebugString(szBuf);
	_stprintf_s(szBuf, 128, _T("�����ظ���:"), cvImg.total());
	OutputDebugString(szBuf);
	_stprintf_s(szBuf, 128, _T("Width:"), cvImg.size().width);
	OutputDebugString(szBuf);
	_stprintf_s(szBuf, 128, _T("Width:"), cvImg.cols);
	OutputDebugString(szBuf);
	_stprintf_s(szBuf, 128, _T("height:"), cvImg.rows);
	OutputDebugString(szBuf);
}

#define MAKEWIDTHBYTES( PIXELW, BITCOUNT )      (((( BITCOUNT * PIXELW ) + 31) / 32) * 4)//����4����һ�е��ֽ���

// ע��opencv Mat�е��ڴ�ͼ��������windows��ͼ���������µߵ�
// ppcvImg��Ҫ�ɵ������ͷ�
int ConvertKSJToOpencv3(unsigned char * pImageData, int nWidth, int nHeight, int nBitCount, Mat **ppcvImg)
{
	int nLineByte = MAKEWIDTHBYTES(nWidth, nBitCount);//����4����һ�е��ֽ���

    Mat *pcvImage = NULL;

	if (nBitCount == 8) //����λͼ��ȳ�ʼ��Mat�����캯��Ϊǳ��������pImageData�仯
	{
		pcvImage = new Mat(nHeight, nWidth, CV_8UC1, pImageData, nLineByte);
	}

	else if (nBitCount == 24)
	{
		pcvImage = new Mat(nHeight, nWidth, CV_8UC3, pImageData, nLineByte);
	}

	else if (nBitCount == 32)
	{
		pcvImage = new Mat(nHeight, nWidth, CV_8UC4, pImageData, nLineByte);
	}

	else
	{
		return -1;
	}

	*pcvImage = pcvImage->clone();  // 

	flip(*pcvImage, *pcvImage, 0);

	if (ppcvImg)    *ppcvImg = pcvImage;

	return 0;
}

//ppImageData�ɵ����߸����ͷţ�����ʱ��ppImage�����Ѿ�4�ֽڶ���
int ConvertOpnecv3ToKSJ(Mat cvImg, unsigned char ** ppImageData, int *pnWidth, int *pnHeight, int *pnBitCount )
{
    int nBitCount = cvImg.step[1]  << 3;    // �õ����ر���λ��
    int nWidth    = cvImg.cols;             // opencv���ݲ���4�ֽڶ����
	int nHeight   = cvImg.rows;

	if (nBitCount != 8 && nBitCount != 24 && nBitCount != 32)
	{
		return -1;
	}
	
	int nLineByte   = MAKEWIDTHBYTES(nWidth, nBitCount);
    int nTotalBytes = nLineByte * nHeight;

	unsigned char * pImageData = new unsigned char[ nTotalBytes ];

	int nWidthByte = nWidth * cvImg.step[1];

	for (int i = 0; i < nHeight; i++)     //�����ppImageData����cvImgӰ��
	{
		memcpy( pImageData + i * nLineByte, cvImg.data + ( nHeight - 1 - i ) * nWidthByte, nWidthByte );
	}

	if(ppImageData)    *ppImageData = pImageData;
    if(pnWidth)        *pnWidth     = nWidth;
    if(pnHeight)       *pnHeight    = nHeight;
    if(pnBitCount)     *pnBitCount  = nBitCount;

	return 0;
}