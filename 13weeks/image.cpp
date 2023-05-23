#include <opencv2/opencv.hpp>

int main() {
	IplImage* src[2];

	 src[0] = cvLoadImage("c://temp//cross1.jpg");
	 src[1] = cvLoadImage("c://temp//cross2.jpg");

	 CvSize size = cvGetSize(src[0]);
	 IplImage* dst = cvCreateImage(size, 8, 3);

	 for (float t = 0.0f; t <= 1.0f; t += 0.01f) {
		 for (int y = 0; y < size.height; y++)
			 for (int x = 0; x < size.width; x++) {
				 CvScalar f[2];
				 f[0] = cvGet2D(src[0], y, x);
				 f[1] = cvGet2D(src[1], y, x);

				 CvScalar g;
				 for (int k = 0; k < 3; k++) {
					 g.val[k] = (1 - t) * f[0].val[k] + t * f[1].val[k];

				 }
				 cvSet2D(dst, y, x, g);


			 }
		 cvShowImage("dst", dst);
		 cvWaitKey(30);
	 }




	cvWaitKey();
	return 0;
}
