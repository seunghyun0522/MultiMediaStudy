#include <opencv2/opencv.hpp>


int main() {

	IplImage* src = cvLoadImage("c:\\temp\\lena.jpeg");
	CvSize size = cvGetSize(src);
	IplImage* dst = cvCreateImage(size, 8, 3);


	int w = size.width;
	int h = size.height;

	// Image Proessing - 1. Image Filtering
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++) {

			CvScalar f = cvGet2D(src, y, x);			//input color
			CvScalar g;			//output color


			cvSet2D(dst, y, x, g);
		}




	cvShowImage("src", src);
	cvShowImage("dst", dst);


	cvWaitKey();
	return 0;
}