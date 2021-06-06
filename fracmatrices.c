#include "fracmatrices.h"

#include <stdio.h>

FracMatrix u_fracMatrixCreate(size_t height, size_t width) {
	FracMatrix m = {
		height,
		width,
		(Frac**)malloc(height * sizeof(Frac*))
	};
	for (size_t i = 0; i < m.rows; ++i) {
		m.data[i] = (Frac*)malloc(width * sizeof(Frac));
	}
	return m;
}

void fracMatrixDestroy(FracMatrix* m) {
	for (size_t i = 0; i < (*m).rows; ++i) {
		free((*m).data[i]);
	}
	free((*m).data);
}

int u_fracMatrixAddRow(FracMatrix* m, size_t row, const Frac* fracArray, size_t length) {
	// Replaces all the values in `row` with those of the fracArray.
	if (length != (*m).cols)
		return -1;
	for (size_t j = 0; j < (*m).cols; ++j) {
		(*m).data[row][j] = fracArray[j];
	}
	return 0;
}

int u_fracMatrixSwapRows(FracMatrix* m, size_t rowa, size_t rowb) {
	// Elementary row operation 0.
	Frac* tmp = (*m).data[rowa];
	(*m).data[rowa] = (*m).data[rowb];
	(*m).data[rowb] = tmp;
	return 0;
}

int u_fracMatrixMultiplyRowByScalar(FracMatrix* m, size_t row, const Frac* scalar) {
	// Elementary row operation 1.
	for (size_t j = 0; j < (*m).cols; ++j)
		(*m).data[row][j] = u_fracMultiply(&(*m).data[row][j], scalar);
	return 0;
}

int u_fracMatrixAddRowMultiple(FracMatrix* m, size_t rowa, size_t rowb, const Frac* scalar) {
	// Elementary row operation 2.
	for (size_t j = 0; j < (*m).cols; ++j) {
		Frac rowbScaled = u_fracMultiply(&(*m).data[rowb][j], scalar);
		(*m).data[rowa][j] = u_fracAdd(&(*m).data[rowa][j], &rowbScaled);
	}
	return 0;
}

void u_fracMatrixPrint(const FracMatrix* m) {
	for (size_t i = 0; i < (*m).rows; ++i) {
		for (size_t j = 0; j < (*m).cols; ++j) {
			Frac f = (*m).data[i][j];
			if ((f).denominator == 1) {
				printf("%d ", (f).numerator);
				continue;
			}
			printf("%d/%d ", (f).numerator, (f).denominator);
		}
		printf("\n");
	}
}

void u_fracMatrixReduceFracs(FracMatrix* m) {
	for (size_t i = 0; i < (*m).rows; ++i) {
		for (size_t j = 0; j < (*m).cols; ++j) {
			u_fracReduce(&(*m).data[i][j]);
		}
	}
}

int u_readCSVAsFracMatrix(Frac* f, size_t f_size, size_t* rows, size_t* cols) {
	// Reads CSV from STDIN as a matrix.
	size_t row = 0;
	size_t col = 0;
	size_t maxWidth = (size_t)-1;
	while (1) {
		/* First scans for a value, then checks if the following character is a
		 * `,` or a `;`.
		 * `,`s increase the col value while `;`s increase the row value.
		 * It also checks that the same amount of `,` are between consecutive
		 * `;`s.
		 */
		int i, j;
		int scans = scanf("%d/%d", &i, &j);							// Should handle ints and floats.
		if (scans == 2) {											// Checks if a match was successful.
			size_t index = maxWidth * row + col;					// Note that this "flattens" a matrix to an array.
			if (col > maxWidth) {
				return -1;
			}
			if (index >= f_size) {
				f = (Frac*)realloc(f, sizeof(Frac) * f_size * 2);	// This assumes the pointer passed was allocated before. UB if it wasn't.
				f_size *= 2;
			}
			f[index] = (Frac){i, j};
			++col;
		} else {
			return -1;
		}

		char c = fgetc(stdin);										// Checks delimiting character.
		if (c == ';') {
			if (!row) {
				maxWidth = col;
			}
			if (col != maxWidth) {
				return -1;
			}
			++row;
			col = 0;
		} else if (c == ',') {
			continue;
		} else if (c == '\n') {										// This is an ugly way of terminating. :/
			if (!row) {												// It's a bit odd that this check is repeated. Maybe it can be refactored.
				maxWidth = col;
			}
			if (col != maxWidth) {
				return -1;
			}
			*cols = col;
			*rows = row + 1;
			return 0;
		}
		else {
			return -1;
		}
	}
}

void u_fracMatrixFillWithFracArray(FracMatrix* m, const Frac* f, const size_t rows, const size_t cols) {
	/* Fills FracMatrix with values from array. It probably SEGFAULTs if the
	 * size of f is smaller than rows * cols.
	 */
	*m = u_fracMatrixCreate(rows, cols);
	for (size_t i = 0; i < rows; ++i) {
		u_fracMatrixAddRow(m, i, &f[i * cols], cols);
	}
}

void u_fracMatrixToCSV(const FracMatrix* m) {
	// Outputs FracMatrix contents to STDOUT as CSV.
	for (size_t i = 0; i < (*m).rows; ++i) {
		for (size_t j = 0; j < (*m).cols; ++j) {
			printf("%d/%d", (*m).data[i][j].numerator, (*m).data[i][j].denominator);
			if (j == ((*m).cols - 1))
				printf(";\n");
			else
				printf(",");
		}
	}
}

FracMatrix u_getFracMatrixFromCSV() {
	size_t rows;
	size_t cols;

	size_t f_size = 64;
	Frac* f =  (Frac*)malloc(sizeof(Frac) * f_size);

	u_readCSVAsFracMatrix(f, f_size, &rows, &cols);		// This function requires Frac* f to be in heap as it uses realloc.

	FracMatrix m;
	u_fracMatrixFillWithFracArray(&m, f, rows, cols);
	free(f);
	u_fracMatrixReduceFracs(&m);

	return m;
}
