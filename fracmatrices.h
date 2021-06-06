#ifndef FRACMATRICES_H
#define FRACMATRICES_H

#include "frac.h"

#include <stdlib.h>

typedef struct {
	size_t rows;
	size_t cols;
	Frac** data;
} FracMatrix;

FracMatrix u_fracMatrixCreate(size_t height, size_t width);
void fracMatrixDestroy(FracMatrix* m);

int u_fracMatrixAddRow(FracMatrix* m, size_t row, const Frac* fracArray, size_t length);

FracMatrix u_getFracMatrixFromCSV();
int u_readCSVAsFracMatrix(Frac* f, size_t f_size, size_t* rows, size_t* cols);	// Frac* f must be in heap.
void u_fracMatrixToCSV(const FracMatrix* m);

// Elementary row operations.
int u_fracMatrixSwapRows(FracMatrix* m, size_t rowa, size_t rowb);
int u_fracMatrixMultiplyRowByScalar(FracMatrix* m, size_t row, const Frac* scalar);
int u_fracMatrixAddRowMultiple(FracMatrix* m, size_t rowa, size_t rowb, const Frac* scalar);

void u_fracMatrixFillWithFracArray(FracMatrix* m, const Frac* f, const size_t rows, const size_t cols);
void u_fracMatrixPrint(const FracMatrix* m);
void u_fracMatrixReduceFracs(FracMatrix* m);

#endif
