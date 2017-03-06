X = randn([6 5])
m = moment(X,3)

pic=imread('/home/kp/CMPE295/tsign.png');
p=rgb2gray(pic);
imshow(p);