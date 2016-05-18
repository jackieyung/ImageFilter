#include"ImageProcessFilter.h"
//功能：RGB转为YUV
//输入参数：Mat src,height,width
//输出参数：buf_Y，buf_U，buf_V
//返回值：无
void RGBtoYUV(Mat src, unsigned char *buf_Y, unsigned char *buf_U, unsigned char *buf_V, int height,int width)
{
	Mat R = Mat::zeros(src.rows, src.cols, CV_8UC1);
	Mat G = Mat::zeros(src.rows, src.cols, CV_8UC1);
	Mat B = Mat::zeros(src.rows, src.cols, CV_8UC1);
	vector<Mat> sbgr(src.channels());
	split(src, sbgr);//分割三通道
	B = sbgr[0];
	G = sbgr[1];
	R = sbgr[2];
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			//Y   = 0.257*R+0.564*G+0.098*B+16   Cb = -0.148*R - 0.291*G + 0.439*B + 128	Cr = 0.439*R - 0.368*G - 0.071*B + 128
			buf_Y[i*src.cols + j] = int(0.257*R.at<uchar>(i, j) + 0.564*G.at<uchar>(i, j) + 0.098*B.at<uchar>(i, j) + 16);
			buf_U[(i / 2)*src.cols / 2 + j / 2] = int(-0.148*R.at<uchar>(i, j) - 0.291*G.at<uchar>(i, j) + 0.439*B.at<uchar>(i, j) + 128);
			buf_V[(i / 2)*src.cols / 2 + j / 2] = int(0.439*R.at<uchar>(i, j) - 0.368*G.at<uchar>(i, j) - 0.071*B.at<uchar>(i, j) + 128);
		}
	}
}