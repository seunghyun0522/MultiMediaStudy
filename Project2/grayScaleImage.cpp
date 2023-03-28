#include<opencv2/opencv.hpp>

int main() {

	IplImage* src = cvLoadImage("c:\\temp\\lena.jpeg");			//source
	CvSize size = cvGetSize(src);
	int w = size.width;
	int h = size.height;
	IplImage* dst = cvCreateImage(size,8,3);			//destination


	//change Gray-sclae image 
	for(int y=0;y<h;y++)
		for (int x = 0; x < w; x++) {
			CvScalar f = cvGet2D(src, y, x);
			int bri = f.val[0] + f.val[1] + f.val[2];
			int avg = bri / 3;
			CvScalar g = cvScalar(avg,avg,avg);
			if (x < w/ 2)g = f;
		
			cvSet2D(dst, y, x, g);
		}


	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();
	return 0;
}