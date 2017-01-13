#ifndef CKSJTOHANCON_H
#define CKSJTOHANCON_H
#define HALCON11

#ifdef HALCON11

#define HCPP_LEGACY_API
#include "HalconCpp.h"
using namespace HalconCpp;
int  ConvertKSJToHalcon11(unsigned char * pImageData, int nWidth, int nHeight, int nBitCount, HObject *Halcon_Image);
int  ConvertHalcon11ToKSJ(HObject Image, unsigned char ** ppImageData, int *pnWidth, int *pnHeight, int *pnBitCount);

#else

//#define HCPP_LEGACY_API
#include "HalconCpp.h"
using namespace Halcon;
int  ConvertKSJToHalcon10(unsigned char * pImageData, int nWidth, int nHeight, int nBitCount, Hobject *Halcon_Image);
int  ConvertHalcon10ToKSJ(Hobject Image, unsigned char ** ppImageData, int *pnWidth, int *pnHeight, int *pnBitCount);

#endif



#endif // CKSJTOHANCON_H