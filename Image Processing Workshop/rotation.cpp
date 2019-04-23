#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>

using namespace cv;
using namespace std;



Mat rotate(Mat x, int o)
{
	int i, j,l,m;
	Mat r(2 * x.rows, 2 * x.cols, CV_8UC1, 255);
	for (i = x.rows; i < x.rows + x.rows / 2; i++)
	{
		for (j =0; j < x.cols; j++)
		{
			r.at<uchar>(i,j)=
		}
	}
}

int main()
{
	int o;
	Mat y,x = imread("G:\\naruto.jpg");
	y=rotate(x,o);
}
