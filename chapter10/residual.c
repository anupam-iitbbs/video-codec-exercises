/* residual.c -- Chapter 10: prediction residual and its variance.
 *
 * Predictor:  xhat[n] = x[n-1]
 * Residual:   e[n] = x[n] - xhat[n]
 *
 * The residual has far smaller variance than the original, which is
 * why it compresses better. This program prints both signals and
 * compares their variances.
 *
 * Build:  cc -O2 -o residual residual.c
 */
#include <stdio.h>

static double variance(const double *a, int n) {
    double m = 0;
    for (int i = 0; i < n; ++i) m += a[i];
    m /= n;
    double v = 0;
    for (int i = 0; i < n; ++i) { double d = a[i] - m; v += d * d; }
    return v / n;
}

int main(void) {
    double x[] = {100, 101, 102, 103, 104, 104, 105, 106};
    int n = sizeof(x) / sizeof(x[0]);

    double e[8];
    e[0] = x[0];                 /* seed: first sample stored as-is */
    for (int i = 1; i < n; ++i)
        e[i] = x[i] - x[i - 1];  /* residual */

    printf("original:");
    for (int i = 0; i < n; ++i) printf(" %g", x[i]);
    printf("\nresidual:");
    for (int i = 0; i < n; ++i) printf(" %g", e[i]);
    printf("\n");

    printf("var(original) = %.4f\n", variance(x, n));
    /* variance of residual ignoring the seed sample */
    printf("var(residual) = %.4f  (much smaller -> cheaper to code)\n",
           variance(e + 1, n - 1));
    return 0;
}
