/*
 * dct_2d.c  -  Chapter 6, Exercise 3
 *
 * Apply the separable 2D DCT-II to an 8x8 block and print the
 * coefficient array. For a smooth block the DC term (top-left)
 * dominates and most other coefficients are near zero.
 *
 * Build: gcc -O2 -o dct_2d dct_2d.c -lm
 * Run:   ./dct_2d
 */

#include <stdio.h>
#include <math.h>

#define N 8
#define PI 3.14159265358979323846

static double alpha(int k)
{
    return (k == 0) ? sqrt(1.0 / N) : sqrt(2.0 / N);
}

/* 2D DCT computed separably: rows first, then columns. */
static void dct2(double in[N][N], double out[N][N])
{
    double tmp[N][N];
    /* transform each row */
    for (int r = 0; r < N; ++r)
        for (int k = 0; k < N; ++k) {
            double s = 0.0;
            for (int n = 0; n < N; ++n)
                s += in[r][n] * cos(PI * (2 * n + 1) * k / (2.0 * N));
            tmp[r][k] = alpha(k) * s;
        }
    /* transform each column */
    for (int c = 0; c < N; ++c)
        for (int k = 0; k < N; ++k) {
            double s = 0.0;
            for (int n = 0; n < N; ++n)
                s += tmp[n][c] * cos(PI * (2 * n + 1) * k / (2.0 * N));
            out[k][c] = alpha(k) * s;
        }
}

int main(void)
{
    double block[N][N], coef[N][N];
    for (int y = 0; y < N; ++y)
        for (int x = 0; x < N; ++x)
            block[y][x] = 100.0 + 3.0 * (x + y);   /* smooth gradient */

    dct2(block, coef);

    printf("2D DCT coefficients (DC at top-left dominates):\n\n");
    for (int u = 0; u < N; ++u) {
        for (int v = 0; v < N; ++v)
            printf("%8.2f", coef[u][v]);
        putchar("\n"[0]);
    }
    return 0;
}
