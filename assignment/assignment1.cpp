#include <opencv2/opencv.hpp>
#include <cmath>
//use cmath function 
// cause use double abs


void switchUpDown(IplImage* src, IplImage* dst,int w,int h) {
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++) {

			CvScalar f = cvGet2D(src, h - 1 - y, x);			//input color
			CvScalar g = f;									//output color
			cvSet2D(dst, y, x, g);
		}
}
void halfReplace(IplImage* src, IplImage* dst, int w, int h) {
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			CvScalar f;
			if (x < w / 2) {
				f = cvGet2D(src, y, x + w / 2);
			}
			else {
				f = cvGet2D(src, y, x - w / 2);
			}
			CvScalar g = f;
			cvSet2D(dst, y, x, g);
		}
	}
}
void diamond(IplImage* src, IplImage* dst, int w, int h) {
	//the diamond equation
//Initial setup of diamond
//init float variable
	float centerX = w / 2;
	float centerY = h / 2;
	float a = (w - 1) / 2;
	float b = (h - 1) / 2;
	//Putting in conditions only
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			//create new input data CvScalar
			float nx = float(x) - centerX;
			float ny = float(y) - centerY;
			CvScalar f = cvGet2D(src, y, x);
			//input silver
			int bri = f.val[0] + f.val[1] + f.val[2];
			int avg = bri / 3;
			CvScalar g;

			//equation of point inside a diamond
			float result = (abs(nx) / a) + (abs(ny) / b);
			if (result <= 1)
				g = f;
			else
				g = cvScalar(avg, avg, avg);
			cvSet2D(dst, y, x, g);
		}
	}
}
void circle(IplImage* src, IplImage* dst, int w, int h) {

	//Initial setup of circle
//use centerX, centerY
//use a,b
//putting in conditions only
	float centerX = w / 2;
	float centerY = h / 2;
	float a = w - centerX;
	float b = h - centerY;
	//printf("a : %f\n", a);
	//printf("b : %f\n", b);
	//printf("centerX : %f\n", centerX);
	//printf("centerY : %f\n", centerY);
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			//create new input data CvScalar
			CvScalar f = cvGet2D(src, y, x);
			float nx = float(x) - centerX;
			float ny = float(y) - centerY;
			//printf("x : %f , y : %f\n", nx, ny);
			//input silver
			int bri = f.val[0] + f.val[1] + f.val[2];
			int avg = bri / 3;
			CvScalar g;
			//equation of point inside a circle
			float result = ((nx * nx) / (a * a)) + ((ny * ny) / (b * b));
			//printf("result : %f\n", result);
			if (result <= 1)
				g = f;
			else
				g = cvScalar(avg, avg, avg);
			cvSet2D(dst, y, x, g);
		}
	}
}
void regularCircle(IplImage* src, IplImage* dst, int w, int h) {
	for (int x = 0; x < w; x++)
	{
		for (int y = 0; y < h; y++)
		{
			float a = w / 2;
			float b = h / 2;
			float gapwdh = (float)w / 20;
			float gaphgt = (float)h / 20;
			CvScalar h = cvGet2D(src, y, x);

			if (((x - a) * (x - a) / (gapwdh * 10 * gapwdh * 10) + (y - b) * (y - b) / (gaphgt * 10 * gaphgt * 10) > 1)
				&& ((x - a) * (x - a) / (gapwdh * 11 * gapwdh * 11) + (y - b) * (y - b) / (gaphgt * 11 * gaphgt * 11) <= 1))
				cvSet2D(dst, y, x, h);
			if (((x - a) * (x - a) / (gapwdh * 12 * gapwdh * 12) + (y - b) * (y - b) / (gaphgt * 12 * gaphgt * 12) > 1)
				&& ((x - a) * (x - a) / (gapwdh * 13 * gapwdh * 13) + (y - b) * (y - b) / (gaphgt * 13 * gaphgt * 13) <= 1))
				cvSet2D(dst, y, x, h);
		}
	}
	for (int cnt = 0; cnt < 10; cnt += 2)
	{
		float gapwdh = (float)w / 20;
		float gaphgt = (float)h / 20;
		float fx = (float)w / 2;
		float fy = (float)h / 2;
		for (int x = gapwdh * cnt; x < w; x++)
		{
			for (int y = gaphgt * cnt; y < h; y++)
			{
				float area = (((fx - x) * (fx - x)) / ((fx - gapwdh * cnt) * (fx - gapwdh * cnt)) + ((fy - y) * (fy - y)) / ((fy - gaphgt * cnt) * (fy - gaphgt * cnt)));
				if (area < 1)
				{
					CvScalar i = cvScalar(0, 0, 0);
					cvSet2D(dst, y, x, i);
				}
			}
		}
		for (int x = gapwdh * (cnt + 1); x <w - gapwdh * (cnt + 1); x++)
		{
			for (int y = gaphgt * (cnt + 1); y <h- gaphgt * (cnt + 1); y++)
			{
				float area = (((fx - x) * (fx - x)) / ((fx - gapwdh * (cnt + 1)) * (fx - gapwdh * (cnt + 1)))) + (((fy - y) * (fy - y)) / ((fy - gaphgt * (cnt + 1)) * (fy - gaphgt * (cnt + 1))));
				if (area < 1)
				{
					CvScalar j = cvGet2D(src, y, x);
					cvSet2D(dst, y, x, j);
				}
			}
		}
	}
}
void square(IplImage* src, IplImage* dst, int w, int h) {
	{
		for (int x = 0; x < w; x++) {
			for (int y = 0; y < h; y++)
			{
				CvScalar k = cvGet2D(src, y, x);
				cvSet2D(dst, y, x, k);
			}
		}

		for (int wd = 0; wd < 10; wd++)
		{
			float fx = (float)w / 10;
			float fy = (float)h / 10;

			for (int x = fx * wd; x < fx * (wd + 1); x++)
			{
				int ht;
				if (wd % 2 == 0) ht = 0;
				else ht = 1;

				for (ht; ht < 10; ht += 2)
				{
					for (float y = fy * ht; y < fy * (ht + 1); y++)
					{
						CvScalar l = cvScalar(0, 0, 0);
						cvSet2D(dst, y, x, l);
					}
				}
			}
		}
	}
}
int main() {

	IplImage* src = cvLoadImage("c:\\temp\\sejong.jpg");
	CvSize size = cvGetSize(src);
	IplImage* dst1 = cvCreateImage(size, 8, 3);
	IplImage* dst2 = cvCreateImage(size, 8, 3);
	IplImage* dst3 = cvCreateImage(size, 8, 3);
	IplImage* dst4 = cvCreateImage(size, 8, 3);
	IplImage* dst5 = cvCreateImage(size, 8, 3);
	IplImage* dst6 = cvCreateImage(size, 8, 3);

	int w = size.width;
	int h = size.height;

	// Image Proessing - 1. Image Filtering
	// 
	// (1) Switch Up and Down
	switchUpDown(src, dst1,w,h);
	// (2) Replacing the right half with the left hal
	halfReplace(src, dst2, w, h);
	//(3)diamond
	diamond(src, dst3, w, h);
	//(4)the equation of a circle
	circle(src, dst4, w, h);
	//(5)regular circle
	regularCircle(src, dst5, w, h);

	//(6) square repit
	square(src, dst6, w, h);


	cvShowImage("src", src);
	cvShowImage("dst1", dst1);
	cvShowImage("dst2", dst2);
	cvShowImage("dst3", dst3);
	cvShowImage("dst4", dst4);
	cvShowImage("dst5", dst5);
	cvShowImage("dst6", dst6);
	cvWaitKey();
	return 0;
}