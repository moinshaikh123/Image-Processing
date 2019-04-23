#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>

using namespace cv;
using namespace std;

Mat q(2000, 2000, CV_8UC1, Scalar(0));


int isvalid(Mat x, int i, int j)
{
	if (i < 0 || i >= x.rows || j < 0 || j >= x.cols)
		return 0;

	else

		return 1;

}

int dfs(Mat x, int i, int j, int c)
{

	int l, n;
	if (q.at<uchar>(i, j) == 0)
	{

		if (x.at<uchar>(i, j) == 255)
		{

			for (l = -1; l <= 1; l++)
			{
				for (n = -1; n <= 1; n++)
				{
					if (isvalid(x, i + l, j + n))
					{
						if (x.at<uchar>(i + l, j + n) == 0)
							continue;
						else
						{
							dfs(x, i + l, j + n, c);
							q.at<uchar>(i, j) = 255 / c;
							return 1;
						}
					}
				}

			}
		}
	}
		return 0;
	}



Mat ert(Mat(x))
{
	int i, j,t;
	int c=2;

	for (i = 0; i < x.rows; i++)
	{
		for (j = 0; j < x.cols; j++)
		{
			if (dfs(x, i, j, c))
				c++;
		}
		
	}

	return q;
}



Mat binary(Mat x)
{
	int i, j;
	Mat y(x.rows, x.cols, CV_8UC1, 255);
	for (i = 0; i < x.rows; i++)
	{
		for (j = 0; j < x.cols; j++)
		{
			if (x.at<uchar>(i, j)<127)
				y.at<uchar>(i, j) = 255; 
			else
				y.at<uchar>(i, j) = 0;
		}
	}
	return y;
}


int main()

{
	Mat x,y,z,m;
	x = imread("G:\\sampleimage.png",CV_8UC1);
	y = binary(x);
	m = ert(y);
    namedWindow("img", WINDOW_NORMAL);
	imshow("img", m);
	waitKey(0);
	
}
