#include "gaussian.h"
#include "frac.h"

#include <stdio.h>

size_t u_fracMatrixRowFirstNonNullIndex(FracMatrix* m, size_t row) {
	/* Returns the index of the first non-null element in a specified FracMatrix
	 * row.
	 */
	for (size_t j = 0; j < (*m).cols; ++j) {
		if (!u_fracEqual(&(*m).data[row][j], &fracZero))
			return j;
	}
	return (size_t)-1;
}

void u_fracMatrixReduceRow(FracMatrix* m, size_t row, size_t col) {
	/* Multiplies every fraction in a row by a scalar such that the first
	 * non-null element of the row is 1.
	 */
	Frac factor = u_fracInverse(&(*m).data[row][col]);
	for (size_t j = col; j < (*m).cols; ++j) {
		(*m).data[row][j] = u_fracMultiply(&(*m).data[row][j], &factor);
	}
}

void u_fracMatrixReduceCol(FracMatrix* m, size_t row, size_t col) {
	/* Applies the third elementary row operation on all the rows of the matrix
	 * so that there is only one unitary fraction in the column specified by col
	 * and all other elements in that column are null.
	 */
	for (size_t i = 0; i < (*m).rows; ++i) {
		if (i == row)
			continue;
		Frac scalar = u_fracNegative(&(*m).data[i][col]);
		u_fracMatrixAddRowMultiple(m, i, row, &scalar);
	}
}

void u_fracMatrixReduceByRows(FracMatrix* m) {
	for (size_t i = 0; i < (*m).rows; ++i) {
		size_t index = u_fracMatrixRowFirstNonNullIndex(m, i);
		if (index == (size_t)-1)
			continue;
		u_fracMatrixReduceRow(m, i, index);
		u_fracMatrixReduceCol(m, i, index);
	}
}

/* A pairArray is an array in which odd indexed elements are paired with the
 * neighboring lower element.
 *
 * It is used to label each row of a matrix with the position of its first
 * non-null element so as to sort the rows to have them in echelon form.
 *
 * Hoare's quicksort is used to sort the pairArray.
 */
void u_pairArraySwapRows(size_t* array, size_t i, size_t j) {
	size_t tmp[2] = {array[2 * i], array[(2 * i) + 1]};
	array[2 * i] = array[2 * j];
	array[(2 * i) + 1] = array[(2 * j) + 1];
	array[2 * j] = tmp[0];
	array[(2 * j) + 1] = tmp[1];
}

size_t u_pairArrayQuicksortPartition(size_t* array, size_t lo, size_t hi) {
	// Hoare's partition scheme for pairArrays.
	size_t pivot = array[((hi + lo) / 2) * 2 + 1];
	size_t i = lo - 1;
	size_t j = hi + 1;
	while (1)
	{
		do {
			++i;
		} while (array[2 * i + 1] < pivot);
		do {
			--j;
		} while (array[2 * j + 1] > pivot);
		if (i >= j) {
			return j;
		}
		u_pairArraySwapRows(array, i, j);
	}
}

void u_pairArrayQuicksort(size_t* array, size_t lo, size_t hi) {
	if (lo >= hi)
		return;
	size_t pivot = u_pairArrayQuicksortPartition(array, lo, hi);
	u_pairArrayQuicksort(array, lo, pivot);
	u_pairArrayQuicksort(array, pivot + 1, hi);
}

void u_pairArraySort(size_t* array, size_t size) {
	/* This function is meant to modularize the code so that any other pairArray
	 * sorting algorithm can be implemented.
	 */
	u_pairArrayQuicksort(array, 0, size);
}

void u_fracMatrixConvertToEchelon(FracMatrix* m) {
	/* Creates an "pairArray" that indexes each row in the FracMatrix with the index
	 * of its corresponding first non-null element.
	 *
	 * Then the pairArray is sorted instead of the entire matrix so as to
	 * minimize matrix row swaps which might be costly.
	 *
	 * A new matrix is created using the original matrix and the sorted array to
	 * end up with a matrix in echelon form.
	 */
	size_t firstPosArray[2 * (*m).rows];
	for (size_t i = 0; i < (*m).rows; ++i) {
		firstPosArray[2 * i] = i;
		int firstNonNull = u_fracMatrixRowFirstNonNullIndex(m, i);
		if (firstNonNull == -1) {
			firstPosArray[(2 * i) + 1] = (*m).cols;
			continue;
		}
		firstPosArray[(2 * i) + 1] = (size_t)u_fracMatrixRowFirstNonNullIndex(m, i);
	}
	u_pairArraySort(firstPosArray, (*m).rows);

	u_fracMatrixCreate((*m).rows, (*m).cols);
	FracMatrix tmp = u_fracMatrixCreate((*m).rows, (*m).cols);
	for (size_t i = 0; i < (*m).rows; ++i) {
		u_fracMatrixAddRow(&tmp, i, (*m).data[firstPosArray[2 * i]], (*m).cols);
	}

	Frac** dataOld = (*m).data;	
	(*m).data = tmp.data;
	for (size_t i = 0; i < (*m).rows; ++i) {
		free(dataOld[i]);
	}
	free(dataOld);
}

int u_fracMatrixGaussianElimination(FracMatrix* m) {
	u_fracMatrixReduceByRows(m);
	u_fracMatrixConvertToEchelon(m);
	return 0;
}
