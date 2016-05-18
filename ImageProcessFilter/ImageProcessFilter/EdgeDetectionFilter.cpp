#include"ImageProcessFilter.h"
/*
*作者：黄明杨
*功能：Sobel边缘检测，素描效果
*输入：Mat &inputImg
*输出：Mat &outputImg
*返回值:无
*/
void EdgeDetectionFilter(Mat inputImg, Mat &outputImg)
{
	Mat tempImg;
	cvtColor(inputImg, tempImg, CV_BGR2GRAY);
	outputImg = Mat::zeros(tempImg.rows,tempImg.cols,CV_8UC1);
	for (int i = 1; i < tempImg.rows - 1; i++)
	{
		for (int j = 1; j < tempImg.cols - 1; j++)
		{
			int tempX = -1* tempImg.at<uchar>(i - 1, j - 1) + 1 * tempImg.at<uchar>(i - 1, j+1)
				- 2 * tempImg.at<uchar>(i, j - 1) + 2*tempImg.at<uchar>(i, j + 1)
				-1*tempImg.at<uchar>(i + 1, j-1) + 1* tempImg.at<uchar>(i + 1, j + 1);
			int tempY = -1 * tempImg.at<uchar>(i - 1, j - 1) - 2 * tempImg.at<uchar>(i - 1, j) - 1 * tempImg.at<uchar>(i - 1, j + 1)
				+ tempImg.at<uchar>(i + 1, j - 1) + 2 * tempImg.at<uchar>(i + 1, j) + tempImg.at<uchar>(i + 1, j + 1);
			outputImg.at<uchar>(i, j) =255- sqrt(abs(tempX)*abs(tempX) + abs(tempY)*abs(tempY))*0.3;
		}
	}
}