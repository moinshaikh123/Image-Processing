#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat x;
	
	x = imread("G:\\abc.jpg");
	printf("mast hai abtak");
	imshow("mast hai boss", x);
	int iKey = waitKey(50);
	waitKey(0);
	return 0;
}
