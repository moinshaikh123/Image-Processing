#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>

using namespace cv;
using namespace std;

Mat shrink(Mat x)
{
	int i, j, k[3];
	Mat q(x.rows / 2, x.cols / 2, CV_8UC3, 255);
	for (i = 0; i < x.rows/2; i++)
	{
		for (j = 0; j < x.cols/2; j++)
		{
			k[0] = (x.at<Vec3b>(2 * i, 2 * j)[0] + x.at<Vec3b>(2 * i + 1, 2 * j)[0] + x.at<Vec3b>(2 * i, 2 * j + 1)[0] + x.at<Vec3b>(2 * i + 1, 2 * j + 1)[0]) / 4;
			k[1] = (x.at<Vec3b>(2 * i, 2 * j)[1] + x.at<Vec3b>(2 * i + 1, 2 * j)[1] + x.at<Vec3b>(2 * i, 2 * j + 1)[1] + x.at<Vec3b>(2 * i + 1, 2 * j + 1)[1]) / 4;
			k[2] = (x.at<Vec3b>(2 * i, 2 * j)[2] + x.at<Vec3b>(2 * i + 1, 2 * j)[2] + x.at<Vec3b>(2 * i, 2 * j + 1)[2] + x.at<Vec3b>(2 * i + 1, 2 * j + 1)[2]) / 4;

			q.at<Vec3b>(i, j)[0] = k[0];
			q.at<Vec3b>(i, j)[1] = k[1];
			q.at<Vec3b>(i, j)[2] = k[2];
		}
	}

	return q;
}
Mat enlarge(Mat x)
{
	int i, j, m, n;
	Mat q(2 * x.rows, 2 * x.cols, CV_8UC3, 255);
	for (i = 0; i < x.rows; i++)
	{
		for (j = 0; j < x.cols; j++)
		{
			q.at<Vec3b>(2 * i, 2 * j)[2] = x.at<Vec3b>(i, j)[2];
			q.at<Vec3b>(2 * i, 2 * j)[1] = x.at<Vec3b>(i, j)[1];
			q.at<Vec3b>(2 * i, 2 * j)[0] = x.at<Vec3b>(i, j)[0];
			q.at<Vec3b>(2 * i+1, 2 * j)[2] = x.at<Vec3b>(i, j)[2];
			q.at<Vec3b>(2 * i+1, 2 * j)[1] = x.at<Vec3b>(i, j)[1];
			q.at<Vec3b>(2 * i+1, 2 * j)[0] = x.at<Vec3b>(i, j)[0];
			q.at<Vec3b>(2 * i, 2 * j+1)[2] = x.at<Vec3b>(i, j)[2];
			q.at<Vec3b>(2 * i, 2 * j+1)[1] = x.at<Vec3b>(i, j)[1];
			q.at<Vec3b>(2 * i, 2 * j+1)[0] = x.at<Vec3b>(i, j)[0]; 
			q.at<Vec3b>(2 * i+1, 2 * j+1)[2] = x.at<Vec3b>(i, j)[2];
			q.at<Vec3b>(2 * i+1, 2 * j+1)[1] = x.at<Vec3b>(i, j)[1];
			q.at<Vec3b>(2 * i+1, 2 * j+1)[0] = x.at<Vec3b>(i, j)[0];
		}
	}return q;
}

int main()
{
	Mat x,y,z;
	x = imread("G:\\naruto.jpg");
	y=enlarge(x);
	z=shrink(x);
	imshow("original", x);
	imshow("enlarged", y);
	imshow("shrink", z);
	waitKey(0);
}

