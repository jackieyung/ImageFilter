#include"ImageProcessFilter.h"
#include<Thread>
//YUV转RGB的系数
int csU_blue = 1.779 * (1 << 8);
int csU_green = 0.346*(1 << 8);
int csV_green = 0.717*(1 << 8);
int csV_red = 1.408*(1 << 8);
int PxHeight, PxWidth;
/*YUV420SP(NV21)转RGB*/
void  NV21toRGB(Mat &processImg, unsigned char *buf_Y, unsigned char *buf_U, unsigned char *buf_V, int height, int width)
{
	PxHeight = height;
	PxWidth = width;
	Mat R = Mat::zeros(height, width, CV_8UC1);
	Mat G = Mat::zeros(height, width, CV_8UC1);
	Mat B = Mat::zeros(height, width, CV_8UC1);

	YUV2RGBLine(buf_Y, buf_U, buf_V, B, G, R);
	//bool isend = false;
	//YUV2RGBPoint(buf_Y, buf_U, buf_U, B, G, R, 0, 0,&isend);

	Mat img = Mat::zeros(height, width, CV_8UC3);
	vector<Mat> mbgr(img.channels());
	mbgr[0] = B;
	mbgr[1] = G;
	mbgr[2] = R;

	merge(mbgr, processImg);//合并三通道数据到一幅图像
}
bool YUV2RGBLine(unsigned char *buf_Y, unsigned char *buf_U, unsigned char *buf_V, Mat &B, Mat &G, Mat &R)
{/*实验发现，在这里开四个线程比开八个线程大约慢0.01s-0.02S*/
	bool t0End = false, t1End = false, t2End = false, t3End = false, t4End = false, t5End = false, t6End = false, t7End = false;// t8End = false, t9End = false;
	thread t0(YUV2RGBPoint, buf_Y, buf_U, buf_V, B, G, R, 0, &t0End);
	thread t1(YUV2RGBPoint, buf_Y, buf_U, buf_V, B, G, R, 1, &t1End);
	thread t2(YUV2RGBPoint, buf_Y, buf_U, buf_V, B, G, R, 2, &t2End);
	thread t3(YUV2RGBPoint, buf_Y, buf_U, buf_V, B, G, R, 3, &t3End);
	thread t4(YUV2RGBPoint, buf_Y, buf_U, buf_V, B, G, R, 4, &t4End);
	thread t5(YUV2RGBPoint, buf_Y, buf_U, buf_V, B, G, R, 5, &t5End);
	thread t6(YUV2RGBPoint, buf_Y, buf_U, buf_V, B, G, R, 6, &t6End);
	thread t7(YUV2RGBPoint, buf_Y, buf_U, buf_V, B, G, R, 7, &t7End);
	/*thread t8(YUV2RGBPoint, buf_Y, buf_U, buf_V, B, G, R, 8, &t8End);
	thread t9(YUV2RGBPoint, buf_Y, buf_U, buf_V, B, G, R, 9, &t9End);*/
	//启动各线程
	t0.join();
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	/*t8.join();
	t9.join();*/

	bool isEnd = t0End&&t1End&&t2End&&t3End&&t4End&&t5End&&t6End&&t7End;// &&t4End&&t5End&&t6End&&t7End;// &&t8End&&t9End;
	while (!isEnd);

	return isEnd;
}

void YUV2RGBPoint(unsigned char *buf_Y, unsigned char *buf_U, unsigned char *buf_V, Mat &B, Mat &G, Mat &R, int m, bool *isEnd)
{
	for (int i = 0; i < PxHeight; i += 8)
	{
		for (int j = 0; j < PxWidth; j++)
		{
			//YUV分别公式转换R' = Y' + 1.402*V';			G' = Y' - 0.344*U' - 0.714*V';				B' = Y' + 1.772*U'
			int b = 0, g = 0, r = 0;//判断点是否溢出，作溢出处理
			//将YUV分量的值先分离出来，以减少每次运算所用的时间
			int yComp = buf_Y[(i + m)*PxWidth + j];
			int uComp = buf_U[((i + m) / 2)*PxWidth / 2 + j / 2] - 128;
			int vComp = buf_V[((i + m) / 2)*PxWidth / 2 + j / 2] - 128;

			//方法一：浮点运算
			/*b = (cvRound)(buf_Y[(i + m)*width + j + n] + 2.032 * (buf_U[((i + m) / 2)*width / 2 + (j + n) / 2] - 128));
			g = (cvRound)(buf_Y[(i + m)*width + j + n] - 0.395 * (buf_U[((i + m) / 2)*width / 2 + (j + n) / 2] - 128) - 0.581 * (buf_V[((i + m) / 2)*width / 2 + (j + n) / 2] - 128));
			r = (cvRound)(buf_Y[(i + m)*width + j + n] + 1.140 * (buf_V[((i + m) / 2)*width / 2 + (j + n) / 2] - 128));*/

			//方法二：整形运算
			//b = (1164 * yComp + 2017 * uComp) / 1000;       // b分量
			//g = (1164 * yComp - 392 * uComp - 813 * vComp) / 1000;    // g分量
			//r = (1164 * yComp + 1596 * vComp) / 1000;
			//b = (1000*yComp + 1779 * uComp) / 1000;       // b分量
			//g = (1000*yComp - 346 * uComp - 717 * vComp) / 1000;    // g分量
			//r = (1000*yComp + 1408 * vComp) / 1000;

			//方法三：移位运算
			b = yComp + (csU_blue * uComp >> 8);
			g = yComp - ((csU_green  * uComp + csV_green * vComp) >> 8);
			r = yComp + (csV_red * vComp >> 8);

			//方法四：查表法
			/*b = yComp + U_B[uComp];
			g = yComp - U_G[uComp] - V_G[vComp];
			r = yComp + V_R[vComp];*/

			B.at<uchar>(i + m, j) = b<0 ? 0 : (b>255 ? 255 : b);
			G.at<uchar>(i + m, j) = g<0 ? 0 : (g>255 ? 255 : g);
			R.at<uchar>(i + m, j) = r<0 ? 0 : (r>255 ? 255 : r);
		}
	}

	*isEnd = true;
}