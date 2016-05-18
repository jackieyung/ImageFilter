#include"ImageProcessFilter.h"
/*
*作者：黄明杨
*功能：黑白滤镜
*输入：Mat &inputImg
*输出：Mat &outputImg
*返回值:无
*/
void blackWhiteFilter(Mat &inputImg, Mat &outputImg)
{
	int row = inputImg.rows;
	int col = inputImg.cols;
	int channel = inputImg.channels();
	outputImg = Mat::zeros(row,col,CV_8UC1);
	for (int i = 0; i < row; i++)
	{
		uchar* dataSrc = inputImg.ptr<uchar>(i);
		uchar* dataFinal = outputImg.ptr<uchar>(i);
		for (int j = 0; j < col; j++)
		{
			dataFinal[j] = dataSrc[j*channel] * 0.59 + dataSrc[j*channel + 1] * 0.11 + dataSrc[j*channel + 2] * 0.3;//BGRBGRBGRBGR....Mat类型数据存储方式
		}
	}
}