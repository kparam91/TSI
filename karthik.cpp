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

int main(){


Mat_<float> samples = (Mat_<float>(3, 2) << 500.0, 350.2,
                                            500.5, 355.8,
                                            498.7, 352.0);
Mat data[3];

vector<float> i;
i.push_back(500.0);
i.push_back(350.2);

Mat temp(i);
data[0]= temp;
vector<float> j;
j.push_back(500.5);
j.push_back(355.8);

Mat temp2(j);
data[1]=temp2;
vector<float> k;

k.push_back(498.7);
k.push_back(352.0);
Mat temp3(k);
data[2]=temp3;

Mat cov, mu;
cv::calcCovarMatrix(samples,cov, mu, CV_COVAR_NORMAL|CV_COVAR_ROWS|CV_COVAR_SCALE);
//cv::calcCovarMatrix(data, 3,cov, mu, CV_COVAR_NORMAL);//|CV_COVAR_ROWS);
//cov=cov/(samples.rows-1);



cout<<"rows: "<<samples.rows<<endl;
cout << "cov: " << endl;
cout << cov << endl;

cout << "mu: " << endl;
cout << mu << endl;

return 0;
}
