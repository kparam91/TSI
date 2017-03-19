#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "opencv2/core/mat.hpp"
using namespace cv;
using namespace std;
int main(int argc, char** argv){
	Mat frames;
	Mat outputImage;
	int x=0;
	int y=0;
	
	/*VideoCapture cap("right.MOV");
	if(!cap.isOpened()){
		cout<<"Could not open the file"<<endl;
	}
	int frame_width=  cap.get(CV_CAP_PROP_FRAME_WIDTH);
 	int frame_height= cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	for(;;){
		cap>>frames;
		if(frames.empty())
		{
			break;
		}*/
	Rect_<int> roi;
	roi.height=200;
	roi.width=200;
	frames=imread("DoNotEnter5.JPG");
	int frame_width=  frames.size().width;
 	int frame_height= frames.size().height;
	imshow("Video",frames);
	outputImage = frames( Rect(x, y, frame_width/2, frame_height/2) );
	
	x+=3;
	/*if((x==frame_width-6)){
	x=0;
	}*/
	cout<<"roi height "<<roi.height<<" sroi.width "<<roi.width<<endl;
	cout<<"height "<<frame_height<<" frame width"<<frame_width<<endl;
	for(int y = roi.y; y+roi.height < frame_height; y=y+10){
    	for(int x = roi.x; x+roi.width <frame_width; x=x+10)
    	{
        	outputImage = frames( Rect(x, y, roi.width,roi.height) );
			imshow("ROI",outputImage);
			cout<<x<<" "<<y<<endl;
			
			waitKey(0);
    	}
		
	}
//cap.release();
return 0;
}
