/* coeff_histogram.c -- Chapter 10: histogram of quantized DCT coefficients.
 *
 * After transforming and quantizing natural-image blocks, most
 * coefficients are zero or near zero. The histogram is a sharp peak
 * at zero with long thin tails -- a Laplacian shape. That is exactly
 * what entropy coding rewards.
 *
 * Build:  cc -O2 -o coeff_histogram coeff_histogram.c
 */
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    /* Stand-in for quantized coefficients from several blocks:
       overwhelmingly zeros, a few +/-1, rarely larger. */
    int coeff[] = {
        0,0,0,0,1,0,0,0,-1,0,0,0,0,2,0,0,
        0,0,0,-1,0,0,0,1,0,0,0,0,0,-3,0,0,
        0,0,1,0,0,0,0,0,0,-1,0,0,4,0,0,0
    };
    int n = sizeof(coeff) / sizeof(coeff[0]);

    int lo = -5, hi = 5;
    int hist[11] = {0};
    for (int i = 0; i < n; ++i) {
        int v = coeff[i];
        if (v < lo) v = lo;
        if (v > hi) v = hi;
        hist[v - lo]++;
    }

    printf("value  count  bar\n");
    for (int v = lo; v <= hi; ++v) {
        printf("%4d   %4d   ", v, hist[v - lo]);
        for (int b = 0; b < hist[v - lo]; ++b) putchar('#');
        putchar('\n');
    }
    printf("(sharp spike at 0 = Laplacian = cheap to entropy-code)\n");
    return 0;
}
