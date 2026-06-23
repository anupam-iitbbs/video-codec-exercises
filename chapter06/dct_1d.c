/*
 * dct_1d.c  -  Chapter 6, Exercise 2
 *
 * Compute the 1D DCT-II directly from its definition and show the
 * energy-compaction property: a smooth ramp collapses onto the
 * first couple of coefficients, while a step edge spreads out.
 *
 * Build: gcc -O2 -o dct_1d dct_1d.c -lm
 * Run:   ./dct_1d
 */

#include <stdio.h>
#include <math.h>

#define N 8
#define PI 3.14159265358979323846

static double alpha(int k)
{
    return (k == 0) ? sqrt(1.0 / N) : sqrt(2.0 / N);
}

static void dct_ii(const double *x, double *X)
{
    for (int k = 0; k < N; ++k) {
        double sum = 0.0;
        for (int n = 0; n < N; ++n)
            sum += x[n] * cos(PI * (2 * n + 1) * k / (2.0 * N));
        X[k] = alpha(k) * sum;
    }
}

static void show(const char *label, const double *x)
{
    double X[N];
    dct_ii(x, X);
    printf("%s\n  input  :", label);
    for (int n = 0; n < N; ++n) printf(" %6.1f", x[n]);
    printf("\n  coeffs :");
    for (int k = 0; k < N; ++k) printf(" %6.2f", X[k]);
    printf("\n\n");
}

int main(void)
{
    double ramp[N] = {10, 12, 14, 16, 18, 20, 22, 24};
    double step[N] = {10, 10, 10, 10, 60, 60, 60, 60};
    show("Smooth ramp (energy in first coeffs):", ramp);
    show("Step edge (energy spread out):", step);
    return 0;
}
