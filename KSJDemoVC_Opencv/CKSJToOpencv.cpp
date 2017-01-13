#include "stdafx.h"
#include "CKSJToOpencv.h"

void KSJDBG_OPENCVMAT(Mat cvImg)
{
	TCHAR szBuf[128] = { 0 };
	_stprintf_s(szBuf, 128, _T("一行含有的字节数:"), cvImg.step);
	OutputDebugString(szBuf);
	_stprintf_s(szBuf, 128, _T("一个像素所含有的字节:"), cvImg.elemSize());
	OutputDebugString(szBuf);
	_stprintf_s(szBuf, 128, _T("通道数:"), cvImg.channels());
	OutputDebugString(szBuf);
	_stprintf_s(szBuf, 128, _T("总像素个数:"), cvImg.total());
	OutputDebugString(szBuf);
	_stprintf_s(szBuf, 128, _T("Width:"), cvImg.size().width);
	OutputDebugString(szBuf);
	_stprintf_s(szBuf, 128, _T("Width:"), cvImg.cols);
	OutputDebugString(szBuf);
	_stprintf_s(szBuf, 128, _T("height:"), cvImg.rows);
	OutputDebugString(szBuf);
}

#define MAKEWIDTHBYTES( PIXELW, BITCOUNT )      (((( BITCOUNT * PIXELW ) + 31) / 32) * 4)//计算4对齐一行的字节数

// 注意opencv Mat中的内存图像数据与windows的图像数据上下颠倒
// ppcvImg需要由调用者释放
int ConvertKSJToOpencv3(unsigned char * pImageData, int nWidth, int nHeight, int nBitCount, Mat **ppcvImg)
{
	int nLineByte = MAKEWIDTHBYTES(nWidth, nBitCount);//计算4对齐一行的字节数

    Mat *pcvImage = NULL;

	if (nBitCount == 8) //根据位图深度初始化Mat，构造函数为浅拷贝，随pImageData变化
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

//ppImageData由调用者负责释放，返回时，ppImage数据已经4字节对齐
int ConvertOpnecv3ToKSJ(Mat cvImg, unsigned char ** ppImageData, int *pnWidth, int *pnHeight, int *pnBitCount )
{
    int nBitCount = cvImg.step[1]  << 3;    // 得到像素比特位数
    int nWidth    = cvImg.cols;             // opencv数据不是4字节对齐的
	int nHeight   = cvImg.rows;

	if (nBitCount != 8 && nBitCount != 24 && nBitCount != 32)
	{
		return -1;
	}
	
	int nLineByte   = MAKEWIDTHBYTES(nWidth, nBitCount);
    int nTotalBytes = nLineByte * nHeight;

	unsigned char * pImageData = new unsigned char[ nTotalBytes ];

	int nWidthByte = nWidth * cvImg.step[1];

	for (int i = 0; i < nHeight; i++)     //深拷贝，ppImageData不受cvImg影响
	{
		memcpy( pImageData + i * nLineByte, cvImg.data + ( nHeight - 1 - i ) * nWidthByte, nWidthByte );
	}

	if(ppImageData)    *ppImageData = pImageData;
    if(pnWidth)        *pnWidth     = nWidth;
    if(pnHeight)       *pnHeight    = nHeight;
    if(pnBitCount)     *pnBitCount  = nBitCount;

	return 0;
}