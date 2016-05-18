#include"ImageProcessFilter.h"
/*
*作者：黄明杨
*功能：浮雕效果滤镜
*输入：Mat inputImg
*输出：Mat &outputImg
*返回值:无
*/
void CameoFilter(Mat inputImg, Mat &outputImg)
{
	Mat tempImg = inputImg.clone();
	for (int i = 1; i < inputImg.rows-1; i++)
	{
		for (int j = 1; j < inputImg.cols-1; j++)
		{
			int b = inputImg.at<uchar>(i - 1, (j - 1) * 3) - inputImg.at<uchar>(i + 1, (j + 1) * 3) + 128;
			int g = inputImg.at<uchar>(i - 1, (j - 1) * 3 + 1) - inputImg.at<uchar>(i + 1, (j + 1) * 3 + 1) + 128;
			int r = inputImg.at<uchar>(i - 1, (j - 1) * 3 + 2) - inputImg.at<uchar>(i + 1, (j + 1) * 3 + 2) + 128;
			tempImg.at<uchar>(i, j * 3) = (b>255 ? 255 : (b < 0 ? 0 : b));
			tempImg.at<uchar>(i, j * 3+1) = (g>255 ? 255 : (g < 0 ? 0 : g));
			tempImg.at<uchar>(i, j * 3+2) = (r>255 ? 255 : (r < 0 ? 0 : r));
		}
	}
	cvtColor(tempImg, outputImg, CV_BGR2GRAY);
}