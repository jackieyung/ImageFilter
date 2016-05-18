#include"ImageProcessFilter.h"
/*
*作者：黄明杨
*功能：毛玻璃效果滤镜
*输入：Mat inputImg
*输出：Mat &outputImg
*返回值:无
*/
void FrostedGlassFilter(Mat inputImg, Mat &outputImg)
{
	outputImg = inputImg.clone();
	int width = inputImg.cols, height = inputImg.rows;
	int imgsize = height*width;
	unsigned char *buf_Y, *buf_U, *buf_V;//原始YUV
	buf_Y = new unsigned char[imgsize];
	buf_U = new unsigned char[imgsize / 4];
	buf_V = new unsigned char[imgsize / 4];//处理YUV420sp格式
	unsigned long *sumIntegral = new unsigned long[imgsize];//累计积分图
	RGBtoYUV(inputImg, buf_Y, buf_U, buf_V, height, width);
	fastIntegralMean(buf_Y, sumIntegral, height, width);
	myBoxFilter(buf_Y, sumIntegral, height,width,8);//修改参数达到不同效果
    NV21toRGB(outputImg, buf_Y, buf_U, buf_V, height, width);
	delete[]buf_Y;
	delete[]buf_U;
	delete[]buf_V;
	delete[]sumIntegral;
}