#include <opencv2/opencv.hpp>


CvScalar gammaCorrection(CvScalar in, float gamma) {
	CvScalar out;

	for (int k = 0; k < 3; k++)
	{
		out.val[k] = pow(in.val[k] / 255.0f, gamma);	//seung 
		out.val[k] = out.val[k] * 255.0f;
	}
	return out;
}

int main() {
	IplImage* src = cvLoadImage("c:\\temp\\lena.jpeg");
	CvSize size = cvGetSize(src);
	IplImage* dst = cvCreateImage(size, 8, 3);

	float gamma = 1.0f;
	int w = size.width;
	int h = size.height;

	while(true){
		for (int y = 0; y < h; y++)
			for (int x = 0; x < w; x++) {
				CvScalar f = cvGet2D(src, y, x);			//input color
				CvScalar g = gammaCorrection(f, gamma);			//output color

				cvSet2D(dst, y, x, g);
			}

		cvShowImage("src", src);
		cvShowImage("dst", dst);


		int key= cvWaitKey();
		if (key == '1')gamma += 0.1f;
		else if (key == '2')gamma -= 0.1f;
		else if (key == 'q')break;
		printf("gamma = %f \n", gamma);
		//up gamma -> dark
		//down gamma ->bright
	}
	// Image Proessing - 1. Image Filtering

	return 0;
}