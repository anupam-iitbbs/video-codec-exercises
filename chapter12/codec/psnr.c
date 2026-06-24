/*
 * psnr.c -- mean squared error and peak signal-to-noise ratio.
 *
 * Companion code for Chapter 12, "Building a Transform Codec."
 *
 * These two numbers answer the question the whole codec exists to manage:
 * how far did the reconstruction drift from the original? MSE is the average
 * squared pixel error; PSNR re-expresses it on a logarithmic decibel scale
 * referenced to the maximum pixel value, which matches how engineers
 * habitually quote quality. Higher PSNR means a closer reconstruction.
 */

#include <math.h>
#include "psnr.h"

#define MAX_PIXEL 255.0

/* Mean squared error between original a[] and reconstruction b[], length n. */
double mse(const unsigned char *a, const unsigned char *b, int n)
{
    double acc = 0.0;
    for (int i = 0; i < n; i++) {
        double e = (double)a[i] - (double)b[i];
        acc += e * e;
    }
    return acc / (double)n;
}

/*
 * PSNR in decibels. A perfect reconstruction has zero MSE; we report a large
 * sentinel in that case since the logarithm would otherwise diverge.
 */
double psnr(const unsigned char *a, const unsigned char *b, int n)
{
    double m = mse(a, b, n);
    if (m <= 0.0)
        return 99.0;  /* effectively lossless */
    return 10.0 * log10((MAX_PIXEL * MAX_PIXEL) / m);
}
