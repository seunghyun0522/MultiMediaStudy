#include <opencv2/opencv.hpp>

int main()
{
	//  add file location 

	IplImage* imgs[2];
	imgs[0] = cvLoadImage("c:\\temp\\sample.jpg");
	imgs[1] = cvLoadImage("c:\\temp\\sample2.jpg");

	for (int i = 0; i < 2; i++) {
		if (imgs[i] == nullptr) return 0;
	}

	//1ms -> change file 
	int index = 0;
	while (true) {
		cvShowImage("image", imgs[index]);
		int key = cvWaitKey();
		switch (key) {
		case '1': index = 0; break;
		case '2': index = 1; break;
		case 'q': return -1; break;
		default:			 break;
		}
	}
	for (int i = 0; i < 2; i++) {
		cvReleaseImage(&imgs[i]);
	}


	return 0;
}