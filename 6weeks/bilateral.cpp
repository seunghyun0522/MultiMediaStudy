//20230406
//Binateral function
#include <opencv2/opencv.hpp>

// isotropic
// unisotropic => 구현하기 어렵고 느리지만 결과는 좋다. 

int main() {

	IplImage* src = cvLoadImage("c:\\temp\\lena.jpeg");
	CvSize size = cvGetSize(src);
	IplImage* mid = cvCreateImage(size, 8, 3);
	IplImage* dst = cvCreateImage(size, 8, 3);

	//use Smooth
	cvSmooth(src, dst, CV_BILATERAL, 0, 0, 50, 10);
	cvShowImage("src", src);
	cvShowImage("dst", dst);

	cvWaitKey();
}
