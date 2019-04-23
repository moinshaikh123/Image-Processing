#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>


using namespace cv;
using namespace std;

void histogram(Mat z)
{
	int i, j, p[260],max=-233;
	for (i = 0; i < 260; i++)
		p[i] = 0;
	for (i = 0; i < z.rows; i++)
	{
		for (j = 0; j < z.cols; j++)
		{
			p[z.at<uchar>(i, j)]++;
		}
	}
	for (i = 0; i < 260; i++)
	{
		if (max < p[i])
			max = p[i];
}
	Mat o(max, 255, CV_8UC1, 255);
	for (j = 0; j < o.cols; j++)
	{
		for (i = 0; i < p[j]; i++)
		{
			o.at<uchar>(max - i-1, j) = 0;
		}
	}
	namedWindow("yo", WINDOW_NORMAL);
	imshow("yo", o);
	waitKey(0);
	
}

int main()
{
	Mat z,r;
	z=imread("G:\\naruto.jpg",CV_8UC1);
	histogram(z);
	namedWindow("yo", WINDOW_NORMAL);
	imshow("yo", r);

}
