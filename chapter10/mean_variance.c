/* mean_variance.c -- Chapter 10: mean (brightness) and variance (activity).
 *
 * mean     = (1/N) sum x_i
 * variance = (1/N) sum (x_i - mean)^2
 *
 * Build:  cc -O2 -o mean_variance mean_variance.c
 */
#include <stdio.h>

int main(void) {
    int x[] = {4, 6, 8, 10, 12};
    int n = sizeof(x) / sizeof(x[0]);

    double sum = 0.0;
    for (int i = 0; i < n; ++i) sum += x[i];
    double mean = sum / n;

    double sq = 0.0;
    for (int i = 0; i < n; ++i) {
        double d = x[i] - mean;
        sq += d * d;
    }
    double var = sq / n;

    printf("N        = %d\n", n);
    printf("mean     = %.4f  (average brightness)\n", mean);
    printf("variance = %.4f  (activity / texture)\n", var);
    return 0;
}
