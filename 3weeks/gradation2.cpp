#include<opencv2/opencv.hpp>

int main() {
	int w = 600;
	int h = 400;
	//CvSize size = cvSize(200,100);
	//size.width = 200;
	//size.height = 100;

	IplImage* img = cvCreateImage(cvSize(w, h), 8, 3);

	cvSet(img, cvScalar(255, 255, 255));
	CvScalar c1 = cvScalar(255, 0, 0);
	CvScalar c2 = cvScalar(0, 0, 255);

	//same bottom code
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++) {

			float nx = float(x) / (w - 1) * 2 - 1;	// nx :-1~1
			float ny = float(y) / (h - 1) * 2 - 1;	//ny : -1 ~1

			float a = sqrt(nx * nx +ny *ny);	//(1-a)
			CvScalar c = cvScalar(0, 0, 0);
			for (int k = 0; k < 3; k++)
				c.val[k] = a * c1.val[k] + (1 - a) * c2.val[k];
			cvSet2D(img, y, x, c);
			/*
			float b = 255.0f*nx;
			float g = 0;
			float r= 255 -255.0f*nx;
			cvSet2D(img, y, x, cvScalar(b,g, r));
			*/
		}

	cvShowImage("image", img);
	cvWaitKey();
}