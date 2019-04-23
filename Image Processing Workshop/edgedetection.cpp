#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>

using namespace cv;
using namespace std;


int isvalid(Mat x, int i, int j)
{
	if (i < 0 || i >= x.rows || j < 0 || j >= x.cols)
		return 0;
	else
		return 1;

}


Mat erosiondilation(Mat x)
{
	Mat a(x.rows, x.cols, CV_8UC1, 255);
	Mat b(x.rows, x.cols, CV_8UC1, 255);
	int i, j, l, n, min = 345, max = -111;
	for (i = 0; i < x.rows; i++)
	{
		for (j = 0; j < x.cols; j++)
		{
			min = 360;
			for (l = -1; l <= 1; l++)
			{
				for (n = -1; n <= 1; n++)
				{
					if (isvalid(x, i + l, j + n))
					{
						if (x.at<uchar>(i + l, j + n) < min)
							min = x.at<uchar>(i + l, j + n);
					}

				}
			}
			if (min == 0)
				a.at<uchar>(i, j) = min;
			else
				a.at<uchar>(i, j) = 255;

		}
	}

	for (i = 0; i < x.rows; i++)
	{
		for (j = 0; j < x.cols; j++)
		{
			max = -255;
			for (l = -1; l <= 1; l++)
			{
				for (n = -1; n <= 1; n++)
				{
					if (isvalid(a, i + l, j + n))
					{
						if (a.at<uchar>(i + l, j + n)>max)
							max = a.at<uchar>(i + l, j + n);
					}

				}
			}
			if (max == 255)
				b.at<uchar>(i, j) = max;
			else
				b.at<uchar>(i, j) = 0;
		}
	}return b;
}



Mat sorbet(Mat x,int pos)
{
	Mat p(x.rows, x.cols, CV_8UC1, 255);
	int i, j, l, n, gx = 0, gy = 0;;
	int a1[3][3] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
	int a2[3][3] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };
	for (i = 0; i < x.rows; i++)
	{
		for (j = 0; j < x.cols; j++)
		{
			gx = 0;
			gy = 0;
			for (l = -1; l <= 1; l++)
			{
				for (n = -1; n <= 1; n++)
				{
					if (isvalid(x, i + l, j + n))
					{
						gx = gx + x.at<uchar>(i + l, j + n)*a1[l + 1][n + 1];
						gy = gy + x.at<uchar>(i + l, j + n)*a2[l + 1][n + 1];
					}
				}
			}
			if (sqrt(gx*gx + gy*gy) >= pos)
				p.at<uchar>(i, j) = 255;
			else
				p.at<uchar>(i, j) = 0;
		}
	}return p;
}

void vary(int pos, void* data)
{
	Mat y,z,w,i;
	y = (*(Mat*)data);
	z = sorbet(y, pos);
	w = erosiondilation(z);
	imshow("track", z);
	imshow("erdil", w);
	Canny(z, i, 50, 200, 3);
	imshow("canny", i);
	waitKey(34);
}


Mat edge(Mat x,int u)
{
	Mat b(x.rows,x.cols,CV_8UC1,255);
	int i, j,gx=0,gy=0,l,h,g;
	int ax[9] = { -1, 0, 1, -1, 0, 1, -1, 0, 1 };
	int ay[9] = { -1, -1, -1, 0, 0, 0, 1, 1, 1 };
	for (i = 0; i < x.rows; i++)
	{
		for (j = 0; j < x.cols; j++)
		{
			for (l = -1; l <= 1; l++)
			{
				for (h = -1; h <= 1; h++)
				{
					if (isvalid(x, i + l, j + h))
					{
						gx = gx + x.at<uchar>(i+l, j+n)*(ax[l + 1][h + 1];
						gy = gy +;
					}
				}
			}
			if (sqrt(gx*gx + gy*gy) > u)
				b.at<uchar>(i, j) = 255;
			else
				b.at<uchar>(i, j) = 0;
		}
	}return b;
}





int main()
{
	int q = 0;
	Mat x,y,z;
	void* data;
	x = imread("G:\\Lenna.png",CV_8UC1);
	data = (Mat*)(&x);
	namedWindow("track", WINDOW_NORMAL);
	createTrackbar("track","track", &q, 255, vary, data);

	



	waitKey(0);
}
