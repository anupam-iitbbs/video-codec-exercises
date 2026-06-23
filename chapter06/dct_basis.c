/*
 * dct_basis.c  -  Chapter 6, Exercise 1
 *
 * Generate the N one-dimensional DCT-II basis functions and print
 * them, so you can see the ladder run from flat (DC) to fast. Each
 * row k is the basis vector cos[pi*(2n+1)*k/(2N)] scaled by alpha(k).
 *
 * Build: gcc -O2 -o dct_basis dct_basis.c -lm
 * Run:   ./dct_basis
 */

#include <stdio.h>
#include <math.h>

#define N 8
#define PI 3.14159265358979323846

static double alpha(int k)
{
    return (k == 0) ? sqrt(1.0 / N) : sqrt(2.0 / N);
}

int main(void)
{
    for (int k = 0; k < N; ++k) {
        printf("basis k=%d: ", k);
        for (int n = 0; n < N; ++n) {
            double b = alpha(k) * cos(PI * (2 * n + 1) * k / (2.0 * N));
            printf("% .3f ", b);
        }
        putchar("\n"[0]);
    }
    printf("\nRow 0 is flat (the DC basis); higher rows wiggle faster.\n");
    return 0;
}
