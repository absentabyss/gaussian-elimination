#include "utils.h"

void swapIfDescending(int* a, int* b){
	if (a >= b)
		return;
	int* temp = a;
	a = b;
	b = temp;
}

int u_gcd(const int a, const int b) {
	// Euclidean algorithm for computing the greatest common divisor (GCD).
	int hi = a;
	int lo = b;
	swapIfDescending(&hi, &lo);
	int temp;
	while (lo != 0) {
		temp = lo;
		lo = hi % lo;
		hi = temp;
	}
	return hi;
}

int u_lcm(const int a, const int b) {
	return (a * b) / u_gcd(a, b);
}
