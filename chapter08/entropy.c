/*
 * entropy.c -- Chapter 8, Exercise 2
 *
 * Compute the entropy H = -sum p_i log2 p_i of a source given its
 * probability distribution. Entropy is the minimum average number
 * of bits per symbol any lossless code can achieve.
 */

#include <stdio.h>
#include <math.h>

static double entropy(const double *p, int n)
{
    double h = 0.0;
    int i;
    for (i = 0; i < n; i++) {
        if (p[i] > 0.0)
            h -= p[i] * log2(p[i]);
    }
    return h;
}

int main(void)
{
    /* The skewed distribution typical of quantized coefficients. */
    double p[] = {0.70, 0.15, 0.10, 0.05};
    int n = (int)(sizeof(p) / sizeof(p[0]));

    double sum = 0.0;
    int i;
    for (i = 0; i < n; i++)
        sum += p[i];

    if (fabs(sum - 1.0) > 1e-6)
        fprintf(stderr, "warning: probabilities sum to %.4f\n", sum);

    printf("entropy H = %.4f bits/symbol\n", entropy(p, n));
    printf("(a fixed-length code would need %d bits/symbol)\n",
           (int)ceil(log2((double)n)));
    return 0;
}
