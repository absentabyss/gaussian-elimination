#include "utils.h"

int u_charAmount(int i) {
	int sign = 0;
	if (i < 0) {
		i *= -1;
		sign = 1;
	}
	int digitCount = 1;
	while (1) {
		if (i < 10)
			break;
		i /= 10;
		digitCount++;
	}
	return digitCount + sign;
}
