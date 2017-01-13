#include "CKSJToHalcon.h"

#define MAKEWIDTHBYTES( PIXELW, BITCOUNT )      (((( BITCOUNT * PIXELW ) + 31) / 32) * 4)//计算4对齐一行的字节数

#ifdef HALCON11

// 将采集的数据转换为HALCON11的数据类型HObject,注意：pImageData需要4字节对齐。
int ConvertKSJToHalcon11(unsigned char * pImageData, int nWidth, int nHeight, int nBitCount, HObject *Halcon_Image)
{
	HObject  Halcon_Image_Convert;

	int nLineByte    = MAKEWIDTHBYTES(nWidth, nBitCount);
	int nPixelBytes  = nBitCount >> 3;     // 每个像素所占字节数
        

	if (nBitCount == 8)//根据位图深度调用相应接口
	{
		gen_image1(&Halcon_Image_Convert, "byte", nLineByte, nHeight, (long)pImageData); // 深拷贝
	}
	else if (nBitCount == 24 || nBitCount == 32)
	{
                int nChannelBytes = nWidth * nHeight;    // 每个通道的字节数

		unsigned char  *pImage_r = new unsigned char[nChannelBytes];    // 此内存不需要4字节对齐
		unsigned char  *pImage_g = new unsigned char[nChannelBytes];
		unsigned char  *pImage_b = new unsigned char[nChannelBytes];

		for (int i = 0; i < nHeight; i++)      //将像素中的红、绿、蓝分开保存
		{
			int nOffsetOnChannel = i * nWidth;
			int nOffsetOnImage   = i * nLineByte;
                        int nPixelOffset = 0;

			for (int j = 0; j < nWidth; j++)
			{
				pImage_r[nOffsetOnChannel + j] = pImageData[nOffsetOnImage + nPixelOffset];
				pImage_g[nOffsetOnChannel + j] = pImageData[nOffsetOnImage + nPixelOffset + 1];
				pImage_b[nOffsetOnChannel + j] = pImageData[nOffsetOnImage + nPixelOffset + 2];

                                nPixelOffset += nPixelBytes;
			}
		}

		gen_image3(&Halcon_Image_Convert, "byte", nWidth, nHeight, (long)pImage_r, (long)pImage_g, (long)pImage_b);   //深拷贝

		delete[]pImage_r;
		delete[]pImage_g;
		delete[]pImage_b;
	}
	else
	{
		return -1;
	}

	mirror_image(Halcon_Image_Convert, &Halcon_Image_Convert, "row");  // 上下反转图片

	if( Halcon_Image )    *Halcon_Image = Halcon_Image_Convert;

	return 0;
}

int ConvertHalcon11ToKSJ(HObject Image, unsigned char ** ppImageData, int *pnWidth, int *pnHeight, int *pnBitCount)//ppImageData在接口调用后需要释放
{
	mirror_image(Image, &Image, "row");//上下反转图片

	unsigned char * pImageData = NULL;
    int       nWidth, nHeight, nBitCount;

	HTuple     Hchannels;
	count_channels(Image, &Hchannels);
	int nChannels = Hchannels[0].I();    // 得到图像的通道数 1， 3， 4

    nBitCount = nChannels << 3;

	HTuple     Htype,Hwidth, Hheight;


	if (nChannels == 1)//根据位图深度调用相应接口
	{
		HTuple hpoint;
		get_image_pointer1(Image, &hpoint, &Htype, &Hwidth, &Hheight);

		unsigned char *  ptr = (unsigned char *)hpoint[0].L();     // halcon数据对象的图像指针

                nWidth      = Hwidth[0].I();                           // 图像宽度（像素）
                nHeight     = Hheight[0].I();

		int nLineByte   = MAKEWIDTHBYTES(nWidth, nBitCount );
                int nTotalBytes = nLineByte * nHeight;

		pImageData = new unsigned char[nTotalBytes];

		for (int i = 0; i < nHeight; i++)//深拷贝
		{
			memcpy(pImageData + i * nLineByte, ptr + i * nWidth, nWidth);
		}

	}

	else if (nChannels == 3 || nChannels == 4)
	{
		HTuple Hr,Hg,Hb;

		get_image_pointer3(Image, &Hr, &Hg, &Hb, &Htype, &Hwidth, &Hheight);
		unsigned char *  ptr_r = (unsigned char *)Hr[0].L();
		unsigned char *  ptr_g = (unsigned char *)Hg[0].L();
		unsigned char *  ptr_b = (unsigned char *)Hb[0].L();

                nWidth      = Hwidth[0].I();                           // 图像宽度（像素）
                nHeight     = Hheight[0].I();

		int nLineByte = MAKEWIDTHBYTES( nWidth, nBitCount );
                int nTotalBytes = nLineByte * nHeight;

		pImageData = new unsigned char[nTotalBytes];

		for (int i = 0; i < Hheight[0].I(); i++)//将红、绿、蓝保存到像素中
		{
			int nOffsetOnChannel     = i * nWidth;
			int nOffsetOnImage       = i * nLineByte;
                        int nPixelOffset         = 0;

			for (int j = 0; j < nHeight; j++)//深拷贝
			{
				pImageData[nOffsetOnImage + nPixelOffset]     = ptr_r[nOffsetOnChannel + j];
				pImageData[nOffsetOnImage + nPixelOffset + 1] = ptr_g[nOffsetOnChannel + j];
				pImageData[nOffsetOnImage + nPixelOffset + 2] = ptr_b[nOffsetOnChannel + j];

                                nPixelOffset += nChannels;
			}
		}
	}
	else
	{
		return -1;
	}


	if(ppImageData)    *ppImageData = pImageData;
        if(pnWidth)        *pnWidth     = nWidth;
        if(pnHeight)       *pnHeight    = nHeight;
        if(pnBitCount)     *pnBitCount  = nBitCount;
    

	return 0;
}

