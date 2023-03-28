#include <opencv2/opencv.hpp>


int main() {

	IplImage* src = cvLoadImage("c:\\temp\\toodark1.jpg");
	CvSize size = cvGetSize(src);
	IplImage* dst = cvCreateImage(size, 8, 3);


	int histo[256][3] = { 0 };	//3 * 256


		for (int y = 0; y < size.height; y++)
			for (int x = 0; x < size.width; x++)
			{
				CvScalar c = cvGet2D(src, y, x);
				for (int k = 0; k < 3; k++)
					histo[(int)c.val[k]][k]++;
			}



	cvShowImage("src", src);
	cvShowImage("dst", dst);


	cvWaitKey();
	return 0;
}