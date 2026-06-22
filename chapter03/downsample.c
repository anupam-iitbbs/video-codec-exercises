/*
 * downsample.c  --- Chapter 3, Exercise 1: Downsampling
 *
 * Companion code for "From Signals to Video Codecs", Volume 1.
 *
 * Generate samples of a sine wave, then keep only every k-th sample
 * (downsampling by a factor of k). Print both so you can compare the
 * full-rate and reduced-rate signals. If the original is near its
 * Nyquist limit, the downsampled version will look like a SLOWER wave
 * --- your first taste of aliasing (see aliasing.c).
 *
 * Build:  gcc -O2 -Wall -o downsample downsample.c -lm
 * Run:    ./downsample
 */

#include <stdio.h>
#include <math.h>

#define N 32          /* number of original samples            */
#define FACTOR 2      /* keep every FACTOR-th sample            */

int main(void)
{
    double fs = 1.0;          /* normalised sampling rate        */
    double f  = 0.1;          /* signal frequency (cycles/sample)*/
    double x[N];

    /* Generate the full-rate signal x[n] = sin(2*pi*f*n). */
    for (int n = 0; n < N; n++) {
        x[n] = sin(2.0 * M_PI * f * n / fs);
    }

    /* Downsample: keep every FACTOR-th sample. */
    printf("Full-rate signal (N = %d):\n", N);
    for (int n = 0; n < N; n++) {
        printf("%2d: % .3f\n", n, x[n]);
    }

    printf("\nDownsampled by %d:\n", FACTOR);
    for (int n = 0; n < N; n += FACTOR) {
        printf("%2d: % .3f\n", n, x[n]);
    }

    printf("\nTry raising f toward 0.5 and watch the downsampled\n");
    printf("signal masquerade as a lower frequency (aliasing).\n");
    return 0;
}
