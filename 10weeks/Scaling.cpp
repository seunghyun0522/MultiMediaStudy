#include <opencv2/opencv.hpp>

int main() {
	IplImage* src = cvLoadImage("c:\\temp\\lena.jpeg");
	CvSize size = cvSize(800, 800); //  사이즈 고정!
	IplImage* dst = cvCreateImage(size, 8, 3);
	cvSet(dst, cvScalar(0, 0, 0));

	float a = 2.0f;
	float b = 2.0f;


	//같은 좌표를 복사해서 전달하는 것이 복사의 개념

	//기본 베이스 
	//scale값이 클수록 공백때문에 어두워진다. 
	/*
	for (int y1 = 0; y1 < src->height; y1++) {
		for (int x1 = 0; x1 < src->width; x1++) {
		
			float x2 = a* x1;
			float y2 = b * y1;

			if (x2<0 || x2>dst->width - 1) continue;
			if (y2<0 || y2>dst->height - 1) continue;
			CvScalar f = cvGet2D(src, y1, x1);

			cvSet2D(dst, y2, x2, f);
		}
	}*/


	for (float y2 = 0; y2 < dst->height; y2++) {
		for (float x2 = 0; x2 < dst->width; x2++) {
			float x1 = x2 / a;
			float y1 = y2/b;

			if (x1<0 || x1>src->width - 1) continue;
			if (y1<0 || y1>src->height - 1) continue;

			CvScalar f = cvGet2D(src, y1, x1);
			cvSet2D(dst, y2, x2, f);
		}
	}

	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();
	return 0;
}
