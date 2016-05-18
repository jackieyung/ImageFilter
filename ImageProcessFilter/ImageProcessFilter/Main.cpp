#include"ImageProcessFilter.h"
#include<time.h>

int main()
{
//	Mat imgInput = imread(".\\img\\test0000.jpg");
	Mat imgInput = imread(".\\BMP\\000001F1P0S254R000003.bmp");
	Mat imgOutput;
	//blackWhiteFilter(imgInput,imgOutput);
	//brickFilter(imgInput, imgOutput);
	//brightContrastFilter(imgInput, imgOutput);
	clock_t start, end;
	double time;
	start = clock();
	//FrostedGlassFilter(imgInput, imgOutput);
	//MosaicFilter(imgInput, imgOutput);
	HighPassFilter(imgInput, imgOutput);
	//CameoFilter(imgInput, imgOutput);
//	Sobel(imgInput, imgOutput, imgInput.depth(), 1, 1, 3, 1, 0, BORDER_DEFAULT);
//	EdgeDetectionFilter(imgInput, imgOutput);
//	skinAdjust(imgInput, imgOutput);
//	skinColorAdjust(imgInput, imgOutput);
//	skinRedOrWhite(imgInput, imgOutput);
	end = clock();
	time = double(end - start) / CLOCKS_PER_SEC;
	cout << "time:" << time*1000 <<"ms"<< endl;
	imshow("input", imgInput);
	imshow("output", imgOutput);
	imwrite("3.jpg", imgOutput);
//	imwrite(".\\img\\blone6.jpg", imgOutput);
	waitKey();
	
	return 0;
}
