#include "ImageProcessFilter.h"
/*
*作者：黄明杨
*功能：人物皮肤颜色改变,可用于黄光下黄色消除，类似于阿宝色
*输入：Mat inputImg
*输出：Mat outputImg
*返回值:无
*/
void skinColorAdjust(Mat inputImg, Mat &outputImg)
{
	float rParameter = 1.2;//值从1到10取(1.5,2.5,5.0,10.0)，调整红色亮度分量，值越大，红色越淡。为1时代表不处理
	Mat imgRed, imgGreen, imgBlue, processImg;
	vector<Mat> mbgr(inputImg.channels());
	imgRed = cv::Mat::zeros(inputImg.rows, inputImg.cols, CV_8UC1);
	imgGreen = cv::Mat::zeros(inputImg.rows, inputImg.cols, CV_8UC1);
	imgBlue = cv::Mat::zeros(inputImg.rows, inputImg.cols, CV_8UC1);
	processImg = cv::Mat::zeros(inputImg.rows, inputImg.cols, CV_8UC3);
	for (int i = 0; i < inputImg.rows; i++)
	{
		for (int j = 0; j < inputImg.cols; j++)
		{
			int b = inputImg.at<Vec3b>(i, j)[1];//蓝色通道用绿色代替，使得整体偏洋红
			int g = inputImg.at<Vec3b>(i, j)[1];
			int r = inputImg.at<Vec3b>(i, j)[2];
			imgBlue.at<uchar>(i, j) = b;
			imgGreen.at<uchar>(i, j) = g;
			imgRed.at<uchar>(i, j) = 255 * pow(r / 255.0, rParameter);
		}
	}
	mbgr[0] = imgBlue;
	mbgr[1] = imgGreen;
	mbgr[2] = imgRed;
	merge(mbgr, outputImg);//合并三通道数据到一幅图像
	skinAdjust(outputImg, outputImg);
}
