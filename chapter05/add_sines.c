/*
 * add_sines.c  -  Chapter 5, Exercise 2
 *
 * Add two sinusoids of different frequencies and show that the
 * combined signal still contains exactly two frequencies, not a
 * blurred average. Demonstrates superposition of sine waves.
 *
 * Build: gcc -O2 -o add_sines add_sines.c -lm
 * Run:   ./add_sines
 */

#include <stdio.h>
#include <math.h>

#define N 64                 /* number of samples            */
#define TWO_PI 6.283185307179586

int main(void)
{
    double f1 = 3.0;         /* first frequency  (cycles)    */
    double f2 = 7.0;         /* second frequency (cycles)    */
    double a1 = 1.0;         /* amplitude of first sinusoid  */
    double a2 = 0.5;         /* amplitude of second sinusoid */
    double x[N];

    for (int n = 0; n < N; ++n) {
        double s1 = a1 * sin(TWO_PI * f1 * n / N);
        double s2 = a2 * sin(TWO_PI * f2 * n / N);
        x[n] = s1 + s2;
        printf("%2d  % .5f\n", n, x[n]);
    }

    printf("\nThe sum still contains exactly two pure frequencies\n");
    printf("(f1=%.0f and f2=%.0f). A DFT of x[] would show two\n", f1, f2);
    printf("nonzero magnitudes, not a single averaged one.\n");
    return 0;
}
