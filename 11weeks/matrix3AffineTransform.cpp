#include<opencv2/opencv.hpp>

void setIdentity(float M[][3]) {

	M[0][0] = 1.0f;  M[0][1] = 0.0f; M[0][2] = 0.0f;
	M[1][0] = 0.0f; M[1][1] = 1.0f;	M[1][2] = 0.0f;
	M[2][0] = 0.0f; M[2][1] = 0.0f;	M[2][2] = 1.0f;
}

void setScale(float M[][3], float sx, float sy) {
	setIdentity(M);
	M[0][0] = sx;
	M[1][1] = sy;
}

void setRotation(float M[][3], float angle) {
	setIdentity(M);
	float rad = angle / 360.0f * 2 * 3.141592;
	M[0][0] = cos(rad);  M[0][1] = -sin(rad);
	M[1][0] = sin(rad); M[1][1] = cos(rad);
}

void setMultiply(float M[][3], float A[][3], float B[][3]) {
	/*
	M[0][0] = A[0][0] * B[0][0] + A[0][1] * B[1][0];
	M[0][1] = A[0][0] * B[0][1] + A[0][1] * B[1][1];
	M[1][0] = A[1][0] * B[0][0] + A[1][1] * B[1][0];
	M[1][1] = A[1][0] * B[0][1] + A[1][1] * B[1][1];
	*/

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			M[i][j] = 0.0f;
			for (int k = 0; k < 3; k++) {
				M[i][j] += A[i][k] * B[k][j];
			}
		}
}

void setInverse(float IM[][2], float M[][2]) {
	float a = M[0][0];
	float b = M[0][1];
	float c = M[1][0];
	float d = M[1][1];
	float det = a * d - b * c;

	IM[0][0] = d / det;	IM[0][1] = -b / det;
	IM[1][0] = -c / det; IM[1][1] = a / det;
}

void setTranslate(float M[][3], float tx, float ty) {
	setIdentity(M);
	M[0][2] = tx;
	M[1][2] = ty;
}

int main() {
	IplImage* src = cvLoadImage("c:\\temp\\lena.jpeg");
	CvSize size = cvSize(800, 800);
	IplImage* dst = cvCreateImage(size, 8, 3);

	cvSet(dst, cvScalar(0, 0, 0));


	float M[3][3], A[3][3], B[3][3],C[3][3],M1[3][3];

	// M[0][0] M[0][1]
	// M[1][0] M[1][1] 

	setIdentity(M);
	setScale(A, 1.5f, 0.5f);
	setRotation(B, 30);
	setTranslate(C, 100, 50);
	setMultiply(M1, B, A);	// M = A B
	setMultiply(M, C, M1);
	//역변형 구하기
	//float IM[2][2];
	//setInverse(IM, M);
	
	for(int y1 = 0; y1<src->height; y1++)
		for (int x1 = 0; x1 < src->width; x1++) {

		float w1=1.0f;
			float x2 = M[0][0]*x1 + M[0][1] * y1 + M[0][2]*w1;
			float y2 = M[1][0]*x1 + M[1][1] * y1 + M[1][2]*w1;
			float w2 = M[2][0] * x1 + M[2][1] * y1 + M[2][2] * w1;

			x2 /= w2;
			y2 /= w2;

			if (x2<0 || x2>dst->width - 1) continue;
			if (y2<0 || y2>dst->height - 1) continue;

			CvScalar f = cvGet2D(src, y1, x1);
			cvSet2D(dst, y2, x2, f);
		}

		
		//역변형을 통해서 점을 깨끗하게 출력하자!!
		//역행렬을 구해서 대입하기 
	/*
	for (int y2 = 0; y2 < dst->height; y2++)
		for (int x2 = 0; x2 < dst->width; x2++) {
			float x1 = IM[0][0] * x2 + IM[0][1] * y2;
			float y1 = IM[1][0] * x2 + IM[1][1] * y2;

			if (x1<0 || x1>src->width - 1) continue;
			if (y1<0 || y1>src->height - 1)continue;

			CvScalar f = cvGet2D(src, y1, x1);
			cvSet2D(dst, y2, x2, f);
		}
		*/
	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();
	return 0;
}
