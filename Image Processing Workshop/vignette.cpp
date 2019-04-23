#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>

using namespace cv;
using namespace std;

Mat vignette(Mat v)
{
	int i, j,n;
	for (i = 0; i < v.rows; i++)
	{
		for (j = 0; j < v.cols; j++)
		{
			n = 255 - sqrt((i - 250)*(i - 250) + (j - 250)*(j - 250))*255/355;
			v.at<uchar>(i, j) = n;
		}
	}
	return v;
}




int main()
{
	Mat v(500, 500, CV_8UC1, 255);
	Mat r;
	r = vignette(v);
	imshow("vignette", r);
	waitKey(0);

}


