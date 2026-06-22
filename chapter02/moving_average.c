/*
 * moving_average.c
 *
 * Chapter 2: Signals and Systems --- The Language of Change
 * Companion code for "From Signals to Video Codecs", Volume 1.
 *
 * A three-point moving-average filter: the simplest possible system
 * that smooths a one-dimensional signal. This is the concrete numerical
 * twin of the convolution-as-weighted-averaging idea from the chapter.
 *
 * Each output sample is the average of an input sample and its two
 * neighbours:
 *
 *     y[n] = ( x[n-1] + x[n] + x[n+1] ) / 3
 *
 * At the two ends, where a neighbour is missing, we simply repeat the
 * edge sample (a common, cheap boundary rule).
 *
 * Build:  gcc -O2 -Wall -o moving_average moving_average.c
 * Run:    ./moving_average
 *
 * Try changing the input to a flat run with a single spike, e.g.
 *     10 11 12 40 11 10
 * and watch the spike get smeared across its neighbours. That smearing
 * is exactly what a low-pass filter does, and why it removes
 * high-frequency detail.
 */

#include <stdio.h>

/* Apply a 3-point moving average to x[0..n-1], writing into y[0..n-1]. */
void moving_average3(const double *x, double *y, int n)
{
    if (n <= 0) {
        return;
    }
    if (n == 1) {
        y[0] = x[0];
        return;
    }

    /* First sample: no left neighbour, so reuse x[0]. */
    y[0] = (x[0] + x[0] + x[1]) / 3.0;

    /* Interior samples: the true three-point average. */
    for (int i = 1; i < n - 1; i++) {
        y[i] = (x[i - 1] + x[i] + x[i + 1]) / 3.0;
    }

    /* Last sample: no right neighbour, so reuse x[n-1]. */
    y[n - 1] = (x[n - 2] + x[n - 1] + x[n - 1]) / 3.0;
}

int main(void)
{
    /* One row of brightness with a flat background and a single spike. */
    double x[] = { 10, 11, 12, 40, 11, 10 };
    int n = (int)(sizeof(x) / sizeof(x[0]));
    double y[sizeof(x) / sizeof(x[0])];

    moving_average3(x, y, n);

    printf("  n     x[n]     y[n]\n");
    printf("-----------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%3d  %7.2f  %7.2f\n", i, x[i], y[i]);
    }

    return 0;
}
