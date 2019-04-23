#include<iostream>
#include<stdio.h>
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


class PathPlanner{
private:
	int startx,starty;
	int endx,endy;
    int plan_method;
    int tot_points;
    int path_length;
    Mat map;
public:
	PathPlanner(int startx,int starty,int endx,int endy,Mat map,int plan_method);
	int isobstacle(int i,int j);
	void getPath();
};


int PathPlanner::isobstacle(int i,int j)
{
  if(map.at<Vec3b>(i,j)[0]==255 && map.at<Vec3b>(i,j)[1]==255 && map.at<Vec3b>(i,j)[2]==255)
    return 1;
  else return 0;	
}

PathPlanner::PathPlanner(int a,int b,int c,int d,Mat img,int e)
{
	startx=a;
	starty=b;
	endx=c;
	endy=d;
	plan_method=e;
	map=img;
	path_length=0;
}
void PathPlanner::getPath()
{
   if(plan_method==3)
   {
     tot_points=0;
   	path_length=-1;
   	int **h;
    h=new int*[map.rows];
    for(int i=0;i<map.rows;i++)
    h[i]=new int[map.cols];
    for(int i=0;i<map.rows;i++)
    {
      for(int j=0;j<map.cols;j++)
	{
	  if(isobstacle(i,j))
	    continue;
	  h[i][j]=(abs(i-endx)+abs(j-endy));
	}
    }

   	Mat mark(map.rows,map.cols,CV_8UC1,Scalar(0));
   	int min=0,minx,miny;
   	minx=startx;
   	miny=starty;
   	while(minx!=endx ||	 miny!=endy)
   	{
   		int a=minx,b=miny;
		min=INT_MAX;
    	for(int i=a-1;i<=a+1;i++)
   		{	 
      		for(int j=b-1;j<=b+1;j++)
      		{
        		if((minx==i && miny==j) || isobstacle(i,j) || mark.at<uchar>(i,j)==1)
 		  			continue;
			tot_points++;
       			 if(h[i][j]<min)
        		{
           			min=h[i][j];
           			minx=i;
           			miny=j;
        		}
    		}
  		}
  		mark.at<uchar>(minx,miny)=1;
  		if(minx==endx && miny==endy);
  		map.at<Vec3b>(minx,miny)[0]=255;
  		path_length++;
  		//imshow("path",map);
  		//waitKey(0);	
	}
	namedWindow("path",WINDOW_NORMAL);
	imshow("path",map);
	cout<<"\nTotal Points Traversed = "<<tot_points<<endl;
	cout<<"\nPath Length = "<<path_length<<endl;
	return;
}

   tot_points=0;

  int **h;
  h=new int*[map.rows];
  for(int i=0;i<map.rows;i++)
  h[i]=new int[map.cols];
 for(int i=0;i<map.rows;i++)
    {
      for(int j=0;j<map.cols;j++)
	{
	  if(isobstacle(i,j))
	    continue;
	  h[i][j]=sqrt(pow(abs(i-gx),2)+pow(abs(j-gy),2))/20;
	}
    }
  path_length=0;
  node **ar;
  ar=new node*[map.rows];
  for(int i=0;i<map.rows;i++)
      ar[i]=new node[map.cols];
  for(int i=0;i<map.rows;i++)
    for(int j=0;j<map.cols;j++)
      {
	ar[i][j].cost=(plan_method==1) ? 0 : h[i][j];
	ar[i][j].x=i;
	ar[i][j].y=j;
      }

  priority_queue<node> s;
  Mat mark(map.rows,map.cols,CV_8UC1,Scalar(0));
  node n,tmp;
  n.cost=0;
  n.x=startx;
  n.y=starty;
  n.px=startx;
  n.py=starty;
  s.push(n);
  mark.at<uchar>(startx,starty)=1;
  namedWindow("Path",WINDOW_NORMAL);
  while(!s.empty())
    {
      n=s.top();
      s.pop();
      for(int i=n.x-1;i<=n.x+1;i++)
	{
	  for(int j=n.y-1;j<=n.y+1;j++)
	    {
	      if(!isvalid(map,i,j))
		continue;
	      if(isobstacle(i,j))
		continue;
	      if(i==n.x && j==n.y)
		continue;
	      if(mark.at<uchar>(i,j)==0)
	     {
	       tot_points++;
	       if(i==endx && j==endy)
		 {
		   ar[i][j].cost=(plan_method==1) ? ar[n.x][n.y].cost+10 : ar[n.x][n.y].cost+10+h[i][j];
		   ar[i][j].px=n.x;
		   ar[i][j].py=n.y;
		   goto jmp;
		 }
	       ar[i][j].cost=(plan_method==1) ? ((i==n.x || j==n.y)?ar[n.x][n.y].cost+10 : ar[n.x][n.y].cost+14) : ((i==n.x || j==n.y)?ar[n.x][n.y].cost+10+h[i][j] : ar[n.x][n.y].cost+10+h[i][j]);
	      ar[i][j].px=n.x;
	      ar[i][j].py=n.y;
	      mark.at<uchar>(i,j)=1;
	      s.push(ar[i][j]);
	      // cout<<ar[i][j].px<<' '<<ar[i][j].py<<endl;
	      // waitKey(1);
	     }
	     else if(mark.at<uchar>(i,j)==1)
		{
		    if(i==n.x || j==n.y)
		    {
		       if(ar[i][j].cost>n.cost+10)
		       {
		          ar[i][j].cost=n.cost+10;
		          ar[i][j].px=n.x;
		          ar[i][j].py=n.y;
		       }
		    }
		    else if(ar[i][j].cost>n.cost+10)
		      {
		      ar[i][j].cost=n.cost+10;
		      ar[i][j].px=n.x;
		      ar[i][j].py=n.y;
		    }

		}
	      // map.at<Vec3b>(i,j)[0]=150;
	      //imshow("img",map);
	      //waitKey(1);
	    }
	}
    }
 jmp:
  int i=endx,j=endy,k,l;
  while(i!=startx || j!=starty)
    { 
      path_length++;
      k=i;
      l=j;
      // cout<<i<<' '<<j<<endl;
      // imshow("img",img);
      // waitKey(0);
      map.at<Vec3b>(i,j)[2]=255;
      map.at<Vec3b>(i,j)[1]=255;
      map.at<Vec3b>(i,j)[0]=0;
      i=ar[k][l].px;
      j=ar[k][l].py;
    }
  imshow("Path",map);
  cout<<"\nTotal Points Traversed = "<<tot_points<<endl;
  cout<<"\nPath Length = "<<path_length<<endl;
  return;
}

