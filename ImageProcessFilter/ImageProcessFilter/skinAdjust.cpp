#include "ImageProcessFilter.h"
/*
*作者：黄明杨
*功能：人物肤色变白变亮
*输入：Mat inputImg
*输出：Mat &outputImg
*返回值:无
*http://www.tuicool.com/articles/IzQbeiB
*/
void skinAdjust(Mat inputImg, Mat &outputImg)
{
	float belta =2.5;//1代表不处理，一般2至10，值越大，亮度越大
	int row = inputImg.rows;
	int col = inputImg.cols;
	outputImg = inputImg.clone();
	for (int i = 0; i < row; i++)
	{
		uchar* dataSrc = inputImg.ptr<uchar>(i);
		uchar* dataFinal = outputImg.ptr<uchar>(i);
		for (int j = 0; j < col; j++)
		{
			float b = (float)dataSrc[j * 3] / 255.0;//归一化
			float g = (float)dataSrc[j * 3 + 1] / 255.0;
			float r = (float)dataSrc[j * 3 + 2] / 255.0;
			b =(float) log(b * (belta - 1) + 1)/log(belta);//套用公式
			g = (float)log(g * (belta - 1) + 1) / log(belta);
			r = (float)log(r * (belta -0.95) + 1) / log(belta);
			b *= 255, g *= 255, r *= 255;
			int bi = b > 255 ? 255 : (b < 0 ? 0 : b);//判断溢出与否
			int gi = g > 255 ? 255 : (g < 0 ? 0 : g);
			int ri = r > 255 ? 255 : (r < 0 ? 0 : r);
			dataFinal[j * 3] = bi;
			dataFinal[j * 3 + 1] = gi;
			dataFinal[j * 3 + 2] = ri;
		}
	}
}