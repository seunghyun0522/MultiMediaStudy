#include<opencv2/opencv.hpp>

IplImage* g_img;

CvPoint g_st;
CvPoint g_ed;


void myMouse(int event, int x, int y, int flags, void* param) {
	if (event == CV_EVENT_LBUTTONDOWN) {
		g_st = cvPoint(x, y);
	}
	if (event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON) != 0) {
		g_ed = cvPoint(x, y);
		cvLine(g_img, g_st, g_ed, cvScalar(255, 255, 0), 2);
		g_st = g_ed;
		cvShowImage("image", g_img);
	}

}


int main() {
	g_img = cvLoadImage("c://temp//friend.jpg");
	cvShowImage("image", g_img);
	cvSetMouseCallback("image", myMouse);
	cvWaitKey();
	
	cvReleaseImage(&g_img);
}
