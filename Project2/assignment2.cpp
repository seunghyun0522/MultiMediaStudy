#include<opencv2\opencv.hpp>
#include<math.h>

#define PI 3.141592

void DrawSin(IplImage* img, CvSize size, CvScalar color, float freq)
{
	float midx = size.width / 2;
	float midy = size.height / 2;
	for (float x = 0; x < 250; x++)
	{
		double y = 125 * sin(x * PI / 120 * freq) + 125;
		y = 250 - y;
		cvSet2D(img, y, x, color);
	}
}

void setSin(IplImage* src, IplImage* dst, float freq)
{
	CvSize size = cvGetSize(src);
	for (int y = 0; y < size.height; y++)
	{
		for (int x = 0; x < size.width; x++)
		{
			CvScalar color = cvGet2D(src, y, x);
			CvScalar clr;
			clr.val[0] = 125 * sin(color.val[0] * PI / 120 * freq) + 125;
			clr.val[1] = 125 * sin(color.val[1] * PI / 120 * freq) + 125;
			clr.val[2] = 125 * sin(color.val[2] * PI / 120 * freq) + 125;
			cvSet2D(dst, y, x, clr);
		}
	}
}

void Sinprint()
{
	printf("\n=============================================\n");
	printf("Sinusoidal Function\n");
	printf("Press following keys!\n");
	printf("   1 : increasing frequency\n");
	printf("   2 : decreasing frequency\n");
	printf("   Q : quit the program\n");
	printf("=============================================\n");
}

void inputSinusoidal(IplImage* src, IplImage* dst, IplImage* draw, CvSize size, CvScalar black, CvScalar ground)
{
	double freq = 1;
	DrawSin(draw, size, black, freq);
	setSin(src, dst, freq);
	Sinprint();
	cvShowImage("Image", dst);
	cvShowImage("Graph", draw);
	int key = cvWaitKey();
	while (true)
	{
		if (key == '1') freq += 0.5;
		else if (key == '2')
		{
			freq -= 0.5;
			if (freq < 0.5)
				freq = 0.5;
		}
		else if (key == 'q') break;
		cvSet(draw, ground);
		DrawSin(draw, size, black, freq);
		setSin(src, dst, freq);
		printf("Current Freq. = %f\n", freq);
		cvShowImage("Image", dst);
		cvShowImage("Graph", draw);
		key = cvWaitKey();
	}
}

void DrawGamma(IplImage* img, CvSize size, CvScalar color, float gamma)
{
	for (float x = 0; x <= 250; x++)
	{
		double y = pow(x / 255, gamma) * 255;
		y = 250 - y;
		if (y < 0 || y>250) break;
		cvSet2D(img, y, x, color);
	}
}

void setGamma(IplImage* src, IplImage* dst, float gamma)
{
	CvSize size = cvGetSize(src);
	for (int y = 0; y < size.height; y++)
	{
		for (int x = 0; x < size.width; x++)
		{
			CvScalar color = cvGet2D(src, y, x);
			CvScalar clr;
			clr.val[0] = pow(color.val[0] / 225, double(gamma)) * 225;
			clr.val[1] = pow(color.val[1] / 225, double(gamma)) * 225;
			clr.val[2] = pow(color.val[2] / 225, double(gamma)) * 225;
			cvSet2D(dst, y, x, clr);
		}
	}
}

void Gammaprint()
{
	printf("\n=============================================\n");
	printf("Gamma Function\n");
	printf("Press following keys!\n");
	printf("   1 : increasing Gamma by 0.1\n");
	printf("   2 : decreasing Gamma by 0.1\n");
	printf("   Q : quit the program\n");
	printf("=============================================\n");
}

void inputGamma(IplImage* src, IplImage* dst, IplImage* draw, CvSize size, CvScalar black, CvScalar ground)
{
	double gamma = 1;
	DrawGamma(draw, size, black, gamma);
	setGamma(src, dst, gamma);
	Gammaprint();
	cvShowImage("Image", dst);
	cvShowImage("Graph", draw);
	int key = cvWaitKey();
	while (true)
	{
		if (key == '1') gamma += 0.1;
		else if (key == '2')
		{
			gamma -= 0.1;
			if (gamma < 0)
				gamma = 0;
		}
		else if (key == 'q') break;
		cvSet(draw, ground);
		DrawGamma(draw, size, black, gamma);
		setGamma(src, dst, gamma);
		printf("Current Gamma = %f\n", gamma);
		cvShowImage("Image", dst);
		cvShowImage("Graph", draw);
		key = cvWaitKey();
	}
}

void Manualprint(CvScalar black, CvScalar ground)
{
	printf("=============================================\n");
	printf("Dept. of Digital Contents, Sejong University\n");
	printf("Multimedia Programming Homework #2\n");
	printf("Point Processing - Gamma Correction and more\n");
	printf("=============================================\n\n");

	char ar[30] = "";
	CvSize size = cvSize(251, 251);
	IplImage* src = cvCreateImage(size, 8, 3);
	while (true)
	{
		printf("Input File Path: ");
		scanf("%s", ar);
		IplImage* src = cvLoadImage(ar);
		if (src == NULL) printf("File not Found!\n");
		else break;
	}
	src = cvLoadImage(ar);
	CvSize imagesize = cvGetSize(src);
	IplImage* dst = cvCreateImage(imagesize, 8, 3);

	IplImage* draw = cvCreateImage(size, 8, 3);
	cvSet(draw, ground);
	printf("Select function (1=gamma, 2=sinusoidal):");
	int input;
	while (true)
	{
		scanf("%d", &input);
		if (input == 1)
		{
			inputGamma(src, dst, draw, size, black, ground);
			break;
		}
		else if (input == 2)
		{
			inputSinusoidal(src, dst, draw, size, black, ground);
			break;
		}
		else printf("Wrong function!\n");
	}
}

int main()
{
	CvScalar ground = cvScalar(255, 255, 255);
	CvScalar black = cvScalar(0, 0, 0);
	Manualprint(black, ground);
	return 0;
}
