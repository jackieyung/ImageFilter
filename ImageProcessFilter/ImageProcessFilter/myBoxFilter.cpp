#include"ImageProcessFilter.h"
//功能：方框滤波
//输入参数：unsigned char *buf_highPass, unsigned long * sumIntegral0, int height, int  width,int size
//输出参数：unsigned char * buf_highPass
//返回值：无
void myBoxFilter(unsigned char *buf_Y, unsigned long * sumIntegral, int height, int  width,int size)
{
//	int size=6;
	int n = size*size;
	size /= 2;
	for (int i = height/2; i < height- size; i++)
	{
		for (int j = size; j < width- size; j++)
		{
			int Mij = 0;
			Mij = *(sumIntegral + (i + size)*width + j + size) - *(sumIntegral + (i + size)*width + j - size) - *(sumIntegral + (i - size)*width + j + size) + *(sumIntegral + (i - size)*width + j - size);
			Mij /= n;
			*(buf_Y + i*width + j) = Mij;
		}
	}
}