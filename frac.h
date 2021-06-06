#ifndef FRAC_H
#define FRAC_H

typedef struct {
	int numerator;
	int denominator;
} Frac;

extern const Frac fracOne;
extern const Frac fracZero;

Frac itof(int i);
void fracPrint(const Frac* f);
void u_fracReduce(Frac* f);

Frac u_fracAdd(const Frac* fa, const Frac* fb);
Frac u_fracInverse(const Frac* f);
Frac u_fracMultiply(const Frac* fa, const Frac* fb);
Frac u_fracNegative(const Frac* f);
Frac u_fracSubtract(const Frac* fa, const Frac* fb);
int u_fracEqual(const Frac* fa, const Frac* fb);

#endif
