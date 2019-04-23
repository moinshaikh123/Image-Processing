// #include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>

using namespace cv;
using namespace std;





int main()
{
	int i, j, t = 1, y = 0, u = 0;
	VideoCapture v(0);
	Mat frame, frame1, frame2, frame3, frame4;
	Mat original, temp;
	int x = 0;
	namedWindow("original", WINDOW_NORMAL);
	createTrackbar("track", "original", &x, 240);

	while (1)
	{
		t = 1;
		v.read(frame1);
		v.read(frame2);
		v.read(frame3);
		v.read(frame4);
		cvtColor(frame1, frame3, CV_RGB2GRAY);
		cvtColor(frame2, frame4, CV_RGB2GRAY);
		original = frame4;



		for (i = 0; i < frame3.rows; i++)
		{
			for (j = 0; j < frame3.cols; j++)
			{
				if ((int)frame3.at<uchar>(i, j) < x)
					frame3.at<uchar>(i, j) = 0;
				else
					frame3.at<uchar>(i, j) = 255;
			}
		}

		for (i = 0; i < frame2.rows; i++)
		{
			for (j = 0; j < frame2.cols; j++)
			{
				if ((int)frame4.at<uchar>(i, j) < x)
					frame4.at<uchar>(i, j) = 0;
				else
					frame4.at<uchar>(i, j) = 255;
			}
		}


		/*absdiff(frame3, frame4, original);*/

		
		for (i = 0; i < frame2.rows; i++)
		{
			for (j = 0; j < frame2.cols; j++)
			{
				if ((int)frame3.at<uchar>(i, j) - (int)frame4.at<uchar>(i, j)>0)
					original.at<uchar>(i, j) = frame3.at<uchar>(i, j) - frame4.at<uchar>(i, j);
				else
					original.at<uchar>(i, j) = frame4.at<uchar>(i, j) - frame3.at<uchar>(i, j);
			}
		}

		for (i = 0; i < original.rows; i++)
		{
			for (j = 0; j < original.cols; j++)

			{
				if ((int)original.at<uchar>(i, j) == 255)
				{
					if (j>original.cols / 2)
					{
						printf("left\n");
						break; break;
					}
					else if (j<original.cols/2)
					{
						printf("right\n");
						break; break;
					}
				}
			}
		}
		imshow("", original);

		waitKey(5);


	}
}
/*while (1)
{
temp=frame;
waitKey(50);

for (i = 0; i < frame.rows/2; i++)
{
for (j = 0; j < frame.cols/2; j++)
{
if ((frame.at<uchar>(frame.rows / 2 - i, frame.cols / 2 - j) - temp.at<uchar>(frame.rows / 2 - i, frame.cols / 2 - j)<-4) || (frame.at<uchar>(frame.rows / 2 + i, frame.cols / 2 + j) - temp.at<uchar>(frame.rows / 2 + i, frame.cols / 2 + j)>4))
{
printf("right\n");
break;

}
else
{
if ((frame.at<uchar>(frame.rows / 2 - i, frame.cols / 2 - j) - temp.at<uchar>(frame.rows / 2 - i, frame.cols / 2 - j)<-4) || (frame.at<uchar>(frame.rows / 2 + i, frame.cols / 2 + j) - temp.at<uchar>(frame.rows / 2 + i, frame.cols / 2 + j)>4))
printf("left\n");
break;
}

}
}
}




}




}*/
