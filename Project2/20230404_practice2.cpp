#include <opencv2/opencv.hpp>

int main() {
	IplImage* src = cvLoadImage("c:\\temp\\lena.jpeg");
	CvSize size = cvGetSize(src);
	IplImage* dst = cvCreateImage(size, 8, 3);
	IplImage* blur = cvCreateImage(size, 8, 3);
	IplImage* diff = cvCreateImage(size, 8, 3);

	//src - blur = diff
	//blur +diff = src

	cvSmooth(src, blur, CV_GAUSSIAN, 21);
	for(int y=0;y<size.height;y++)
		for (int x = 0; x < size.width; x++) {
			CvScalar f = cvGet2D(src, y, x);
			CvScalar b = cvGet2D(blur, y, x);

			CvScalar d;
			for (int k = 0; k < 3; k++)
				//그림으로 저장하기 위해 128을 더함... 
				d.val[k] = f.val[k] - b.val[k] + 128;
			cvSet2D(diff, y, x, d);
		}
	//또렷해지기

	
	for (float alpha = 0.0; alpha < 3.0f; alpha++) {
		for (int y = 0; y < size.height; y++)
			for (int x = 0; x < size.width; x++) {
				CvScalar b = cvGet2D(blur, y, x);
				CvScalar d = cvGet2D(diff, y, x);
				CvScalar g;
				for (int k = 0; k < 3; k++)
					//또렷해지는 과정... 
					g.val[k] = b.val[k] + alpha*(d.val[k] - 128);
				cvSet2D(dst, y, x, g);
			}

		cvShowImage("dst", dst);
		cvWaitKey();
		printf("alpha = %f\n", alpha);
	}
	cvShowImage("src",src);
	//cvShowImage("dst", dst);
	cvShowImage("blur", blur);
	cvShowImage("diff", diff);
	cvWaitKey();
}