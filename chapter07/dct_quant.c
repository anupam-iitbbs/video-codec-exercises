/*
 * dct_quant.c  --  Chapter 7: Quantization
 *
 * Transform, then quantize. Apply the 1D DCT-II to an 8-point signal,
 * quantize the coefficients with a uniform step size, and count how
 * many coefficients collapse to zero. This is the core of why
 * transform coding compresses.
 *
 * Build: gcc -O2 -o dct_quant dct_quant.c -lm
 */

#include <stdio.h>
#include <math.h>

#define N 8

void dct_1d(const double *x, double *X) {
    for (int k = 0; k < N; k++) {
        double sum = 0.0;
        for (int n = 0; n < N; n++)
            sum += x[n] * cos(M_PI * (2*n + 1) * k / (2.0 * N));
        double alpha = (k == 0) ? sqrt(1.0/N) : sqrt(2.0/N);
        X[k] = alpha * sum;
    }
}

int main(void) {
    double x[N] = {52, 55, 61, 66, 70, 61, 64, 73};
    double X[N];
    double delta = 10.0;

    dct_1d(x, X);

    int zeros = 0;
    printf("%4s %10s %6s\n", "k", "coeff", "q");
    for (int k = 0; k < N; k++) {
        int q = (int)lround(X[k] / delta);
        if (q == 0) zeros++;
        printf("%4d %10.2f %6d\n", k, X[k], q);
    }
    printf("\nStep size = %.1f, zeros created = %d of %d\n", delta, zeros, N);
    return 0;
}
