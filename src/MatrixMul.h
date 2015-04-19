/*
 * MatrixMul.h
 *
 *  Created on: Apr 8, 2015
 *      Author: pnookala
 */

#ifndef MATRIXMUL_H_
#define MATRIXMUL_H_
#endif 

#ifndef MIC_DEV
#define MIC_DEV 0
#endif

#define basetype int
#define basetypeprint "%d"

__attribute__ ((target(mic))) typedef struct matrix2d {
	basetype** data;
	int rows;
	int cols;
} matrix2d;

/*matrix2d* loadMatrixFile(char* file);
matrix2d* createMatrix(int rows, int cols);
void randomizeMatrix(matrix2d* mat);
matrix2d* multiplyMatrices(matrix2d* A, matrix2d* B);
void printMatrix(matrix2d* mat, char format);
void deleteMatrix(matrix2d* mat);
*/
__attribute__ ((target(mic))) matrix2d* loadMatrixFile(char* file);
__attribute__ ((target(mic))) matrix2d* createMatrix(int rows, int cols);
__attribute__ ((target(mic))) void randomizeMatrix(matrix2d* mat);
__attribute__ ((target(mic))) matrix2d* multiplyMatrices(matrix2d* A, matrix2d* B);
__attribute__ ((target(mic))) void printMatrix(matrix2d* mat, char format);
__attribute__ ((target(mic))) void deleteMatrix(matrix2d* mat);
__attribute__ ((target(mic))) void printMatrix_compact(matrix2d* mat);
__attribute__ ((target(mic))) void printMatrix_simple(matrix2d* mat);
