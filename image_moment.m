clc;
pic=imread('/home/kp/CMPE295/tsign.png');
p=rgb2gray(pic);
p=imresize(p,[100 100]);
imwrite(p,'/home/kp/CMPE295/gray_stop.png');
m=moment(p,3);
disp(m);
imshow(p);