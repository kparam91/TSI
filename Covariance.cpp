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

//template<typename _Tp> explicit Mat(const vector<_Tp>& vec, bool copyData=false);
int main(int argc, char **argv)
{
Mat source, gray;
double hu[7];
Moments stop_cmoments;
int sukriti=1;
Mat arr[5];
int o;

while(1){

string file_name=argv[sukriti];
cout<<file_name<<endl;

if(file_name=="z"){
	
	break;
}
source = imread(file_name);

cvtColor( source, gray, CV_BGR2GRAY );
stop_cmoments=moments(gray, false );
HuMoments(stop_cmoments,hu );

vector<double> featureVector;
/*****************Spatial Moments****************/
featureVector.push_back(stop_cmoments.m00);
featureVector.push_back(stop_cmoments.m10 );
featureVector.push_back(stop_cmoments.m01);
featureVector.push_back(stop_cmoments.m20);
featureVector.push_back(stop_cmoments.m11);
featureVector.push_back(stop_cmoments.m02);
featureVector.push_back(stop_cmoments.m30);
featureVector.push_back(stop_cmoments.m21);
featureVector.push_back(stop_cmoments.m12);
featureVector.push_back(stop_cmoments.m03);
/*****************Central Moments****************/
featureVector.push_back(stop_cmoments.mu20);
featureVector.push_back(stop_cmoments.mu11);
featureVector.push_back(stop_cmoments.mu02);
featureVector.push_back(stop_cmoments.mu30);
featureVector.push_back(stop_cmoments.mu21);
featureVector.push_back(stop_cmoments.mu12);
featureVector.push_back(stop_cmoments.mu03);
/************Normalized Central Moments**********/
featureVector.push_back(stop_cmoments.nu20);
featureVector.push_back(stop_cmoments.nu11);
featureVector.push_back(stop_cmoments.nu02);
featureVector.push_back(stop_cmoments.nu30);
featureVector.push_back(stop_cmoments.nu21);
featureVector.push_back(stop_cmoments.nu12);
featureVector.push_back(stop_cmoments.nu03);
/******************Hu Moments*******************/

for(int i=0;i<7;i++){
featureVector.push_back(hu[i]);
}

cout<<endl;

//Conversion to matrix
//Mat fVector(featureVector);
//cout<<fVector<<endl;
arr[sukriti-1]=Mat(featureVector, true);//fVector;

featureVector.clear();
sukriti++;
}

//calculate covariance
Mat mean, covariance;
//const Mat feature(arr);

calcCovarMatrix(arr,5, covariance, mean, CV_COVAR_NORMAL|CV_COVAR_SCALE);

cout<<"Covariance: "<<covariance<<endl;
cout<<"------------------------------------------------------------------------"<<endl;
cout<<"Mean"<<mean<<endl;


/*
cout<<&stop_cmoments.m00<<endl;
cout<<&stop_cmoments.m10 <<endl;
cout<<&stop_cmoments.m01<<endl;
cout<<&stop_cmoments.m20<<endl;
cout<<&stop_cmoments.m11<<endl;
cout<<&stop_cmoments.m02<<endl;
cout<<&stop_cmoments.m30<<endl;
cout<<&stop_cmoments.m21<<endl;
cout<<&stop_cmoments.m12<<endl;
cout<<&stop_cmoments.m03<<endl;
cout<<&stop_cmoments.mu20<<endl;
cout<<&stop_cmoments.mu11<<endl;
cout<<&stop_cmoments.mu02<<endl;
cout<<&stop_cmoments.mu30<<endl;
cout<<&stop_cmoments.mu21<<endl;
cout<<&stop_cmoments.mu12<<endl;
cout<<&stop_cmoments.mu03<<endl;
cout<<&stop_cmoments.nu20<<endl;
cout<<&stop_cmoments.nu11<<endl;
cout<<&stop_cmoments.nu02<<endl;
cout<<&stop_cmoments.nu30<<endl;
cout<<&stop_cmoments.nu21<<endl;
cout<<&stop_cmoments.nu12<<endl;
cout<<&stop_cmoments.nu03<<endl;
*/

return 0;
}








