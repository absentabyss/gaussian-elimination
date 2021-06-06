#include "gaussian.h"
#include "frac.h"

#include <stdio.h>

size_t u_fracMatrixRowFirstNonNullIndex(FracMatrix* m, size_t row) {
	for (size_t j = 0; j < (*m).cols; ++j) {
		if (!u_fracEqual(&(*m).data[row][j], &fracZero))
			return j;
	}
	return (size_t)-1;
}

void u_fracMatrixReduceRow(FracMatrix* m, size_t row, size_t col) {
	Frac factor = u_fracInverse(&(*m).data[row][col]);
	for (size_t j = col; j < (*m).cols; ++j) {
		(*m).data[row][j] = u_fracMultiply(&(*m).data[row][j], &factor);
	}
}

void u_fracMatrixReduceCol(FracMatrix* m, size_t row, size_t col) {
	for (size_t i = 0; i < (*m).rows; ++i) {
		if (i == row)
			continue;
		Frac scalar = u_fracNegative(&(*m).data[i][col]);
		u_fracMatrixElem2(m, i, row, scalar);
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

void u_pairArraySwapRows(size_t* array, size_t i, size_t j) {
	size_t tmp[2] = {array[2 * i], array[(2 * i) + 1]};
	array[2 * i] = array[2 * j];
	array[(2 * i) + 1] = array[(2 * j) + 1];
	array[2 * j] = tmp[0];
	array[(2 * j) + 1] = tmp[1];
}

size_t u_pairArrayQuicksortPartition(size_t* array, size_t lo, size_t hi) {
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
	u_pairArrayQuicksort(array, 0, size);
}

void u_fracMatrixConvertToEchelon(FracMatrix* m) {
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
