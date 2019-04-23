#include <iostream>
#include<math.h>
#include<limits.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<queue>


#define PATH "ps1.png"

using namespace std;
using namespace cv;


class node
{
	public:
  	int cost,x,y,px,py;
};
	int rx,ry,gx,gy;
	bool operator<(node a,node b) {return a.cost > b.cost ? true : false;}

int isvalid(Mat img,int i,int j)
{
	  if(i<0 || j<0 || i>=img.rows || j>=img.cols)
	    return 0;
	  else return 1;
}

Mat raw_image()
{
  Mat img=imread(PATH,CV_LOAD_IMAGE_COLOR);
  Mat img2(img.rows,img.cols,CV_8UC3,Scalar(0,0,0));
  for(int i=0;i<img.rows;i++)
    {
      for(int j=0;j<img.cols;j++)
	{
	  if(img.at<Vec3b>(i,j)[0]<50 && img.at<Vec3b>(i,j)[1]<50 && img.at<Vec3b>(i,j)[2]>200)
	    img2.at<Vec3b>(i,j)[2]=255;
	  if(img.at<Vec3b>(i,j)[0]<50 && img.at<Vec3b>(i,j)[1]>200 && img.at<Vec3b>(i,j)[2]<50)
	    img2.at<Vec3b>(i,j)[1]=255;
	  if(img.at<Vec3b>(i,j)[0]>200 && img.at<Vec3b>(i,j)[1]>200 && img.at<Vec3b>(i,j)[2]>200)
	    {
                img2.at<Vec3b>(i,j)[2]=255;
	  	img2.at<Vec3b>(i,j)[1]=255;
	  	img2.at<Vec3b>(i,j)[0]=255;
	    }
	}
    }

    imshow("img2",img2);
    waitKey(1000);
  return img2;
}



int main()
{
	raw_image();
	cout<<"Hello";
}