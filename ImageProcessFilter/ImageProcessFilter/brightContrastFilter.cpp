#include "ImageProcessFilter.h"
/*
*作者：黄明杨
*功能：高亮对比度特效
*输入：Mat &inputImg
*输出：Mat &outputImg
*返回值:无
*/
void brightContrastFilter(Mat &inputImg, Mat &outputImg)
{
	float brightnessFactor = 0.25;//-1 to +1
	float contrastFactor = 0;//-1 to +1
	int r, g, b;
	int bfi = (int)(brightnessFactor * 255);
	float cf = 1.0 + contrastFactor;
	cf *= cf;
	int cfi = (int)(cf * 32768) + 1;
	int row = inputImg.rows;
	int col = inputImg.cols;
	outputImg = inputImg.clone();
	for (int i = 0; i < row; i++)
	{
		uchar* dataSrc = inputImg.ptr<uchar>(i);
		uchar* dataFinal = outputImg.ptr<uchar>(i);
		for (int j = 0; j < col; j++)
		{
			b = dataSrc[j * 3];
			g = dataSrc[j * 3 + 1];
			r = dataSrc[j * 3 + 2];
			if (bfi != 0)
			{
				int ri = r + bfi;
				int gi = g + bfi;
				int bi = b + bfi;
				r = ri > 255 ? 255 : (ri < 0 ? 0 : ri);
				g = gi > 255 ? 255 : (gi < 0 ? 0 : gi);
				b = bi > 255 ? 255 : (bi < 0 ? 0 : bi);
			}
			if (cfi != 32769)
			{
				// Transform to range [-128, 127]
				int ri = r - 128;
				int gi = g - 128;
				int bi = b - 128;

				// Multiply contrast factor
				ri = (ri * cfi) >> 15;
				gi = (gi * cfi) >> 15;
				bi = (bi * cfi) >> 15;

				// Transform back to range [0, 255]
				ri = ri + 128;
				gi = gi + 128;
				bi = bi + 128;

				// Clamp to byte boundaries
				r = ri > 255 ? 255 : (ri < 0 ? 0 : ri);
				g = gi > 255 ? 255 : (gi < 0 ? 0 : gi);
				b = bi > 255 ? 255 : (bi < 0 ? 0 : bi);
			}
			dataFinal[j * 3] = b;
			dataFinal[j * 3 + 1] = g;
			dataFinal[j * 3 + 2] = r;
		}
	}

}

