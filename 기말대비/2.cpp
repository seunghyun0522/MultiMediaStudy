#include <opencv2/opencv.hpp>


IplImage* g_img;
IplImage* g_buf;
CvPoint g_st;
CvPoint g_ed;
CvScalar g_palette[2];

int g_cindex = 0;


void myMouse(int event, int x, int y, int flags, void* param) {

	if (event == CV_EVENT_LBUTTONDOWN)
	{
		g_st = cvPoint(x, y);
		cvCopy(g_img, g_buf);
	}
	else if (event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON) != 0)
	{
		cvCopy(g_img, g_buf);
		g_ed = cvPoint(x, y);
		cvRectangle(g_buf, g_st, g_ed, g_palette[g_cindex], 2);
		cvShowImage("image", g_buf);
	}
	else if (event == CV_EVENT_LBUTTONUP) {
		cvCopy(g_buf, g_img);
	}
	else if (event == CV_EVENT_RBUTTONUP) {
		if (g_cindex == 0) g_cindex = 1;
		else g_cindex = 0;
	}
}
int main() {
	g_palette[0] = cvScalar(0, 0, 0);
	g_palette[1] = cvScalar(255, 255, 255);
	g_img = cvLoadImage("c://temp//friend.jpg");
	g_buf = cvCreateImage(cvGetSize(g_img), 8, 3);
	cvShowImage("image",g_img);
	cvSetMouseCallback("image", myMouse);
	cvWaitKey();
	cvReleaseImage(&g_img);
}
