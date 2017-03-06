#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
string file_name="stop1.jpg";
Mat source, gray;
double hu[7];
 Moments stop_cmoments;
source = imread(file_name);
namedWindow( "window1", CV_WINDOW_AUTOSIZE );
cvtColor( source, gray, CV_BGR2GRAY );
stop_cmoments=moments(gray, false );
printf("%lf %lf %lf %lf %lf %lf %lf \n",stop_cmoments.nu20, stop_cmoments.nu11, stop_cmoments.nu02, stop_cmoments.nu30, stop_cmoments.nu21, stop_cmoments.nu12, stop_cmoments.nu03);
HuMoments(stop_cmoments,hu );
for(int i=0;i<7;i++){
	cout<<hu[i]<<endl;
}
imshow( "window1", source );
waitKey(0);
return 0;
}

