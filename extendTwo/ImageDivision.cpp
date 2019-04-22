#include <opencv2/opencv.hpp>
#include "math.h"


using namespace cv;

/**
https://blog.csdn.net/ttransposition/article/details/38514127
https://blog.csdn.net/guoyunfei20/article/details/78729490
��ֵƯ�Ʒ�������ͼ��ָ�
Mean Shift�㷨��һ����ָһ�������Ĳ��裬
���������ǰ���ƫ�ƾ�ֵ���ƶ��õ㵽��ƫ�ƾ�ֵ��
Ȼ���Դ�Ϊ�µ���ʼ�㡣�����ƶ���ֱ������һ��������������
*/

int main()
{
	Mat img = imread("F:/ustcsse/AdvancedImageProcessing/experiment/picture/natali.jpg"); //����ͼ��RGB��ͨ��    
	imshow("ԭͼ��", img);
	Mat res;                    //�ָ��ͼ��  
	int spatialRad = 50;        //�ռ䴰�ڴ�С  
	int colorRad = 50;          //ɫ�ʴ��ڴ�С  
	int maxPyrLevel = 2;        //����������  
	pyrMeanShiftFiltering(img, res, spatialRad, colorRad, maxPyrLevel); //ɫ�ʾ���ƽ���˲�  
	imshow("res", res);
	RNG rng = theRNG();

	//https://blog.csdn.net/poem_qianmo/article/details/28261997
	Mat mask(res.rows + 2, res.cols + 2, CV_8UC1, Scalar::all(0));  //��ģ  
	for (int y = 0; y < res.rows; y++)
	{
		for (int x = 0; x < res.cols; x++)
		{
			if (mask.at<uchar>(y + 1, x + 1) == 0)  //��0����Ϊ1����ʾ�Ѿ�������䣬���ٴ���  
			{
				Scalar newVal(rng(256), rng(256), rng(256));
				floodFill(res, mask, Point(x, y), newVal, 0, Scalar::all(5), Scalar::all(5)); //ִ����ˮ���  ��ˮ��䲻�������Ĥmask�ķ��������������磬һ����Ե������ӵ��������������Ϊ��Ĥ���Է�ֹ��䵽��Ե
			}
		}
	}
	imshow("meanShiftͼ��ָ�", res);
	char c=waitKey();
	if (c == 27)
	{
		return 0;
	}
	
}

