#include <opencv2/opencv.hpp>

int main() {
	IplImage* src = cvLoadImage("c:\\temp\\lena.jpeg");
	CvSize size = cvGetSize(src);
	IplImage* dst = cvCreateImage(size, 8, 3);
	IplImage* blur = cvCreateImage(size, 8, 3);

	//사각형의 좌표 2,1,3,0 
	int pat[10] = { 1,8,0,6,2,5,7,3,4 };
	int numPat = 10;

	cvSet(dst, cvScalar(0, 0, 0));
	cvSmooth(src, blur, CV_BLUR, 5);

	//한칸씩 건너 뛴다.
	for(int y=0;y<size.height-2;y+=3)
		for (int x = 0; x < size.width-2; x+=3)
		{
			CvScalar f = cvGet2D(src, y, x);
			for (int k = 0; k < 3; k++) {
				int bri = f.val[k];

				float div = 255.0f / (numPat + 1);
				int lev = bri / div;
				if (lev > 10) lev = 10;
				for (int i = 0; i < lev; i++) {
					int x2 = x + pat[i] % 3;
					int y2 = y + pat[i] / 3;
					CvScalar g = cvGet2D(dst, y2, x2);
					g.val[k] = 255;
					cvSet2D(dst, y2, x2, g);
				}
			}
		}



	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();
}
