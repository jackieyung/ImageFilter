#include"ImageProcessFilter.h"
/*
*作者：黄明杨
*功能：马赛克效果滤镜
*输入：Mat inputImg
*输出：Mat &outputImg
*返回值:无
*/
void MosaicFilter(Mat inputImg, Mat &outputImg)
{
	int MosiacSize = 16;
	int width = inputImg.cols, height = inputImg.rows;
	int r = 0, g = 0, b = 0;
	outputImg = inputImg.clone();
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (i % MosiacSize == 0)
			{
				if (j%MosiacSize == 0)
				{//整数倍时，取像素赋值                      	 
					r = outputImg.at<uchar>(i, j * 3 + 2);
					g = outputImg.at<uchar>(i, j * 3 + 1);
					b = outputImg.at<uchar>(i, j * 3);
				}
				outputImg.at<uchar>(i, j * 3 + 2) = r;
				outputImg.at<uchar>(i, j * 3 + 1) = g;
				outputImg.at<uchar>(i, j * 3) = b;
			}
			else
			{ //复制上一行           	       		 
				outputImg.at<uchar>(i, j * 3 + 2) = outputImg.at<uchar>(i - 1, j * 3 + 2);
				outputImg.at<uchar>(i, j * 3 + 1) = outputImg.at<uchar>(i - 1, j * 3 + 1);
				outputImg.at<uchar>(i, j * 3) = outputImg.at<uchar>(i - 1, j * 3);
			}
		}


	}
}