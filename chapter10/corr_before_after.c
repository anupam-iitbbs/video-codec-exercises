/* corr_before_after.c -- Chapter 10: correlation before vs after prediction.
 *
 * Measures the horizontal correlation of adjacent samples in the
 * original signal, then in the one-step prediction residual. The
 * original is highly correlated (rho ~ 0.95); the residual is almost
 * uncorrelated (rho ~ 0), because prediction has already removed the
 * redundancy. This is the whole point of predictive coding.
 *
 * Build:  cc -O2 -o corr_before_after corr_before_after.c
 */
#include <stdio.h>
#include <math.h>

/* Correlation of a[i] with a[i+1] over a length-n array. */
static double adjacent_corr(const double *a, int n) {
    double sx = 0, sy = 0, sxx = 0, syy = 0, sxy = 0;
    int m = n - 1;
    for (int i = 0; i < m; ++i) {
        double x = a[i], y = a[i + 1];
        sx += x; sy += y; sxx += x * x; syy += y * y; sxy += x * y;
    }
    double cov = sxy / m - (sx / m) * (sy / m);
    double vx  = sxx / m - (sx / m) * (sx / m);
    double vy  = syy / m - (sy / m) * (sy / m);
    if (vx <= 0 || vy <= 0) return 0.0;
    return cov / sqrt(vx * vy);
}

int main(void) {
    /* A smooth, slowly varying row -- strongly correlated. */
    double x[] = {100,101,102,104,105,107,108,110,
                  111,112,114,115,116,118,119,120};
    int n = sizeof(x) / sizeof(x[0]);

    /* One-step prediction residual e[i] = x[i] - x[i-1]. */
    double e[16];
    e[0] = 0.0;
    for (int i = 1; i < n; ++i) e[i] = x[i] - x[i - 1];

    printf("correlation of original samples : %.4f\n", adjacent_corr(x, n));
    printf("correlation of residual samples : %.4f\n", adjacent_corr(e + 1, n - 1));
    printf("(prediction removes the correlation -> residual ~ 0)\n");
    return 0;
}
