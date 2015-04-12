/*
 * MatrixMul.h
 *
 *  Created on: Apr 8, 2015
 *      Author: pnookala
 */

#ifndef MATRIXMUL_H_
#define MATRIXMUL_H_

#define basetype int
#define basetypeprint "%d"

typedef struct matrix2d {
	basetype** data;
	int rows;
	int cols;
} matrix2d;

matrix2d* loadMatrixFile(char* file);
matrix2d* createMatrix(int rows, int cols);
void randomizeMatrix(matrix2d* mat);
matrix2d* multiplyMatrices(matrix2d* A, matrix2d* B);
void printMatrix(matrix2d* mat, char format);
void deleteMatrix(matrix2d* mat);

#endif /* MATRIXMUL_H_ */
