/*
 * manual_dft.c  -  Chapter 5, Exercise 3
 *
 * Compute the Discrete Fourier Transform directly from its
 * definition for N = 8, with no FFT shortcuts. Use it to verify
 * the worked examples from the chapter:
 *   - a constant signal yields only X[0],
 *   - x[n] = cos(2*pi*n/8) yields X[1] = X[7] = 4 (others ~ 0).
 *
 * Build: gcc -O2 -o manual_dft manual_dft.c -lm
 * Run:   ./manual_dft
 */

#include <stdio.h>
#include <math.h>

#define N 8
#define TWO_PI 6.283185307179586

/* Compute and print the DFT magnitudes of x[]. */
static void dft(const double *x, const char *label)
{
    printf("%s\n", label);
    for (int k = 0; k < N; ++k) {
        double re = 0.0, im = 0.0;
        for (int n = 0; n < N; ++n) {
            double angle = TWO_PI * k * n / N;
            re += x[n] * cos(angle);
            im -= x[n] * sin(angle);   /* note the minus sign */
        }
        double mag = sqrt(re * re + im * im);
        printf("  X[%d] = % .3f % +.3fj   |X[%d]| = %.3f\n",
               k, re, im, k, mag);
    }
    printf("\n");
}

int main(void)
{
    double constant[N];
    double cosine[N];

    for (int n = 0; n < N; ++n) {
        constant[n] = 5.0;                       /* flat signal      */
        cosine[n]   = cos(TWO_PI * n / N);       /* one cycle        */
    }

    dft(constant, "Constant signal (expect only X[0] nonzero):");
    dft(cosine,   "Cosine, one cycle (expect X[1]=X[7]=4):");
    return 0;
}
