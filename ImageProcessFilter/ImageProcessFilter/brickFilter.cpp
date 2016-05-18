#include "ImageProcessFilter.h"
/*
*作者：黄明杨
*功能：积木效果，用于处理人像
*输入：Mat &inputImg
*输出：Mat &outputImg
*返回值:无
*/
void brickFilter(Mat &inputImg, Mat &outputImg)
{
	int threshHold = 128;
	int row = inputImg.rows;
	int col = inputImg.cols;
	int avg = 0;
	outputImg = inputImg.clone();
	for (int i = 0; i < row; i++)
	{
		uchar* dataSrc = inputImg.ptr<uchar>(i);
		uchar* dataFinal = outputImg.ptr<uchar>(i);
		for (int j = 0; j < col; j++)
		{
			avg = (dataSrc[j * 3] + dataSrc[j * 3 + 1] + dataSrc[j * 3 + 2]) / 3;
			avg = avg >= threshHold ? 255 : 0;
			dataFinal[j * 3] = avg;
			dataFinal[j * 3 + 1] = avg;
			dataFinal[j * 3 + 2] = avg;
		}
	}
}