#include "fracmatrices.h"
#include "gaussian.h"

int main() {
	FracMatrix m = u_getFracMatrixFromCSV();
	u_fracMatrixGaussianElimination(&m);
	u_fracMatrixToCSV(&m);
	fracMatrixDestroy(&m);
	return 0;
}
