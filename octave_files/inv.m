stop=imread('stop1.jpg');
stop_gray=rgb2gray(stop);
imwrite(stop_gray,'gray_stop.png')
scale_gray=imresize(stop_gray,0.5);
imwrite(scale_gray,'scaled_stop.png');
stop_invmoments=invmoments(stop_gray);
scale_invmoments=invmoments(scale_gray);


printf("stop sign moments\n");
disp(stop_invmoments);
disp(scale_invmoments);
