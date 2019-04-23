#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>

using namespace cv;
using namespace std;



Mat edit(int x, int y,Mat r)
{
	int i, j;

	
	r.at <uchar> (y, x) = 0;
	return r;
	
}
void change(int e, int x, int y, int d, void* i)
{
	line()
	Mat o,z;
	o = *(Mat*)i;
	int t;
	if (e == EVENT_MOUSEMOVE)
	{
		z = edit(x, y, o);
	}
	
	imshow("mousecallback", z);
	waitKey(5);
	
}


int main()
{
	Mat img(800, 600, CV_8UC1, 255);

	void* data = (void*)(&img);
	namedWindow("mousecallback",WINDOW_AUTOSIZE);
	setMouseCallback("mousecallback", change, data);

	waitKey(0);

}
