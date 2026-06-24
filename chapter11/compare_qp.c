/* compare_qp.c -- Chapter 11: compare two quantization parameters.
 *
 * A small QP keeps precision: high rate, low distortion.
 * A large QP rounds harshly: low rate, high distortion.
 * Choosing QP is choosing a point on the rate-distortion curve.
 *
 * Build:  cc -O2 -o compare_qp compare_qp.c
 */
#include <stdio.h>
#include <stdlib.h>

#define N 8

/* Quantize, dequantize, and measure rate (nonzero count) and
   distortion (sum of squared error) for a given step size. */
static void code_with_qp(const int *x, int n, int step,
                         long *rate_bits, double *distortion) {
    long nonzero = 0;
    double sse = 0.0;
    for (int i = 0; i < n; ++i) {
        int q  = (x[i] >= 0) ? (x[i] + step / 2) / step
                             : -((-x[i] + step / 2) / step);
        int xr = q * step;                 /* reconstructed value */
        if (q != 0) nonzero++;
        double e = x[i] - xr;
        sse += e * e;
    }
    /* Crude rate model: ~5 bits per surviving coefficient. */
    *rate_bits  = nonzero * 5;
    *distortion = sse;
}

int main(void) {
    int coeff[N] = {120, -45, 17, -8, 30, -3, 6, -22};

    long r20, r40;
    double d20, d40;
    code_with_qp(coeff, N, 4,  &r20, &d20);   /* small step ~ QP 20 */
    code_with_qp(coeff, N, 32, &r40, &d40);   /* large step ~ QP 40 */

    printf("QP-like step  rate(bits)  distortion(SSE)\n");
    printf("small (4)     %8ld     %10.1f\n", r20, d20);
    printf("large (32)    %8ld     %10.1f\n", r40, d40);
    printf("(small step: more bits, less distortion; large step: the reverse)\n");
    return 0;
}
