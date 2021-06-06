#include "frac.h"
#include "lcm.h"

#include <stdio.h>

#define INT_MIN (unsigned int)-1/2+1

const Frac fracZero = {
	0,
	1
};

const Frac fracOne = {
	1,
	1
};

const Frac fracError = {
	INT_MIN,
	1
};

Frac itof(int i) { 	// Converts integers to fractions with denominator 1.
	return (Frac){i, 1};
}

void fracPrint(const Frac* f) {
	if ((*f).denominator == 1) {
		printf("%d\n", (*f).numerator);
		return;
	}
	printf("%d/%d\n", (*f).numerator, (*f).denominator);
}

void u_fracReduce(Frac* f) {
	int scalar = u_gcd((*f).numerator, (*f).denominator);
	(*f).numerator /= scalar;
	(*f).denominator /= scalar;
	if ((*f).denominator >= 0)
		return;
	(*f).numerator *= -1;
	(*f).denominator *= -1;
}

int u_fracEqual(const Frac* fa, const Frac* fb) {
	Frac faReduced = {
		(*fa).numerator,
		(*fa).denominator
	};
	u_fracReduce(&faReduced);
	Frac fbReduced = {
		(*fb).numerator,
		(*fb).denominator
	};
	u_fracReduce(&fbReduced);
	if (
		faReduced.numerator == fbReduced.numerator &&
		faReduced.denominator == fbReduced.denominator
	) return 1;
	return 0;
}

Frac u_fracAdd(const Frac* fa, const Frac* fb) {
	int denominatorLcm = u_lcm((*fa).denominator, (*fb).denominator);
	int faNumeratorExpanded = (*fa).numerator * (denominatorLcm / (*fa).denominator);
	int fbNumeratorExpanded = (*fb).numerator * (denominatorLcm / (*fb).denominator);
	Frac result = {
		faNumeratorExpanded + fbNumeratorExpanded,
		denominatorLcm
	};
	u_fracReduce(&result);
	return result;
}

Frac u_fracSubtract(const Frac* fa, const Frac* fb) {
	int denominatorLcm = u_lcm((*fa).denominator, (*fb).denominator);
	int faNumeratorExpanded = (*fa).numerator * (denominatorLcm / (*fa).denominator);
	int fbNumeratorExpanded = (*fb).numerator * (denominatorLcm / (*fb).denominator);
	Frac result = {
		faNumeratorExpanded - fbNumeratorExpanded,
		denominatorLcm
	};
	u_fracReduce(&result);
	return result;
}

Frac u_fracMultiply(const Frac* fa, const Frac* fb) {
	Frac result = {
		(*fa).numerator * (*fb).numerator,
		(*fa).denominator * (*fb).denominator,
	};
	u_fracReduce(&result);
	return result;
}

Frac u_fracInverse(const Frac* f) {
	return (Frac){(*f).denominator, (*f).numerator};
}

Frac u_fracNegative(const Frac* f) {
	return (Frac){-(*f).numerator, (*f).denominator};
}
