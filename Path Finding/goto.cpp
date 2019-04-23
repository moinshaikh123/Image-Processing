#include <bits/stdc++.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>
using namespace std;
using namespace cv;


int isvalid(Mat& x,int i,int j)
{
	if(i>=0 && i<(x).rows && j>=0 && j<(x).cols)
		return 1;
	else return 0;
}



void line(Mat& img, Point pt1, Point pt2, const Scalar& color, int thickness=1, int lineType=8, int shift=0);

int discrete(Mat& x,Point temp2,Point a,Point b,int* t,Mat *e,int q)
{           cout<<"everuthing all right here "<<q<<endl;
              int i,j;
              Point temp1=a;
              if(a==b)
              	return 0;

              for(i=-1+temp1.x;i<=1+temp1.x;i++)
              {
              	for(j=-1+temp1.y;j<=1+temp1.y;j++)
              	{
              		if(isvalid(x,i,j))
              		{
                                        if(x.at<uchar>(i,j)==0)
                                        	if((i==temp2.x && j==temp2.y) || (i==a.x && j==a.y))
                                        		continue;
                                        	else
                                        	{           if(q%(*t)==0)
                                        		(*e).at<uchar>(i,j)=0;
                                        		else
                                        			(*e).at<uchar>(i,j)=255;
                                        		temp1.x=i;
                                        		temp1.y=j;
                                        		temp2=a;

                                        		discrete(x,temp2,temp1,b,t,e,++q);
                                        		return 0;

                                        	}
              		}
              	}
              }

}

int main()
{	
int t;
Mat x(150,150,CV_8UC1,Scalar::all(255));
Mat& y=x;
Mat e(150,150,CV_8UC1,Scalar::all(255));
Point a(30,30),b(120,120);

printf("what is the value of t?\n");
scanf("%d",&t);

x.at<uchar>(30,30)=0;
x.at<uchar>(120,120)=0;

cv::line(y,a,b,CV_RGB(0,0,0));
puts("ads\n");


namedWindow("this is initial output image",WINDOW_NORMAL);
imshow("this is initial output image",e);
discrete(y,a,a,b,&t,&e,0);
namedWindow("this is the input image",WINDOW_NORMAL);
imshow("this is the input image",x);	
namedWindow("this is the output image",WINDOW_NORMAL);
imshow("this is the output image",e);


waitKey(0);
return 0;

}	