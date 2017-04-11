/******************************************************
VIDEO PLAYBACK WITH TRACKBAR
CMPE 295
AUTHORS: KARTHIK PARAMESWARAN / SUKRITI CHOUDHARY
******************************************************/
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "opencv2/core/mat.hpp"
#include <ctime>
using namespace cv;
using namespace std;
Mat frame;
int pos;
VideoCapture source=VideoCapture();
static void onMouse(int event, int x, int y, int, void* ){

if( event == EVENT_LBUTTONUP ){
		source.get(CAP_PROP_POS_FRAMES);
		waitKey(0);
		imshow("Video", frame);
		pos =getTrackbarPos("seek", "Video");
		source.set(CAP_PROP_POS_FRAMES, pos);
		
		return;
	}
	else if(event == EVENT_RBUTTONDOWN){
		time_t now = time(0);
		string timeStamp=ctime(&now);
		string name= "Capture"+ timeStamp+".jpg";
		imwrite(name.c_str(),frame);
		cout<<"Captured"<<endl;
	}
}
int main(int argc, char **argv)
{
	
	
	source=VideoCapture(argv[1]);
	//VideoCapture source(0);
	if(!source.isOpened()) { // check if we succeeded
		cout<<"Open Failure"<<endl;        
		return -1;
	}
	int fc=source.get(CAP_PROP_FRAME_COUNT);
	namedWindow("Video",WINDOW_AUTOSIZE);
	createTrackbar( "seek", "Video", &pos, fc);
	setMouseCallback("Video", onMouse, 0 );
	cout<<"frame height" << source.get(CV_CAP_PROP_FRAME_HEIGHT)<<"frame width "<<source.get(CV_CAP_PROP_FRAME_WIDTH)<<endl	;
	for(;;){

		source>>frame;
		pos=source.get(CAP_PROP_POS_FRAMES);
		if(frame.empty()){
			cout<<"EOF"<<endl;
			break;
		}
		setTrackbarPos("seek", "Video", pos);
		
		imshow("Video", frame);
		waitKey(70);
	}
	source.release();
return 0;
}

