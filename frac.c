#include "frac.h"
#include "utils.h"

#include <stdio.h>

// Some privileged fractions.
const Frac fracZero = {0, 1};
const Frac fracOne = {1, 1};

Frac itof(int i) { 			// Converts integers to fractions with denominator 1.
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
	/* Reducing a fraction requires dividing both the numerator and denominator by
	 * their greatest common divisor (GCD).
	 */
	int scalar = u_gcd((*f).numerator, (*f).denominator);
	(*f).numerator /= scalar;								// GCD guarantees result of division is integer.
	(*f).denominator /= scalar;
	if ((*f).denominator >= 0)								// Ensures the sign goes on the numerator.
		return;
	(*f).numerator *= -1;
	(*f).denominator *= -1;
}

int u_fracEqual(const Frac* fa, const Frac* fb) {
	// Fractions are first reduced to compare their terms.
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
	/* To add two fractions their denominators have to match. To do so, they are
	 * expanded to have the least common multiple (LCM) of the denominators, as a
	 * denominator. Then their numerators are added classically and then the
	 * resulting fraction is reduced.
	 */
	int denominatorLcm = u_lcm((*fa).denominator, (*fb).denominator);
	int faNumeratorExpanded = (*fa).numerator * (denominatorLcm / (*fa).denominator); // LCM guarantees result of division is integer.
	int fbNumeratorExpanded = (*fb).numerator * (denominatorLcm / (*fb).denominator);
	Frac result = {
		faNumeratorExpanded + fbNumeratorExpanded,
		denominatorLcm
	};
	u_fracReduce(&result);
	return result;
}

Frac u_fracSubtract(const Frac* fa, const Frac* fb) {
	// Analogous process as fracAdd.
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
	// Fractions are multiplied term by term.
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
