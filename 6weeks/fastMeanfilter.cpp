//20230406

#include <opencv2/opencv.hpp>

//Two - pass filtering

int main() {
	//1000이 넘으면 메모리가 안된다. 동적할당으로 설정
	//동적 할당으로 하거나 전역으로 하면 use
	//2차원 배열을 동적할당 하여 만들기
	//fastest mean filter
	CvScalar SAT[100][100];
	
	IplImage* src = cvLoadImage("c:\\temp\\lena.jpeg");
	CvSize size = cvGetSize(src);
	IplImage* mid = cvCreateImage(size, 8, 3);
	IplImage* dst = cvCreateImage(size, 8, 3);
	int K = 10;
	int total = (2 * K + 1);
	for(int y=K;y<size.height-K;y++)
		for (int x = K; x < size.width - K; x++)
		{
			CvScalar g = cvScalar(0, 0, 0);
			for (int v = -K; v <= K; v++)
				{
					CvScalar f = cvGet2D(src, y + v,x);
					g.val[0] += f.val[0] / total;
					g.val[1] += f.val[1] / total;
					g.val[2] += f.val[2] / total;
				}
			cvSet2D(mid, y, x, g);
		}
	cvShowImage("src", src);
	cvShowImage("mid",mid);
	cvWaitKey();
	for (int y = K; y < size.height - K; y++)
		for (int x = K; x < size.width - K; x++)
		{
			CvScalar g = cvScalar(0, 0, 0);
			for (int u = -K; u <= K; u++)
			{
				CvScalar f = cvGet2D(mid, y, x+u);
				g.val[0] += f.val[0] / total;
				g.val[1] += f.val[1] / total;
				g.val[2] += f.val[2] / total;
			}
			cvSet2D(dst, y, x, g);
		}
	cvShowImage("dst", dst);
	cvWaitKey();
}
