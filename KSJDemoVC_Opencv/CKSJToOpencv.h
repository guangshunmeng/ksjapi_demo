
#include "cv.h"
#include "highgui.h"
#include "opencv.hpp"
using namespace std;
using namespace cv;

int ConvertKSJToOpencv3(unsigned char * pImageData, int nWidth, int nHeight, int nBitCount, Mat **ppcvImg);
int ConvertOpnecv3ToKSJ(Mat cvImg, unsigned char ** ppImageData);