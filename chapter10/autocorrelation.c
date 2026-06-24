/* autocorrelation.c -- Chapter 10: autocorrelation of a 1-D signal.
 *
 * R[k] = (1/N) sum_n x[n] * x[n-k]   (here normalized so R[0] = 1)
 *
 * For natural signals R[k] decays slowly with k: a sample resembles
 * neighbors several steps away. For noise it collapses immediately.
 *
 * Build:  cc -O2 -o autocorrelation autocorrelation.c
 */
#include <stdio.h>

int main(void) {
    /* A smooth, slowly varying row (mean removed for clarity). */
    double x[] = {-4, -3, -2, -1, 0, 1, 2, 3, 2, 1, 0, -1, -2, -3};
    int n = sizeof(x) / sizeof(x[0]);

    double r0 = 0;
    for (int i = 0; i < n; ++i) r0 += x[i] * x[i];
    r0 /= n;

    printf("shift k   R[k] (normalized)\n");
    for (int k = 0; k < 8; ++k) {
        double r = 0;
        for (int i = k; i < n; ++i) r += x[i] * x[i - k];
        r /= n;
        printf("%5d     %7.4f\n", k, r / r0);
    }
    printf("(slow decay = strong structure; fast decay = noise)\n");
    return 0;
}
