#include <opencv2\opencv.hpp>

IplImage* g_img;
IplImage* g_buf;
CvPoint g_pt;
int g_size = 10;
int g_dsize = 1;

void myMouse(int event, int x, int y, int flags, void* param)
{
	if (event == CV_EVENT_MOUSEMOVE)
	{
		g_pt = cvPoint(x, y);
	}
}

int main()
{
	printf("Example for the final exam: \n");
	printf("Drawing a circle at the mouse position: \n");

	g_img = cvLoadImage("c://temp//friend.jpg");
	g_buf = cvCreateImage(cvGetSize(g_img), 8, 3);

	cvCopy(g_img, g_buf);


	cvShowImage("image", g_img);
	cvSetMouseCallback("image", myMouse);
	while (true)
	{
		cvCopy(g_img, g_buf);
		cvCircle(g_buf, g_pt, g_size, cvScalar(255, 255, 255), -1);
		cvShowImage("image", g_buf);
		if (cvWaitKey(30) != -1) break;


		g_size += g_dsize;
		if (g_size > 30 || g_size < 1) g_dsize = -g_dsize;
	}
	cvReleaseImage(&g_img);
	return 0;
}
