#ifndef FRAC_H
#define FRAC_H

typedef struct {
	int numerator;
	int denominator;
} Frac;

extern const Frac fracZero;
extern const Frac fracOne;
extern const Frac fracError;
Frac itof(int i);
void fracPrint(const Frac* f);
void u_fracReduce(Frac* f);
int u_fracEqual(const Frac* fa, const Frac* fb);
Frac u_fracAdd(const Frac* fa, const Frac* fb);
Frac u_fracSubtract(const Frac* fa, const Frac* fb);
Frac u_fracMultiply(const Frac* fa, const Frac* fb);
Frac u_fracInverse(const Frac* f);
Frac u_fracNegative(const Frac* f);

#endif
