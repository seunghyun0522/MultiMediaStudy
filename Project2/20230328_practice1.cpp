#include <opencv2/opencv.hpp>


int main() {

	IplImage* src = cvLoadImage("c:\\temp\\toodark1.jpg");
	CvSize size = cvGetSize(src);
	IplImage* dst = cvCreateImage(size, 8, 3);




	cvShowImage("src", src);
	cvShowImage("dst", dst);


	cvWaitKey();
	return 0;
}