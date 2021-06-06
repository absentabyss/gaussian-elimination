#include "fracmatrices.h"
#include "gaussian.h"

int main() {
	FracMatrix m = u_getFracMatrixFromCSV();	// Reads CSV from STDIN into a FracMatrix.
	u_fracMatrixGaussianElimination(&m);
	u_fracMatrixToCSV(&m);						// Outputs FracMatrix contents to STDOUT as CSV.
	fracMatrixDestroy(&m);
	return 0;
}
