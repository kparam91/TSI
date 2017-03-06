#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <string.h>
#include <vector>
#include <iostream>

using namespace cv;
using namespace std;
int H, S, V;
Mat src;
bool flag = false;
int hist_w = 512;
int hist_h = 405;
Mat h_hist, s_hist, v_hist;
int x_coord_h, y_coord_h, x_coord_s, y_coord_s, x_coord_v, y_coord_v;
int bin_w;
 Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
  Mat histImage_h( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
  Mat histImage_s( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );	
  Mat histImage_v( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
if  ( event == EVENT_LBUTTONDOWN )
{
        cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	Mat image=src.clone();
        Mat image_dst;
 	Vec3b rgb=image.at<Vec3b>(y,x);
 	int B=rgb.val[0];
 	int G=rgb.val[1];
 	int R=rgb.val[2];
	cout <<"R "<< R <<" G " << G <<" B " << B << endl;
	Mat HSV;
	Mat RGB=image(Rect(x,y,20,20));//capture that pixel in its own ROI
       // Scalar color1;
  	cvtColor(RGB, HSV,CV_BGR2HSV);
	//rectangle(image, Rect(x,y,20,20), Scalar(255),1, 8, 0);
       // bitwise_xor(RGB,Scalar(255,255,255),color1);
        line(image,Point(x+20,y),Point(x-20,y), Scalar(0,255,0), 2, 8, 0  );
        line(image,Point(x,y+20),Point(x,y-20), Scalar(0,255,0), 2, 8, 0  );
        //bitwise_or(image,src,image_dst);
	imshow("My Window", image);
   	Vec3b hsv=HSV.at<Vec3b>(0,0);
    	 H=hsv.val[0];
    	 S=hsv.val[1];
    	 V=hsv.val[2];
	cout <<"H "<< H <<" S " << S <<" V " << V << endl;
	
	x_coord_h = bin_w * H;
	y_coord_h = hist_h - cvRound(h_hist.at<float>(H));
        x_coord_s = bin_w * S;
	y_coord_s = hist_h - cvRound(s_hist.at<float>(S));
        x_coord_v = bin_w * V;
	y_coord_v = hist_h - cvRound(v_hist.at<float>(V));
		
	cout <<"x coord h " <<x_coord_h << "y_coord h "<<y_coord_h <<"Hist h " << cvRound(h_hist.at<float>(H))<<endl;
        cout <<"x coord s " <<x_coord_s << "y_coord s "<<y_coord_s <<"Hist s " << cvRound(s_hist.at<float>(S))<<endl;
	cout <<"x coord v " <<x_coord_v << "y_coord v " << y_coord_v <<"Hist v " << cvRound(v_hist.at<float>(V))<<endl;
	rectangle(histImage_h, Rect(x_coord_h,y_coord_h,10,10), Scalar(255,255,255),1, 8, 0);
        rectangle(histImage_s, Rect(x_coord_s,y_coord_s,10,10), Scalar(255,255,255),1, 8, 0);
        rectangle(histImage_v, Rect(x_coord_v,y_coord_v,10,10), Scalar(255,255,255),1, 8, 0);
        imshow("Hist hue", histImage_h);
	imshow("Hist saturation", histImage_s);
       
      imshow("Hist value", histImage_v);
}
}
	
int main(int argc, char** argv )
{
     Mat dst, hsv;
     src = imread("40-1.jpg");
     cvtColor(src, hsv,CV_BGR2HSV);
     /// Separate the image in 3 places ( h, s and v )
     vector<Mat> hsv_planes;
     split( hsv, hsv_planes );

    /// Establish the number of bins
    int histSize = 256;

   /// Set the ranges ( for h,s,v) )
   float range_h[] = { 0, 180 } ;
   float range_s[] = { 0, 256 } ;
   float range_v[] = { 0, 256 } ;
   //const float* histRange = { range };
   const float* histRange_h = { range_h};
   const float* histRange_s = { range_s};
   const float* histRange_v = { range_v};

   bool uniform = true; bool accumulate = false;

  /// Compute the histograms:
  calcHist( &hsv_planes[0], 1, 0, Mat(), h_hist, 1, &histSize, &histRange_h, uniform, accumulate );
  calcHist( &hsv_planes[1], 1, 0, Mat(), s_hist, 1, &histSize, &histRange_s, uniform, accumulate );
  calcHist( &hsv_planes[2], 1, 0, Mat(), v_hist, 1, &histSize, &histRange_v, uniform, accumulate );

  // Draw the histograms for B, G and R
  //int hist_w = 512; int hist_h = 400;
   bin_w = cvRound( (double) hist_w/histSize );

  /*Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
  Mat histImage_h( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
  Mat histImage_s( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );	
  Mat histImage_v( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );*/

  /// Normalize the result to [ 0, histImage.rows ]
  normalize(h_hist, h_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
  normalize(s_hist, s_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
  normalize(v_hist, v_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
  /// Draw for each channel
  for( int i = 1; i < histSize; i++ )
  {
      line( histImage, Point( bin_w*(i-1), hist_h - cvRound(h_hist.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_h - cvRound(h_hist.at<float>(i)) ),
                       Scalar( 255, 0, 0), 2, 8, 0  );
      cout << "intensity" <<i << "h val" << cvRound(h_hist.at<float>(i)) <<endl;
      line( histImage, Point( bin_w*(i-1), hist_h - cvRound(s_hist.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_h - cvRound(s_hist.at<float>(i)) ),
                       Scalar( 0, 255, 0), 2, 8, 0  );
      line( histImage, Point( bin_w*(i-1), hist_h - cvRound(v_hist.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_h - cvRound(v_hist.at<float>(i)) ),
                       Scalar( 0, 0, 255), 2, 8, 0  );
  }
  for( int i = 1; i < histSize; i++ )
  {
      line( histImage_h, Point( bin_w*(i-1), hist_h - cvRound(h_hist.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_h - cvRound(h_hist.at<float>(i)) ),
                       Scalar( 255, 0, 0), 2, 8, 0  ); // red
      line( histImage_s, Point( bin_w*(i-1), hist_h - cvRound(s_hist.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_h - cvRound(s_hist.at<float>(i)) ),
                       Scalar( 0, 255, 0), 2, 8, 0  ); //green
      line( histImage_v, Point( bin_w*(i-1), hist_h - cvRound(v_hist.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_h - cvRound(v_hist.at<float>(i)) ),
                       Scalar( 0, 0, 255), 2, 8, 0  ); // blue
  }

  /// Display
  namedWindow("My Window",WINDOW_NORMAL);
     
  imshow("My Window", src);
  namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE );
  imshow("calcHist Demo", histImage);
  namedWindow("Hist hue", CV_WINDOW_AUTOSIZE);
  imshow("Hist hue", histImage_h);
  namedWindow("Hist saturation", CV_WINDOW_AUTOSIZE );
  imshow("Hist saturation", histImage_s);
  namedWindow("Hist value", CV_WINDOW_AUTOSIZE );
  imshow("Hist value", histImage_v);
  setMouseCallback("My Window", CallBackFunc, &src); 

     waitKey(0);

     return 0;
}
