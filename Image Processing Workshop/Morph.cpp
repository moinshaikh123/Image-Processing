#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>

using namespace cv;
using namespace std;

Mat morph(Mat x, Mat y,int u)
{
	int i, j;
	Mat m(x.rows, x.cols, CV_8UC3, 255);

	for (i = 0; i < x.rows; i++)
	{
		for (j = 0; j < x.cols; j++)
		{
			m.at<Vec3b>(i, j)[2] = ((u)*x.at<Vec3b>(i, j)[2] + (100 - u)*y.at<Vec3b>(i, j)[2]) / 100;
			m.at<Vec3b>(i, j)[1] = ((u)*x.at<Vec3b>(i, j)[1] + (100 - u)*y.at<Vec3b>(i, j)[1]) / 100;
			m.at<Vec3b>(i, j)[0] = ((u)*x.at<Vec3b>(i, j)[0] + (100 - u)*y.at<Vec3b>(i, j)[0]) / 100;
		}
	}return m;
}

int main()
{
	int u=0;
	Mat x, y,z;
	x = imread("G:\\naruto.jpg");
	y = imread("G:\\naruto (2).jpg");
	namedWindow("morph", WINDOW_NORMAL);
	createTrackbar("morph", "morph", &u, 100);
	while (1)
	{
		z = morph(x, y, u);
		imshow("morph", z);
		waitKey(30);
	}


}
