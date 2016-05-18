#ifndef IMAGE_PROCESS_FILTER_H
#define IMAGE_PROCESS_FILTER_H

#include<iostream>
#include"opencv2/core/core.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/highgui/highgui.hpp"
using namespace cv;
using namespace std;

void RGBtoYUV(Mat src, unsigned char *buf_Y, unsigned char *buf_U, unsigned char *buf_V, int height, int width);
void  NV21toRGB(Mat &processImg, unsigned char *buf_Y, unsigned char *buf_U, unsigned char *buf_V, int height, int width);
bool YUV2RGBLine(unsigned char *buf_Y, unsigned char *buf_U, unsigned char *buf_V, Mat &B, Mat &G, Mat &R);
void YUV2RGBPoint(unsigned char *buf_Y, unsigned char *buf_U, unsigned char *buf_V, Mat &B, Mat &G, Mat &R, int m, bool *isEnd);

void fastIntegralMean(unsigned char* inputMatrix, unsigned long* outputMatrixSum, int height, int width);
void myBoxFilter(unsigned char *buf_Y, unsigned long * sumIntegral, int height, int  width, int size);


void blackWhiteFilter(Mat &inputImg,Mat &outputImg);//黑白滤镜
void brickFilter(Mat &inputImg, Mat &outputImg);//积木效果，处理人像
void brightContrastFilter(Mat &inputImg, Mat &outputImg);//高亮对比度特效
void FrostedGlassFilter(Mat inputImg, Mat &outputImg);//毛玻璃滤镜
void HighPassFilter(Mat inputImg, Mat &outputImg);//高反差保留
void MosaicFilter(Mat inputImg, Mat &outputImg);//马赛克
void CameoFilter(Mat inputImg, Mat &outputImg);//浮雕
void EdgeDetectionFilter(Mat inputImg, Mat &outputImg);//边缘检测
void skinAdjust(Mat inputImg, Mat &outputImg);//皮肤亮度调整，变白

void skinColorAdjust(Mat inputImg, Mat &outputImg);//皮肤颜色调整
void skinRedOrWhite(Mat inputImg, Mat &outputImg);//皮肤白皙或红润





#endif