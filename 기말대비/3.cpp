#include <opencv2\opencv.hpp>

IplImage* g_img;
IplImage* g_buf;
CvPoint g_pt[3];
int g_pInd = 0;

bool isLeft(CvPoint p, CvPoint q, CvPoint r)
{
	float ax = q.x - p.x;
	float ay = q.y - p.y;
	float bx = r.x - p.x;
	float by = r.y - p.y;

	float cross = ax * by - ay * bx;

	if (cross < 0) return false;
	return true;
}

bool isIn(CvPoint in, CvPoint pt[])
{
	if (isLeft(pt[0], pt[1], in)) return false;
	if (isLeft(pt[1], pt[2], in)) return false;
	if (isLeft(pt[2], pt[0], in)) return false;
	return true;
}


void drawTriangle(IplImage* img, CvPoint pt[])
{
	for (int x = 0; x < img->width; x++)
		for (int y = 0; y < img->height; y++)
		{
			if (isIn(cvPoint(x, y), pt))
				cvSet2D(img, y, x, cvScalar(255, 255, 255));
		}
}

void myMouse(int event, int x, int y, int flags, void* param)
{
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		cvCopy(g_img, g_buf);
	}
	else if (event == CV_EVENT_MOUSEMOVE && g_pInd > 0)
	{
		cvCopy(g_img, g_buf);

		cvLine(g_buf, g_pt[g_pInd - 1], cvPoint(x, y), cvScalar(0, 0, 0), 3);
		cvShowImage("image", g_buf);
	}
	else if (event == CV_EVENT_LBUTTONUP)
	{
		g_pt[g_pInd] = cvPoint(x, y);
		g_pInd++;
		if (g_pInd > 1)
			cvLine(g_img, g_pt[g_pInd - 2], g_pt[g_pInd - 1], cvScalar(0, 0, 0), 3);
		if (g_pInd == 3)
		{
			cvLine(g_img, g_pt[2], g_pt[0], cvScalar(0, 0, 0), 3);
			drawTriangle(g_img, g_pt);
			g_pInd = 0;
		}
		cvShowImage("image", g_img);
	}

}

int main()
{
	printf("Example for the final exam: \n");
	printf("Drawing triangles in the counterclock direction: \n");

	g_img = cvLoadImage("c://temp//friend.jpg");
	g_buf = cvCreateImage(cvGetSize(g_img), 8, 3);


	cvShowImage("image", g_img);

	cvSetMouseCallback("image", myMouse);

	cvWaitKey();

	cvReleaseImage(&g_img);
	return 0;
}