#else
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ConvertKSJToHalcon10(unsigned char * pImageData, int nWidth, int nHeight, int nBitCount, Hobject *Halcon_Image)
{
	Hobject  Halcon_Image_Convert;

	int nLineByte    = MAKEWIDTHBYTES(nWidth, nBitCount);
	int nPixelBytes  = nBitCount >> 3;     // 每个像素所占字节数
        

	if (nBitCount == 8)//根据位图深度调用相应接口
	{
		gen_image1(&Halcon_Image_Convert, "byte", nLineByte, nHeight, (long)pImageData); // 深拷贝
	}
	else if (nBitCount == 24 || nBitCount == 32)
	{
                int nChannelBytes = nWidth * nHeight;    // 每个通道的字节数

		unsigned char  *pImage_r = new unsigned char[nChannelBytes];    // 此内存不需要4字节对齐
		unsigned char  *pImage_g = new unsigned char[nChannelBytes];
		unsigned char  *pImage_b = new unsigned char[nChannelBytes];

		for (int i = 0; i < nHeight; i++)      //将像素中的红、绿、蓝分开保存
		{
			int nOffsetOnChannel = i * nWidth;
			int nOffsetOnImage   = i * nLineByte;
                        int nPixelOffset = 0;

			for (int j = 0; j < nWidth; j++)
			{
				pImage_r[nOffsetOnChannel + j] = pImageData[nOffsetOnImage + nPixelOffset];
				pImage_g[nOffsetOnChannel + j] = pImageData[nOffsetOnImage + nPixelOffset + 1];
				pImage_b[nOffsetOnChannel + j] = pImageData[nOffsetOnImage + nPixelOffset + 2];

                                nPixelOffset += nPixelBytes;
			}
		}

		gen_image3(&Halcon_Image_Convert, "byte", nWidth, nHeight, (long)pImage_r, (long)pImage_g, (long)pImage_b);   //深拷贝

		delete[]pImage_r;
		delete[]pImage_g;
		delete[]pImage_b;
	}
	else
	{
		return -1;
	}

	mirror_image(Halcon_Image_Convert, &Halcon_Image_Convert, "row");  // 上下反转图片

	if( Halcon_Image )    *Halcon_Image = Halcon_Image_Convert;

	return 0;
}

int ConvertHalcon10ToKSJ(Hobject Image, unsigned char ** ppImageData, int *pnWidth, int *pnHeight, int *pnBitCount)
{
	mirror_image(Image, &Image, "row");//上下反转图片

	unsigned char * pImageData = NULL;
        int       nWidth, nHeight, nBitCount;

	HTuple     Hchannels;
	count_channels(Image, &Hchannels);
	int nChannels = Hchannels[0].I();    // 得到图像的通道数 1， 3， 4

        nBitCount = nChannels << 3;

	HTuple     Htype,Hwidth, Hheight;


	if (nChannels == 1)//根据位图深度调用相应接口
	{
		HTuple hpoint;
		get_image_pointer1(Image, &hpoint, &Htype, &Hwidth, &Hheight);

		unsigned char *  ptr = (unsigned char *)hpoint[0].L();     // halcon数据对象的图像指针

                nWidth      = Hwidth[0].I();                              // 图像宽度（像素）
                nHeight     = Hheight[0].I();

		int nLineByte   = MAKEWIDTHBYTES(nWidth, nBitCount );
                int nTotalBytes = nLineByte * nHeight;

		pImageData = new unsigned char[nTotalBytes];

		for (int i = 0; i < nHeight; i++)//深拷贝
		{
			memcpy(pImageData + i * nLineByte, ptr + i * nWidth, nWidth);
		}

	}

	else if (nChannels == 3 || nChannels == 4)
	{
		HTuple Hr,Hg,Hb;

		get_image_pointer3(Image, &Hr, &Hg, &Hb, &Htype, &Hwidth, &Hheight);
		unsigned char *  ptr_r = (unsigned char *)Hr[0].L();
		unsigned char *  ptr_g = (unsigned char *)Hg[0].L();
		unsigned char *  ptr_b = (unsigned char *)Hb[0].L();

                nWidth      = Hwidth[0].I();                           // 图像宽度（像素）
                nHeight     = Hheight[0].I();

		int nLineByte = MAKEWIDTHBYTES( nWidth, nBitCount );
                int nTotalBytes = nLineByte * nHeight;

		pImageData = new unsigned char[nTotalBytes];

		for (int i = 0; i < Hheight[0].I(); i++)//将红、绿、蓝保存到像素中
		{
			int nOffsetOnChannel     = i * nWidth;
			int nOffsetOnImage       = i * nLineByte;
                        int nPixelOffset         = 0;

			for (int j = 0; j < nHeight; j++)//深拷贝
			{
				pImageData[nOffsetOnImage + nPixelOffset]     = ptr_r[nOffsetOnChannel + j];
				pImageData[nOffsetOnImage + nPixelOffset + 1] = ptr_g[nOffsetOnChannel + j];
				pImageData[nOffsetOnImage + nPixelOffset + 2] = ptr_b[nOffsetOnChannel + j];

                                nPixelOffset += nChannels;
			}
		}
	}
	else
	{
		return -1;
	}

	if(ppImageData)    *ppImageData = pImageData;
        if(pnWidth)        *pnWidth     = nWidth;
        if(pnHeight)       *pnHeight    = nHeight;
        if(pnBitCount)     *pnBitCount  = nBitCount;

	return 0;
}
#endif