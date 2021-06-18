#ifndef UTILS_H
#define UTILS_H

extern const int INT_MAX;
extern const int INT_MIN;

void swapIfDescending(int* a, int* b);
int u_gcd(const int a, const int b);
int gcd(const int a, const int b);
int u_lcm(const int a, const int b);
int lcm(const int a, const int b);
int safeIntAdd(int* a, const int* b);
int safeIntMultiply(int* a, const int* b);

#endif
