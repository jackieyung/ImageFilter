#include<iostream>
#include"opencv2/core/core.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/highgui/highgui.hpp"
using namespace cv;
using namespace std;
/*
*作者：huoyan
*功能：高反差保留。增强图像=模糊图像+k*(原始图像-模糊图像)。当k > 1时，是钝化掩模锐化；当k = 1时，即为原始图像 ；当0 <= k<1时，仍为模糊的图像。
*输入：Mat inputImg(RGB三通道)
*输出：Mat &outputImg(RGB三通道)
*返回值:无
*/
void HighPassFilter(Mat inputImg, Mat &outputImg)
{
	int k =15;
	int row = inputImg.rows;
	int col = inputImg.cols;
//	GaussianBlur(inputImg, outputImg, Size(5, 5), 12);
	bilateralFilter(inputImg, outputImg, 12, 12 ,5);
//	boxFilter(inputImg, outputImg, 8, Size(5, 5));
	for (int i = 0; i < row; i++)
	{
		uchar *dataSrc = inputImg.ptr<uchar>(i);
		uchar *dataFinal = outputImg.ptr<uchar>(i);
		for (int j = 0; j < col; j++)
		{
			int b = dataFinal[j * 3] + k*(dataSrc[j * 3] - dataFinal[j * 3]);
			int g = dataFinal[j * 3 + 1] + k*(dataSrc[j * 3 + 1] - dataFinal[j * 3 + 1]);
			int r = dataFinal[j * 3 + 2] + k*(dataSrc[j * 3 + 2] - dataFinal[j * 3 + 2]);
			dataFinal[j * 3+2] = r > 255 ? 255 : (r < 0 ? 0 : r);
			dataFinal[j * 3 + 1] = g > 255 ? 255 : (g < 0 ? 0 : g);
			dataFinal[j * 3 ] = b > 255 ? 255 : (b < 0 ? 0 : b);
		}
	}
//	threshold(outputImg, outputImg, 100, 255,0);
}