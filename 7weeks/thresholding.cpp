#include <opencv2/opencv.hpp>


//thresholding

//제곱이 되어있다.
float getDiff2(CvScalar a, CvScalar b) {
	return (a.val[0] - b.val[0])* (a.val[0] - b.val[0]) + (a.val[1] - b.val[1]) * (a.val[1] - b.val[1]) + (a.val[2] - b.val[2]) * (a.val[2] - b.val[2]);
}
int main() {
	IplImage* src = cvLoadImage("c:\\temp\\lena.jpeg");
	CvSize size = cvGetSize(src);
	IplImage* dst = cvCreateImage(size, 8, 3);

	CvScalar pal[] = { cvScalar(0,0,0),cvScalar(255,255,255),cvScalar(255,0,0) ,
		cvScalar(0,255,0),cvScalar(0,0,255),cvScalar(255,255,0)
		,cvScalar(0,255,255),cvScalar(255,0,255)};
	int numPal = 5;
	

	for(int y=0;y<size.height;y++)
		for (int x = 0; x < size.width; x++) {
			CvScalar f = cvGet2D(src, y, x);

			int min_ind = 0;
			float min_diff = 10000000;
			for (int i = 0; i < numPal; i++) {
				float diff = getDiff2(f,pal[i]);
				if (diff < min_diff) {
					min_diff = diff;
					min_ind = i;
				}
			}
			CvScalar g = pal[min_ind];
			cvSet2D(dst, y, x, g);
		}

	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();
}
