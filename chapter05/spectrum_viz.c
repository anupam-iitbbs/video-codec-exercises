/*
 * spectrum_viz.c  -  Chapter 5, Exercise 4
 *
 * Compute the magnitude spectrum of a signal and print it as a
 * simple ASCII bar chart, so you can SEE where the energy lands.
 * The default signal is a sum of a slow and a fast sinusoid; the
 * spectrum shows two clear peaks.
 *
 * Build: gcc -O2 -o spectrum_viz spectrum_viz.c -lm
 * Run:   ./spectrum_viz
 */

#include <stdio.h>
#include <math.h>

#define N 32
#define TWO_PI 6.283185307179586

int main(void)
{
    double x[N];
    double mag[N];
    double maxmag = 0.0;

    /* signal: slow component (k=2) plus weaker fast one (k=9) */
    for (int n = 0; n < N; ++n)
        x[n] = sin(TWO_PI * 2 * n / N) + 0.4 * sin(TWO_PI * 9 * n / N);

    /* magnitude spectrum via the direct DFT */
    for (int k = 0; k < N; ++k) {
        double re = 0.0, im = 0.0;
        for (int n = 0; n < N; ++n) {
            double a = TWO_PI * k * n / N;
            re += x[n] * cos(a);
            im -= x[n] * sin(a);
        }
        mag[k] = sqrt(re * re + im * im);
        if (mag[k] > maxmag) maxmag = mag[k];
    }

    /* ASCII bar chart */
    printf("bin   magnitude\\n");
    for (int k = 0; k < N; ++k) {
        int bars = (maxmag > 0) ? (int)(40.0 * mag[k] / maxmag) : 0;
        printf("%3d  ", k);
        for (int b = 0; b < bars; ++b) putchar("#"[0]);
        printf("  %.2f\\n", mag[k]);
    }
    return 0;
}
