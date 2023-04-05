#include <opencv2/opencv.hpp>

int compare(CvScalar a, CvScalar b) {
	//0: equal
	//>0: a>b
	//<0 :a<b
	int a_bri = a.val[0] + a.val[1] + a.val[2];
	int b_bri = b.val[0] + b.val[1] + b.val[2];
	return a_bri - b_bri;
}


int main() {
	IplImage* src = cvLoadImage("c:\\temp\\saltpepper.jpg");

	CvSize size = cvGetSize(src);
	IplImage* dst = cvCreateImage(size, 8, 3);

	int nk = 5;
	//CV_BLUR		:mean filter
	//CV_GAUSSIAN	:gaussian filter
	//CV_MEDIAN		:median filter

	//window의 한개 크기 2*nk -1 항상 홀수

	cvSmooth(src, dst, CV_MEDIAN, 2 * nk - 1);
	//밑에를 간단한 정렬로 표현 Smooth
/*
	int nk = 5;
	int total = (2 * nk + 1) * (2 * nk + 1);

	//할당한다. 전체 갯수
	CvScalar* f = new CvScalar[total];
	for (int y = nk; y < size.height-nk; y++) {
		for (int x = nk; x < size.width-nk; x++) {
			
			int count = 0;
			for (int v = -nk; v <= nk; v++) {
				for (int u = -nk; u <= nk; u++) {
					f[count] = cvGet2D(src, y + v, x + u);
					count++;
				}
			}
			//sorting (정렬 )
			//제일 큰 거 찾기 -> 그거 맨 앞으로 옮기기
			//f[0] : max ~~ f[total-1] : min
			for (int i = 0; i < total - 1; i++) {
				for (int j = i+1; j < total; j++)
					if (compare(f[i], f[j]) < 0) {
						//swap f[9] and f[j]
						CvScalar temp = f[i];
						f[i] = f[j];
						f[j] = temp;
					}
			}
			CvScalar g = f[total/2];
			cvSet2D(dst, y, x, g);
			//free(f);
		}
	}
	delete[]f;
	*/
	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();
	return 0;
}