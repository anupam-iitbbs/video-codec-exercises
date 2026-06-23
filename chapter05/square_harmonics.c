/*
 * square_harmonics.c  -  Chapter 5, Exercise 5
 *
 * Build a square wave, take its DFT, and watch the tail of odd
 * harmonics that its sharp edges demand. The amplitudes of the
 * odd harmonics fall off roughly as 1/k, while the even
 * harmonics are essentially zero.
 *
 * Build: gcc -O2 -o square_harmonics square_harmonics.c -lm
 * Run:   ./square_harmonics
 */

#include <stdio.h>
#include <math.h>

#define N 64
#define TWO_PI 6.283185307179586

int main(void)
{
    double x[N];
    double mag[N];
    double maxmag = 0.0;

    /* square wave: +1 for first half period, -1 for second */
    for (int n = 0; n < N; ++n)
        x[n] = (n % 16 < 8) ? 1.0 : -1.0;

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

    printf("Square-wave spectrum (note odd harmonics, 1/k decay):\\n");
    printf("bin   magnitude\\n");
    for (int k = 0; k < N / 2; ++k) {
        int bars = (maxmag > 0) ? (int)(40.0 * mag[k] / maxmag) : 0;
        printf("%3d  ", k);
        for (int b = 0; b < bars; ++b) putchar("#"[0]);
        printf("  %.2f\\n", mag[k]);
    }
    return 0;
}
