#include "stdio.h"
#include <math.h>
#include <stdlib.h>
#include "MatrixMul.h"
#include "omp.h"

// Performs a naive multiplication of A * B (which is O(n^3)).
// If A and B are N x M and M x P respectively, the result will be an N x P matrix
// nb: N x M signifies a matrix with N rows and M columns

matrix2d* multiplyMatrices(matrix2d* A, matrix2d* B) {
	/*if(A->cols != B->rows){
		 return NULL;
		 }*/

		matrix2d* C;
		C = malloc(sizeof(matrix2d));

		int rows = A->rows;
		int cols = B->cols;
		C->data = malloc(sizeof(basetype*) * rows);

	#pragma offload target(mic:MIC_DEV) in(A:length(rows*A->cols)) \
	 in( B:length(B->rows*cols)) \
	out(C:length(rows*cols))
#pragma omp parallel
		{

			// Initialize matrix rows
			C->rows = rows;
			C->cols = cols;

			int r = 0;
			for (; r < rows; r++) {
				// Initialize matrix columns
				C->data[r] = malloc(sizeof(basetype) * cols);
				int c = 0;
				for (; c < cols; c++) {
					basetype item = 0;
					// Determine product of A's row and B's col
					int i = 0;
					for (; i < A->cols; i++) {
						item += A->data[r][i] * B->data[i][c];
					}
					// Assign to matrix
					C->data[r][c] = item;
				}
			}
		}

		return C;
}

matrix2d* loadMatrixFile(char* file) {
	FILE *fp;
	fp = fopen(file, "r");

	// Initialize matrix
	matrix2d* final;
	final = malloc(sizeof(matrix2d));

	if (fp == NULL) {
		//fprintf(stderr, "Can't open input file %s\n", file);
		exit(1);
	}

	int rows, cols;
	if (fscanf(fp, "%d %d", &rows, &cols) != EOF) {
		//printf("Reading %d x %d\n", rows, cols);

		// Initialize matrix rows
		final->rows = rows;
		final->cols = cols;
		final->data = malloc(sizeof(basetype*) * rows);

		int r = 0;
		int c = 0;
		//	for(; c < cols; c++){
		//		printf("\t[][%d]", c);
		//	}
		//	printf("\n");
		for (; r < rows; r++) {
			c = 0;
			//printf("[%d][]", r);

			// Initialize matrix columns
			final->data[r] = malloc(sizeof(basetype) * cols);
			for (; c < cols; c++) {
				basetype item = 0;
				if (fscanf(fp, basetypeprint, &item) == EOF) {
					printf("Unexpected EOF while reading at [%d][%d]\n", r, c);
					break;
				}
				// Assign to matrix
				final->data[r][c] = item;
				//printf("\t%d", final->data[r][c]);
			}
			//printf("\n");
		}
		//printf("\n");
	} else {
		printf("Couldn't get rows and columns");
	}

	fclose(fp);
	return final;
}

matrix2d* createMatrix(int rows, int cols) {
	matrix2d* final = malloc(sizeof(matrix2d));
	final->rows = rows;
	final->cols = cols;
	final->data = malloc(sizeof(basetype*) * rows);

	int r = 0;

#pragma omp parallel

	for (; r < rows; r++) {
		final->data[r] = malloc(sizeof(basetype) * cols);
		// done initializing here, this is just to clear everything to 0
		int c = 0;
		for (; c < cols; c++) {
			final->data[r][c] = 0;
		}
	}

	return final;
}

void randomizeMatrix(matrix2d* mat) {

	int r = 0;
	for (; r < mat->rows; r++) {
		int c = 0;
		for (; c < mat->cols; c++) {
			mat->data[r][c] = rand() % 100;
		}
	}
}

void printMatrix_simple(matrix2d* mat) {
	int maxRows = 20;
	int maxCols = 10;
	int r = 0;
	int c = 0;

	if (!mat) {
		printf("<null>\n\n");
		return;
	}

	for (; c < mat->cols; c++) {
		printf("\t[%d]", c);
		if(c >= maxCols){
			break;
		}
	}
	printf("\n");

	for (; r < mat->rows; r++) {
		printf("[%d]", r);
		for (c = 0; c < mat->cols; c++) {
			if (c >= maxCols) {
				if(r >= maxRows) {
					printf("\t...");
				} else {
					printf("\t...");
				}
				break;
			} else if(r >= maxRows) {
				printf("\t...");
			} else {
				printf("\t%d", mat->data[r][c]);
			}
		}

		if (r == 0) {
			printf("\t%d x %d", mat->rows, mat->cols);
		} else if (r == 1) {
			printf("\t(%d elements)", mat->rows * mat->cols);
		}
		printf("\n");
		
		if (r >= maxRows) {
			break;
		}
	}
	printf("\n");
}

void printMatrix_compact(matrix2d* mat) {
	printf("{");
	int r = 0;
	for (; r < mat->rows; r++) {
		if (r > 0) {
			printf(",");
		}
		printf("{");
		int c = 0;
		for (; c < mat->cols; c++) {
			if (c > 0) {
				printf(",");
			}
			printf("%d", mat->data[r][c]);
		}
		printf("}");
	}
	printf("}\n");
}

void printMatrix(matrix2d* mat, char format) {
	if (!mat) {
		printf("<null>\n\n");
		return;
	}

	if (format == 'c') {
		printMatrix_compact(mat);
	} else {
		printMatrix_simple(mat);
	}
}

void deleteMatrix(matrix2d* mat) {
	if (!mat)
		return;

	//printMatrix(mat);
	//printf("Freeing matrix\n");
	int r = 0;

	for (; r < mat->rows; r++) {
		//printf("\t[%d]/%d\n", r, mat->rows);
		if (mat->data[r]) {
			free(mat->data[r]);
		} else {
			//printf("was null\n");
		}
	}
	//printf("\tmat->data\n");
	free(mat->data);
	//printf("\tmat\n");
	free(mat);

}
