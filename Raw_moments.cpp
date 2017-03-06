#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{

 ofstream myfile;

  

Mat source, gray;
double hu[7];
 Moments stop_cmoments;
int sukriti=1;


while(1){

string file_name=argv[sukriti];
if(file_name=="z"){
	break;
}
source = imread(file_name);
cvtColor( source, gray, CV_BGR2GRAY );
stop_cmoments=moments(gray, false );
HuMoments(stop_cmoments,hu );

if(sukriti==1){
myfile.open ("Moments.csv");
myfile<<"image,s00,s10,s01,s20,s11,s02,s30,s21,s12,s03,c20,c11,c02,c30,c21,c12,c03,n20,n11,n02,n30,n21,n12,n03,hu0,hu1,hu2,hu3,hu4,hu5,hu6"<<endl;
}
else{
myfile.open ("Moments.csv",fstream::app);
}
//<<"*****************Spatial Moments****************"<<endl
myfile<<file_name<<","
<<stop_cmoments.m00<<","
<<stop_cmoments.m10<<","
<<stop_cmoments.m01<<","
<< stop_cmoments.m20<<","
<< stop_cmoments.m11<<"," 
<<stop_cmoments.m02<<","
<< stop_cmoments.m30<<","
<< stop_cmoments.m21<<","
<< stop_cmoments.m12<<","
<< stop_cmoments.m03<<","
//<<"*****************Central Moments****************"<<endl
<<stop_cmoments.mu20<<","
<< stop_cmoments.mu11<<","
<<stop_cmoments.mu02<<","
<< stop_cmoments.mu30<<","
<< stop_cmoments.mu21<<","
<< stop_cmoments.mu12<<","
<< stop_cmoments.mu03<<","
//<<"************Normalized Central Moments**********"<<endl
<< stop_cmoments.nu20<<","
<< stop_cmoments.nu11<<","
<<stop_cmoments.nu02<<","
<<stop_cmoments.nu30<<","
<< stop_cmoments.nu21<<","
<< stop_cmoments.nu12<<","
<< stop_cmoments.nu03<<",";
for(int i=0;i<7;i++){
myfile<<hu[i]<<',';
}
myfile<<endl;
myfile.close();
//cout<<"sukriti "<<sukriti<<endl;
sukriti++;
}
cout<<"SUCCESS!"<<endl;
return 0;
}

