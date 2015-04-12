/*
 ============================================================================
 Name        : MIC_OpenMP.c
 Author      : Poornima Nookala
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#ifndef MIC_DEV
#define MIC_DEV 0

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "MatrixMul.h"
#include "omp.h"

#define basetype int
#define basetypeprint "%d"

int numThreads, numIterations;

void MatrixMultiplication();
void Sleep(int sleepTime);


int main(int argc, char *argv[]) {

	if (argc != 3) {
		/*fprintf(stderr, "Enter number of threads and iterations.\n");
		 return -1;*/
		argv[0] = "1";
		argv[1] = "1";
		argv[2] = "1";
		argv[3] = "5";
	}

	numThreads = atoi(argv[0]);
	numIterations = atoi(argv[1]);
	int jobType = atoi(argv[2]);
	int duration = atoi(argv[3]);

	switch (jobType) {
	case 1:
		Sleep(duration);
		break;
	case 2:
		MatrixMultiplication();
		break;
	}
}

void MatrixMultiplication()
{

	omp_set_num_threads(numThreads);

	int i, nt = 0;

	printf("Starting matrix multiplication\n");
	char* fileA = "matA";
	char* fileB = "matB";

	if (fileA == "") {
		printf("No file specified\n");
		return;
	} else {
		printf("Using file: '%s'\n", fileA);
	}

	matrix2d *A, *B, *C;
	A = loadMatrixFile(fileA);
	B = loadMatrixFile(fileB);

	printf("Matrix A:\n");
	printMatrix(A, 'd');
	printf("Matrix B:\n");
	printMatrix(B, 'd');
	//__Offload_report(2);
#pragma offload target(mic:MIC_DEV) in(A:length(rows*cols)) \
	 in(B:length(rows*cols)) \
	out(C:length(rows*cols))
#pragma omp parallel

	nt = omp_get_num_threads();

	/* warm up to overcome setup overhead */
	C = multiplyMatrices(A, B);
	double aveTime, minTime = 1e6, maxTime = 0.;
	struct timeval tvBegin, tvEnd, tvDiff;
	/*Run matrix multiplication numIterations times and calculate the average running time. */
	for (i = 0; i < numIterations; i++) {
		gettimeofday(&tvBegin, NULL);
		C = multiplyMatrices(A, B);

		printf("Product (C):\n");
		printMatrix(C, 'd');

		gettimeofday(&tvEnd, NULL);
		tvDiff.tv_sec = tvEnd.tv_sec - tvBegin.tv_sec;

		maxTime = (maxTime > tvDiff.tv_sec) ? maxTime : tvDiff.tv_sec;
		minTime = (minTime < tvDiff.tv_sec) ? minTime : tvDiff.tv_sec;
		aveTime += tvDiff.tv_sec;
	}
	aveTime /= numIterations;

	printf(
			"%d numThreads %d*%d matrix %d maxRT %g minRT %g aveRT %g GFlop/s %g\n",
			numThreads, nt, C->rows, C->cols, maxTime, minTime, aveTime,2e-9 * C->rows * C->cols * C->rows / aveTime);

	deleteMatrix(A);
	deleteMatrix(B);
	deleteMatrix(C);

	free(A);
	free(B);
	free(C);

	//__Offload_report(2);
	return;
}

void Sleep(int sleepTime)
{
	printf("Starting Sleep Jobs\n");

	int i;

#pragma offload target(mic:MIC_DEV)
#pragma omp parallel
	for (i = 0; i < numIterations; i++) {
		int dummy = 1;
		int threadId = omp_get_thread_num();
		printf("%d", threadId);

		struct timeval tvBegin, tvEnd, tvDiff;

		// begin
		gettimeofday(&tvBegin, NULL);

//		printf(tvBegin.tv_sec);

		gettimeofday(&tvEnd, NULL);
		if (sleepTime) {
			while ((int) (tvEnd.tv_sec - tvBegin.tv_sec) < sleepTime) {
				int i, j;
				for (i = 0; i < 10000000; ++i) {
					dummy *= 2;
				}

				gettimeofday(&tvEnd, NULL);

			}
		}

	//	printf(tvEnd.tv_sec);
	}
}

#endif
