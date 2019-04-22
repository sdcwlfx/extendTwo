#include <opencv2/opencv.hpp>
#include "math.h"


using namespace cv;

/**
https://blog.csdn.net/ttransposition/article/details/38514127
https://blog.csdn.net/guoyunfei20/article/details/78729490
均值漂移方法进行图像分割
Mean Shift算法，一般是指一个迭代的步骤，
即先算出当前点的偏移均值，移动该点到其偏移均值，
然后以此为新的起始点。继续移动，直到满足一定的条件结束。
*/

int main()
{
	Mat img = imread("F:/ustcsse/AdvancedImageProcessing/experiment/picture/natali.jpg"); //读入图像，RGB三通道    
	imshow("原图像", img);
	Mat res;                    //分割后图像  
	int spatialRad = 50;        //空间窗口大小  
	int colorRad = 50;          //色彩窗口大小  
	int maxPyrLevel = 2;        //金字塔层数  
	pyrMeanShiftFiltering(img, res, spatialRad, colorRad, maxPyrLevel); //色彩聚类平滑滤波  
	imshow("res", res);
	RNG rng = theRNG();

	//https://blog.csdn.net/poem_qianmo/article/details/28261997
	Mat mask(res.rows + 2, res.cols + 2, CV_8UC1, Scalar::all(0));  //掩模  
	for (int y = 0; y < res.rows; y++)
	{
		for (int x = 0; x < res.cols; x++)
		{
			if (mask.at<uchar>(y + 1, x + 1) == 0)  //非0处即为1，表示已经经过填充，不再处理  
			{
				Scalar newVal(rng(256), rng(256), rng(256));
				floodFill(res, mask, Point(x, y), newVal, 0, Scalar::all(5), Scalar::all(5)); //执行漫水填充  漫水填充不会填充掩膜mask的非零像素区域。例如，一个边缘检测算子的输出可以用来作为掩膜，以防止填充到边缘
			}
		}
	}
	imshow("meanShift图像分割", res);
	char c=waitKey();
	if (c == 27)
	{
		return 0;
	}
	
}

