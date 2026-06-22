/*
 * quantize.c  --- Chapter 3, Exercise 2: Quantization
 *
 * Companion code for "From Signals to Video Codecs", Volume 1.
 *
 * Quantize a signal to a chosen bit depth and observe the distortion.
 * We quantize the SAME signal to 8, 4, and 2 bits and print the
 * resulting values together with the quantization error. As the bit
 * count falls, the staircase grows coarser and the error grows with it
 * --- this is the numerical face of banding (Section 3.9).
 *
 *     levels = 2^bits
 *     step   = (max - min) / (levels - 1)
 *     q(s)   = round((s - min) / step) * step + min
 *
 * Build:  gcc -O2 -Wall -o quantize quantize.c -lm
 * Run:    ./quantize
 */

#include <stdio.h>
#include <math.h>

#define N 16

/* Quantize one value to 'bits' bits across the range [lo, hi]. */
double quantize(double s, int bits, double lo, double hi)
{
    int levels = 1 << bits;            /* 2^bits */
    double step = (hi - lo) / (levels - 1);
    double q = round((s - lo) / step) * step + lo;
    return q;
}

int main(void)
{
    double x[N];
    double lo = -1.0, hi = 1.0;
    int depths[] = { 8, 4, 2 };

    /* A smooth ramp from lo to hi: easy to see banding on. */
    for (int n = 0; n < N; n++) {
        x[n] = lo + (hi - lo) * n / (N - 1);
    }

    for (int d = 0; d < 3; d++) {
        int bits = depths[d];
        double max_err = 0.0;
        printf("\n=== %d-bit quantization (%d levels) ===\n",
               bits, 1 << bits);
        printf("  n     x[n]      q[n]     error\n");
        for (int n = 0; n < N; n++) {
            double q = quantize(x[n], bits, lo, hi);
            double err = fabs(q - x[n]);
            if (err > max_err) max_err = err;
            printf("%3d  % .3f   % .3f   % .3f\n", n, x[n], q, err);
        }
        printf("  max error = %.3f\n", max_err);
    }

    printf("\nNotice how the error grows as the bit depth shrinks.\n");
    return 0;
}
