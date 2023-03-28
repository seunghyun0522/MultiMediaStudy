#include <opencv2/opencv.hpp>

int main()
{
	//  add file location 
	IplImage* img = cvLoadImage("c:\\temp\\sample.jpg");	

	// if img is NULL, program exit.
	if (img == nullptr) { // null pointer -> nullptr
		printf("File not found!");
		return -1;
	}
	//lplImage is structure 
	// if you curious its structure , command + click

	// same (*img).width
	int w = img->width;
	int h = img->height;
	printf("width : %d \n height: %d\n", w, h);

	//create window
	cvNamedWindow("Test Window");

	//window file nickName 
	cvShowImage("hello image1",img);	
	cvShowImage("hello image2", img);


	// when input keyboard function -> exit
	cvWaitKey(1000);
	

	//destroy window
	cvDestroyWindow("hello image2");

	//input keyboard
	char key = cvWaitKey();
	printf("key =%c \n", key);

	//img -> file save , 
	cvSaveImage("c:\\temp\\sample.bmp", img);

	//memory free-> why?memory leak.....
	cvReleaseImage(&img);
	
	return 0;
}