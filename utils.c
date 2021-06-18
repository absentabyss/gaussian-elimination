#include "utils.h"

const int INT_MAX = (int)-1U/2 == (int)(-1U/2) ? (int)-1U : (int)(-1U/2);
const int INT_MIN = -INT_MAX - 1;

void swapIfDescending(int* a, int* b){
	if (a >= b)
		return;
	int* temp = a;
	a = b;
	b = temp;
}

int gcd(const int a, const int b) {
	// Euclidean algorithm for computing the greatest common divisor (GCD).
	if (a <= 0 || b <= 0)
		return 0;
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

int lcm(const int a, const int b) {
	if (a <= 0 || b <= 0 )
		return 0;
	return (a * b) / gcd(a, b);
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

int safeIntAdd(int* a, const int* b) {
	if (
		((*b > 0) && (*a > INT_MAX - *b)) ||
		((*b < 0) && (*a < INT_MIN - *b))
	)
		return -1;
	*a += *b;
	return 0;
}

int safeIntMultiply(int* a, const int* b) {
	if (
		((*a == -1) && (*b == INT_MIN)) ||
		((*b == -1) && (*a == INT_MIN)) ||
		(*a > INT_MAX / *b) ||
		(*a < INT_MIN / *b)
	)
		return -1;
	*a *= *b;
	return 0;
}
