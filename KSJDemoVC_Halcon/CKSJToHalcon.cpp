#include "CKSJToHalcon.h"

#define MAKEWIDTHBYTES( PIXELW, BITCOUNT )      (((( BITCOUNT * PIXELW ) + 31) / 32) * 4)//����4����һ�е��ֽ���

#ifdef HALCON11

// ���ɼ�������ת��ΪHALCON11����������HObject,ע�⣺pImageData��Ҫ4�ֽڶ��롣
int ConvertKSJToHalcon11(unsigned char * pImageData, int nWidth, int nHeight, int nBitCount, HObject *Halcon_Image)
{
	HObject  Halcon_Image_Convert;

	int nLineByte    = MAKEWIDTHBYTES(nWidth, nBitCount);
	int nPixelBytes  = nBitCount >> 3;     // ÿ��������ռ�ֽ���
        

	if (nBitCount == 8)//����λͼ��ȵ�����Ӧ�ӿ�
	{
		gen_image1(&Halcon_Image_Convert, "byte", nLineByte, nHeight, (long)pImageData); // ���
	}
	else if (nBitCount == 24 || nBitCount == 32)
	{
                int nChannelBytes = nWidth * nHeight;    // ÿ��ͨ�����ֽ���

		unsigned char  *pImage_r = new unsigned char[nChannelBytes];    // ���ڴ治��Ҫ4�ֽڶ���
		unsigned char  *pImage_g = new unsigned char[nChannelBytes];
		unsigned char  *pImage_b = new unsigned char[nChannelBytes];

		for (int i = 0; i < nHeight; i++)      //�������еĺ졢�̡����ֿ�����
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

		gen_image3(&Halcon_Image_Convert, "byte", nWidth, nHeight, (long)pImage_r, (long)pImage_g, (long)pImage_b);   //���

		delete[]pImage_r;
		delete[]pImage_g;
		delete[]pImage_b;
	}
	else
	{
		return -1;
	}

	mirror_image(Halcon_Image_Convert, &Halcon_Image_Convert, "row");  // ���·�תͼƬ

	if( Halcon_Image )    *Halcon_Image = Halcon_Image_Convert;

	return 0;
}

int ConvertHalcon11ToKSJ(HObject Image, unsigned char ** ppImageData, int *pnWidth, int *pnHeight, int *pnBitCount)//ppImageData�ڽӿڵ��ú���Ҫ�ͷ�
{
	mirror_image(Image, &Image, "row");//���·�תͼƬ

	unsigned char * pImageData = NULL;
    int       nWidth, nHeight, nBitCount;

	HTuple     Hchannels;
	count_channels(Image, &Hchannels);
	int nChannels = Hchannels[0].I();    // �õ�ͼ���ͨ���� 1�� 3�� 4

    nBitCount = nChannels << 3;

	HTuple     Htype,Hwidth, Hheight;


	if (nChannels == 1)//����λͼ��ȵ�����Ӧ�ӿ�
	{
		HTuple hpoint;
		get_image_pointer1(Image, &hpoint, &Htype, &Hwidth, &Hheight);

		unsigned char *  ptr = (unsigned char *)hpoint[0].L();     // halcon���ݶ����ͼ��ָ��

                nWidth      = Hwidth[0].I();                           // ͼ���ȣ����أ�
                nHeight     = Hheight[0].I();

		int nLineByte   = MAKEWIDTHBYTES(nWidth, nBitCount );
                int nTotalBytes = nLineByte * nHeight;

		pImageData = new unsigned char[nTotalBytes];

		for (int i = 0; i < nHeight; i++)//���
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

                nWidth      = Hwidth[0].I();                           // ͼ���ȣ����أ�
                nHeight     = Hheight[0].I();

		int nLineByte = MAKEWIDTHBYTES( nWidth, nBitCount );
                int nTotalBytes = nLineByte * nHeight;

		pImageData = new unsigned char[nTotalBytes];

		for (int i = 0; i < Hheight[0].I(); i++)//���졢�̡������浽������
		{
			int nOffsetOnChannel     = i * nWidth;
			int nOffsetOnImage       = i * nLineByte;
                        int nPixelOffset         = 0;

			for (int j = 0; j < nHeight; j++)//���
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
	int nPixelBytes  = nBitCount >> 3;     // ÿ��������ռ�ֽ���
        

	if (nBitCount == 8)//����λͼ��ȵ�����Ӧ�ӿ�
	{
		gen_image1(&Halcon_Image_Convert, "byte", nLineByte, nHeight, (long)pImageData); // ���
	}
	else if (nBitCount == 24 || nBitCount == 32)
	{
                int nChannelBytes = nWidth * nHeight;    // ÿ��ͨ�����ֽ���

		unsigned char  *pImage_r = new unsigned char[nChannelBytes];    // ���ڴ治��Ҫ4�ֽڶ���
		unsigned char  *pImage_g = new unsigned char[nChannelBytes];
		unsigned char  *pImage_b = new unsigned char[nChannelBytes];

		for (int i = 0; i < nHeight; i++)      //�������еĺ졢�̡����ֿ�����
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

		gen_image3(&Halcon_Image_Convert, "byte", nWidth, nHeight, (long)pImage_r, (long)pImage_g, (long)pImage_b);   //���

		delete[]pImage_r;
		delete[]pImage_g;
		delete[]pImage_b;
	}
	else
	{
		return -1;
	}

	mirror_image(Halcon_Image_Convert, &Halcon_Image_Convert, "row");  // ���·�תͼƬ

	if( Halcon_Image )    *Halcon_Image = Halcon_Image_Convert;

	return 0;
}

int ConvertHalcon10ToKSJ(Hobject Image, unsigned char ** ppImageData, int *pnWidth, int *pnHeight, int *pnBitCount)
{
	mirror_image(Image, &Image, "row");//���·�תͼƬ

	unsigned char * pImageData = NULL;
        int       nWidth, nHeight, nBitCount;

	HTuple     Hchannels;
	count_channels(Image, &Hchannels);
	int nChannels = Hchannels[0].I();    // �õ�ͼ���ͨ���� 1�� 3�� 4

        nBitCount = nChannels << 3;

	HTuple     Htype,Hwidth, Hheight;


	if (nChannels == 1)//����λͼ��ȵ�����Ӧ�ӿ�
	{
		HTuple hpoint;
		get_image_pointer1(Image, &hpoint, &Htype, &Hwidth, &Hheight);

		unsigned char *  ptr = (unsigned char *)hpoint[0].L();     // halcon���ݶ����ͼ��ָ��

                nWidth      = Hwidth[0].I();                              // ͼ���ȣ����أ�
                nHeight     = Hheight[0].I();

		int nLineByte   = MAKEWIDTHBYTES(nWidth, nBitCount );
                int nTotalBytes = nLineByte * nHeight;

		pImageData = new unsigned char[nTotalBytes];

		for (int i = 0; i < nHeight; i++)//���
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

                nWidth      = Hwidth[0].I();                           // ͼ���ȣ����أ�
                nHeight     = Hheight[0].I();

		int nLineByte = MAKEWIDTHBYTES( nWidth, nBitCount );
                int nTotalBytes = nLineByte * nHeight;

		pImageData = new unsigned char[nTotalBytes];

		for (int i = 0; i < Hheight[0].I(); i++)//���졢�̡������浽������
		{
			int nOffsetOnChannel     = i * nWidth;
			int nOffsetOnImage       = i * nLineByte;
                        int nPixelOffset         = 0;

			for (int j = 0; j < nHeight; j++)//���
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