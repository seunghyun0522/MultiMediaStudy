#include<opencv2/opencv.hpp>

int main() {

	IplImage* src = cvLoadImage("c:\\temp\\sample.jpg");			//source
	CvSize size = cvGetSize(src);
	int w = size.width;
	int h = size.height;
	IplImage* dst = cvCreateImage(size, 8, 3);			//destination

	CvScalar c = cvScalar(200, 236, 255);
	//change Gray-sclae image 
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++) {
			CvScalar f = cvGet2D(src, y, x);
			float bri = f.val[0] + f.val[1] + f.val[2];
			float avg = bri / 3 / 255.0f;
			CvScalar g;
			for (int k = 0; k < 3; k++)
				g.val[k] = c.val[k] * avg;


			cvSet2D(dst, y, x, g);
		}


	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();
	return 0;
}