#ifndef GAUSSIAN_H
#define GAUSSIAN_H

#include "fracmatrices.h"

size_t u_fracMatrixRowFirstNonNullIndex(FracMatrix* m, size_t row);

void u_pairArraySwapRows(size_t* array, size_t i, size_t j);
size_t u_pairArrayQuicksortPartition(size_t* array, size_t lo, size_t hi);
void u_pairArrayQuicksort(size_t* array, size_t lo, size_t hi);
void u_pairArraySort(size_t* array, size_t size);

void u_fracMatrixReduceCol(FracMatrix* m, size_t row, size_t col);
void u_fracMatrixReduceRow(FracMatrix* m, size_t row, size_t col);

void u_fracMatrixReduceByRows(FracMatrix* m);
void u_fracMatrixConvertToEchelon(FracMatrix* m);
int u_fracMatrixGaussianElimination(FracMatrix* m);

#endif