int* Find_Centre(Mat img,int* c)
{
	int c1,c2;
    c[0]=c[1]=c[2]=c[3]=c1=c2=0;
    for(int i=0;i<img.rows;i++)
    {
      for(int j=0;j<img.cols;j++)
	{
	  if(img.at<Vec3b>(i,j)[0]==0 && img.at<Vec3b>(i,j)[1]==0 && img.at<Vec3b>(i,j)[2]==255)
	    {
	      c1++;
	      c[0]+=i;
	      c[1]+=j;
	    }
	  if(img.at<Vec3b>(i,j)[0]==0 && img.at<Vec3b>(i,j)[1]==255 && img.at<Vec3b>(i,j)[2]==0)
	    {
	      c2++;
	      c[2]+=i;
	      c[3]+=j;
	    }
	}
    }
   c[0]/=c1;
   c[1]/=c1;
   c[2]/=c2;
   c[3]/=c2;
  return c;
}


Mat filter_image(Mat img)
{
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
  return img2;
}



int main()
{
  Mat img=imread(PATH,CV_LOAD_IMAGE_COLOR);
  img=filter_image(img);
  int c[4],rx,ry,gx,gy,method;
  Find_Centre(img,c);  
  rx=c[0],ry=c[1],gx=c[2],gy=c[3];
  jmp2:
  cout<<"\nEnter Method to be used\n1. Dijkstra(Gives Shortest Path\n2. A Star\n3. Any Path\n";
  cin>>method;
  if(method!=1 && method!=2 && method!=3)
  {
  	cout<<"\nPlease Enter Correct Choice]n";
    goto jmp2;
  }
  PathPlanner P(rx,ry,gx,gy,img,method);
  P.getPath();
  waitKey(0);
  return 0;
}
